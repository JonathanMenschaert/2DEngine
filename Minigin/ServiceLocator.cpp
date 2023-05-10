#include "ServiceLocator.h"

std::unique_ptr<dae::SoundSystem> dae::ServiceLocator::m_pSoundSystemInstance = std::move(dae::ServiceLocator::m_pDefaultSoundSystem);

dae::SoundSystem& dae::ServiceLocator::GetSoundSystem()
{
    return *m_pSoundSystemInstance;
}

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<SoundSystem> soundSystem)
{
    if (soundSystem)
    {
        m_pDefaultSoundSystem = std::move(m_pSoundSystemInstance);
        m_pSoundSystemInstance = std::move(soundSystem);
        m_pDefaultSoundSystem = nullptr;
    }
    else if (m_pDefaultSoundSystem)
    {
        m_pSoundSystemInstance =  std::move(m_pDefaultSoundSystem);
    }
}


