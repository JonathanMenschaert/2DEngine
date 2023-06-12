#pragma once
#include "SoundSystem.h"
#include <memory>
namespace dae
{
	class SoundSystemLogging final : public SoundSystem
	{
	public:
		SoundSystemLogging(std::unique_ptr<SoundSystem>&& soundsystem);
		virtual ~SoundSystemLogging() = default;
		SoundSystemLogging(const SoundSystemLogging& soundSystem) = delete;
		SoundSystemLogging(SoundSystemLogging&& soundSystem) noexcept = delete;
		SoundSystemLogging& operator=(const SoundSystemLogging& soundSystem) = delete;
		SoundSystemLogging& operator=(SoundSystemLogging&& soundSystem) noexcept = delete;

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
		std::unique_ptr<SoundSystem> m_pSoundSystem{};
	};
}

