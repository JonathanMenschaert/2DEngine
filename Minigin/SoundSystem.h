#pragma once
#include <string>

namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(unsigned int soundIdx, float volume) = 0;
		virtual void Pause(unsigned int soundIdx) = 0;
		virtual void Resume(unsigned int soundIdx) = 0;
		virtual void SetVolume(unsigned int soundIdx, float volume) = 0;
		virtual void Stop(unsigned int idx) = 0;
		virtual void LoadSound(const std::string& soundPath) = 0;
		
	};
}

