#pragma once
#include "SoundSystem.h"
#include <memory>

namespace dae
{
	class SoundSystemSDL final : public SoundSystem
	{
	public:
		SoundSystemSDL();
		virtual ~SoundSystemSDL();
		SoundSystemSDL(const SoundSystemSDL& soundSystem) = delete;
		SoundSystemSDL(SoundSystemSDL&& soundSystem) noexcept = delete;
		SoundSystemSDL& operator=(const SoundSystemSDL& soundSystem) = delete;
		SoundSystemSDL& operator=(SoundSystemSDL&& soundSystem) noexcept = delete;

		virtual void Play(unsigned int soundId, int volume) override;
		virtual void Pause(unsigned int soundIdx) override;
		virtual void Resume(unsigned int soundIdx) override;
		virtual void SetVolume(unsigned int soundIdx, int volume) override;
		virtual void Stop(unsigned int idx) override;
		virtual void Mute(bool mute) override;
		virtual bool IsMuted() override;
		virtual void LoadSound(const std::string& soundPath) override;
		virtual unsigned int FindSoundId(const std::string soundName) override;

	private:

		class SoundSystemSDLImpl;
		std::unique_ptr<SoundSystemSDLImpl> m_pImpl;
	};
}

