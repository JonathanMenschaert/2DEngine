#pragma once
#include "SoundSystem.h"
#include <memory>
namespace dae
{
	class DefaultSoundSystem final : public SoundSystem
	{
		virtual void Play(unsigned int, float) override {}
		virtual void Pause(unsigned int) override {}
		virtual void Resume(unsigned int) override {}
		virtual void SetVolume(unsigned int, float ) override {}
		virtual void Stop(unsigned int ) override {}
		virtual void LoadSound(const std::string&) override { }
	};

	class ServiceLocator final
	{
	public:

		static SoundSystem& GetSoundSystem();
		
		template <typename T>
		static void RegisterSoundSystem()
		{
			m_pSoundSystemInstance = std::make_unique<T>();
		}
	
	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystemInstance;
		static std::unique_ptr<DefaultSoundSystem> m_pDefaultSoundSystem;
	};
}

