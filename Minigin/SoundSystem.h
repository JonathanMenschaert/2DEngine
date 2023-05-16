#pragma once
#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(unsigned int soundIdx, int volume) = 0;
		virtual void Pause(unsigned int soundIdx) = 0;
		virtual void Resume(unsigned int soundIdx) = 0;
		virtual void SetVolume(unsigned int soundIdx, int volume) = 0;
		virtual void Stop(unsigned int idx) = 0;
		virtual void LoadSound(const std::string& soundPath) = 0;
		virtual unsigned int FindSoundId(const std::string soundName) = 0;
	};
}

