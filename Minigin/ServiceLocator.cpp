#include "ServiceLocator.h"

std::unique_ptr<dae::DefaultSoundSystem> dae::ServiceLocator::m_pDefaultSoundSystem{std::make_unique<dae::DefaultSoundSystem>()};
std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_pSoundSystemInstance{ nullptr};

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
    return m_pSoundSystemInstance.get() != nullptr ? *m_pSoundSystemInstance : *m_pDefaultSoundSystem;
}


