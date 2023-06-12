#pragma once
#include "SoundSystem.h"
#include <memory>
namespace dae
{
	class DefaultSoundSystem final : public SoundSystem
	{
		virtual void Play(unsigned int, int) override {}
		virtual void Pause(unsigned int) override {}
		virtual void Resume(unsigned int) override {}
		virtual void SetVolume(unsigned int, int ) override {}
		virtual void Stop(unsigned int ) override {}
		virtual void Mute(bool ) override {};
		virtual bool IsMuted() override { return false; }
		virtual void LoadSound(const std::string&) override { }
		virtual unsigned int FindSoundId(const std::string soundName) override { return UINT32_MAX;  };
	};

	class ServiceLocator final
	{
	public:

		static SoundSystem& GetSoundSystem();
		
		
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem)
		{
			m_pSoundSystemInstance = std::move(soundSystem);
		}
	
	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystemInstance;
		static std::unique_ptr<DefaultSoundSystem> m_pDefaultSoundSystem;
	};
}

