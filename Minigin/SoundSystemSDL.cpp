#include "SoundSystemSDL.h"
#include <thread>
#include <mutex>
#include "SDL_mixer.h"
#include "SDL.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace dae;

class SoundSystemSDL::SoundSystemSDLImpl
{
public:

	SoundSystemSDLImpl()
	{
		//Init SDL Audio
		if (SDL_Init(SDL_INIT_AUDIO) < 0)
		{
			std::cerr << "Unable to initialize SDL_Audio! " << SDL_GetError();
			return;
		}

		//Init SDL Mixer
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
		{
			std::cerr << "Unable to initialize SDL_Mixer! " << SDL_GetError();
			return;
		}

		m_Thread = std::jthread{ [&] {HandleSound(); } };
		

		//Mix_ChannelFinished()

	}

	~SoundSystemSDLImpl()
	{
		m_Thread.request_stop();
		m_ThreadCondition.notify_all();
	}

	void Play(unsigned int soundIdx, float volume)
	{
		m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Play, soundIdx, volume});
		m_ThreadCondition.notify_one();
	}

	void Pause(unsigned int soundIdx)
	{
		m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Pause, soundIdx});
		m_ThreadCondition.notify_one();
	}

	void Resume(unsigned int soundIdx)
	{
		m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Resume, soundIdx});
		m_ThreadCondition.notify_one();
	}

	void SetVolume(unsigned int soundIdx, float volume)
	{
		m_SoundQueue.push(SoundEvent{ SoundEvent::Type::VolumeChange, soundIdx, volume });
		m_ThreadCondition.notify_one();
	}

	void Stop(unsigned int soundIdx)
	{
		m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Stop, soundIdx});
		m_ThreadCondition.notify_one();
	}

	void LoadSound(const std::string& soundPath)
	{
		m_SoundQueue.push(SoundEvent{ SoundEvent::Type::Load, 0, 0.0f, soundPath });
		m_ThreadCondition.notify_one();
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
			VolumeChange
		};

		Type eventType{};
		unsigned int soundIdx{};
		float volume{};
		std::string data{};
	};

	struct Sound
	{
		Mix_Chunk* soundData{};
		std::string soundName{};
	};

	void HandleSound()
	{
		const std::stop_token& stopToken{ m_Thread.get_stop_token() };
		while (!stopToken.stop_requested())
		{
			std::unique_lock lock{ m_Lock };
			m_ThreadCondition.wait(lock);

			while (m_SoundQueue.size() > 0)
			{
				SoundEvent soundEvent{ m_SoundQueue.front()};
				m_SoundQueue.pop();
				switch (soundEvent.eventType)	
				{
				case SoundEvent::Type::Play:
				{
					
				}
				break;
				case SoundEvent::Type::Pause:
				{
				}
				break;
				case SoundEvent::Type::Resume:
				{
				}
				break;
				case SoundEvent::Type::Stop:
				{
				}
				break;
				case SoundEvent::Type::Load:
				{

				}
				break;
				case SoundEvent::Type::VolumeChange:
				{
				}
				break;
				}
			}
		}
	}

	void HandleSoundEnd(int/* channel*/)
	{

	}

	std::queue<SoundEvent> m_SoundQueue{};
	std::jthread m_Thread{};
	std::condition_variable m_ThreadCondition{};
	std::mutex m_Lock{};
	std::vector<Sound> m_LoadedSounds{};
};

dae::SoundSystemSDL::SoundSystemSDL()
	:m_pImpl{std::make_unique<SoundSystemSDLImpl>()}
{	
}

dae::SoundSystemSDL::~SoundSystemSDL()
{
}

void dae::SoundSystemSDL::Play(unsigned int soundId, float volume)
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

void dae::SoundSystemSDL::SetVolume(unsigned int soundIdx, float volume)
{
	m_pImpl->SetVolume(soundIdx, volume);
}

void dae::SoundSystemSDL::Stop(unsigned int soundIdx)
{
	m_pImpl->Stop(soundIdx);
}

void dae::SoundSystemSDL::LoadSound(const std::string& soundPath)
{
	return m_pImpl->LoadSound(soundPath);
}
