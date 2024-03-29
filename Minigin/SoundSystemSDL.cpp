#include "SoundSystemSDL.h"
#include <thread>
#include <mutex>
#include "SDL_mixer.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
using namespace dae;

class SoundSystemSDL::SoundSystemSDLImpl
{
public:

	SoundSystemSDLImpl()
	{
		//Init SDL Mixer
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, m_MaxChannels) < 0)
		{
			std::cerr << "Unable to initialize SDL_Mixer! " << SDL_GetError();
			return;
		}

		m_Thread = std::jthread{ [this]{HandleSound(); } };
	}

	~SoundSystemSDLImpl()
	{
		m_Thread.request_stop();
		m_ThreadCondition.notify_all();
		Mix_HaltChannel(m_ChannelWildcard);

		for (Sound& sound : m_LoadedSounds)
		{
			
			Mix_FreeChunk(sound.soundData);
		}
		
		Mix_CloseAudio();
		Mix_Quit();
	}

	void Play(unsigned int soundIdx, int volume)
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Play, soundIdx });
			if (!m_IsMuted)
			{
				m_SoundQueue.push(SoundEvent{ SoundEvent::Type::VolumeChange, soundIdx, volume });
			}
		}
		m_ThreadCondition.notify_one();
	}

	bool IsMuted()
	{
		return m_IsMuted;
	}

	void Pause(unsigned int soundIdx)
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Pause, soundIdx });
		}
		m_ThreadCondition.notify_one();
	}

	void Resume(unsigned int soundIdx)
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Resume, soundIdx });
		}
		m_ThreadCondition.notify_one();
	}

	void SetVolume(unsigned int soundIdx, int volume)
	{
		if (m_IsMuted)
		{
			return;
		}
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::VolumeChange, soundIdx, volume });
		}
		m_ThreadCondition.notify_one();
	}

	void Stop(unsigned int soundIdx)
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Stop, soundIdx });
		}
		m_ThreadCondition.notify_one();
	}

	void Mute(bool mute)
	{
		m_IsMuted = mute;
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Mute, 0, (mute ? 0 : m_CurrentVolume) });
		}
		m_ThreadCondition.notify_one();
	}

	void LoadSound(const std::string& soundPath)
	{
		{
			std::lock_guard lock{ m_Lock };
			m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Load, UINT32_MAX, 0, soundPath });
		}
		m_ThreadCondition.notify_one();
	}

	unsigned int FindSoundId(const std::string& soundName)
	{
		auto soundIt = std::find_if(m_LoadedSounds.begin(), m_LoadedSounds.end(), [&soundName](const Sound& element)
			{
				return element.soundName == soundName;
			});

		if (soundIt != m_LoadedSounds.end())
		{
			return static_cast<unsigned int>(std::distance(m_LoadedSounds.begin(), soundIt));
		}
		return UINT32_MAX;
	}

private:

	struct SoundEvent
	{
		enum class Type
		{
			Play,
			Pause,
			Resume,
			Stop,
			Load,
			VolumeChange,
			Mute
		};

		Type eventType{};
		unsigned int soundIdx{};
		int volume{};
		std::string data{};
	};

	struct Sound
	{
		Mix_Chunk* soundData{};
		std::string soundName{};
		int channel{INT32_MAX};
	};

	void HandleSound()
	{
		const std::stop_token& stopToken{ m_Thread.get_stop_token() };
		while (!stopToken.stop_requested())
		{
			std::unique_lock lock{ m_Lock };
			m_ThreadCondition.wait(lock);
			while (m_SoundQueue.size() > 0 && !stopToken.stop_requested())
			{
				
				SoundEvent soundEvent{ m_SoundQueue.front()};
				m_SoundQueue.pop();

				lock.unlock();

				switch (soundEvent.eventType)	
				{
				case SoundEvent::Type::Play:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (Mix_Playing(sound.channel))
					{
						break;
					}

					if (sound.channel > m_MaxChannels)
					{
						const int channel{ Mix_PlayChannel(m_ChannelWildcard, sound.soundData, 0) };
						if (channel != m_ChannelWildcard)
						{
							sound.channel = channel;
						}
						else
						{
							break;
						}
					}
					else
					{
						Mix_PlayChannel(sound.channel, sound.soundData, 0);
					}
				}
				break;
				case SoundEvent::Type::Pause:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels && !Mix_Paused(sound.channel))
					{
						Mix_Pause(sound.channel);
					}					
				}
				break;
				case SoundEvent::Type::Resume:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels && Mix_Paused(sound.channel))
					{
						Mix_Resume(sound.channel);
					}					
				}
				break;
				case SoundEvent::Type::Stop:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels)
					{
						Mix_HaltChannel(sound.channel);
					}					
				}
				break;
				case SoundEvent::Type::Load:
				{
					std::stringstream filePath{};
					filePath << m_PathPrefix << soundEvent.data.c_str() << ".wav";
					Mix_Chunk* pSound{Mix_LoadWAV(filePath.str().c_str())};
					if (pSound)
					{						
						Sound sound{ pSound, soundEvent.data.c_str() };
						lock.lock();
						m_LoadedSounds.emplace_back(sound);
						lock.unlock();
					}				
				}
				break;
				case SoundEvent::Type::VolumeChange:
				{
					Sound& sound{ m_LoadedSounds[soundEvent.soundIdx] };
					if (sound.channel < m_MaxChannels)
					{
						Mix_Volume(sound.channel, soundEvent.volume);
					}					
				}
				break;
				case SoundEvent::Type::Mute:
					if (soundEvent.volume == 0)
					{
						Mix_Volume(-1, 0);
					}
					else
					{
						Mix_Volume(-1, soundEvent.volume);
					}
				break;
				}

				lock.lock();
			}
		}
	}

	std::queue<SoundEvent> m_SoundQueue{};
	std::jthread m_Thread{};
	std::condition_variable m_ThreadCondition{};
	std::mutex m_Lock{};
	std::vector<Sound> m_LoadedSounds{};
	const int m_ChannelWildcard{ -1 };
	const std::string m_PathPrefix{ "Data/"};
	const int m_MaxChannels{ 4096 };
	int m_CurrentVolume{ 100 };
	bool m_IsMuted{};
};

dae::SoundSystemSDL::SoundSystemSDL()
	:m_pImpl{std::make_unique<SoundSystemSDLImpl>()}
{	
}

dae::SoundSystemSDL::~SoundSystemSDL()
{
}

void dae::SoundSystemSDL::Play(unsigned int soundId, int volume)
{
	m_pImpl->Play(soundId, volume);
}

void dae::SoundSystemSDL::Pause(unsigned int soundIdx)
{
	m_pImpl->Pause(soundIdx);
}

void dae::SoundSystemSDL::Resume(unsigned int soundIdx)
{
	m_pImpl->Resume(soundIdx);
}

void dae::SoundSystemSDL::SetVolume(unsigned int soundIdx, int volume)
{
	m_pImpl->SetVolume(soundIdx, volume);
}

void dae::SoundSystemSDL::Stop(unsigned int soundIdx)
{
	m_pImpl->Stop(soundIdx);
}

void dae::SoundSystemSDL::Mute(bool mute)
{
	m_pImpl->Mute(mute);
}

bool dae::SoundSystemSDL::IsMuted()
{
	return m_pImpl->IsMuted();
}

void dae::SoundSystemSDL::LoadSound(const std::string& soundPath)
{
	return m_pImpl->LoadSound(soundPath);
}

unsigned int dae::SoundSystemSDL::FindSoundId(const std::string soundName)
{
	return m_pImpl->FindSoundId(soundName);
}
