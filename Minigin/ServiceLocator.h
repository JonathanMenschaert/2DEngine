#pragma once
#include "SoundSystem.h"
#include <memory>
namespace dae
{
	class DefaultSoundSystem final : public SoundSystem
	{
		virtual void Play(unsigned int, float) override {};
	};

	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem();
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem);
	
	private:
		static std::unique_ptr<SoundSystem> m_pSoundSystemInstance;
		static std::unique_ptr<SoundSystem> m_pDefaultSoundSystem;
	};
}

