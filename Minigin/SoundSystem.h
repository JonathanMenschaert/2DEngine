#pragma once
namespace dae
{
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(unsigned int soundId, float volume) = 0;
	};
}

