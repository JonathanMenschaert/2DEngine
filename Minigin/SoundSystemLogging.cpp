#include "SoundSystemLogging.h"
#include <iostream>
dae::SoundSystemLogging::SoundSystemLogging(std::unique_ptr<SoundSystem>&& soundsystem)
    :m_pSoundSystem{std::move(soundsystem)}
{
}

void dae::SoundSystemLogging::Play(unsigned int soundId, int volume)
{
    std::cout << "Playing sound with id " << soundId << " and volume " << volume << "\n";
    m_pSoundSystem->Play(soundId, volume);
}

void dae::SoundSystemLogging::Pause(unsigned int soundIdx)
{
    std::cout << "Pausing sound with id " << soundIdx << "\n";
    m_pSoundSystem->Pause(soundIdx);
}

void dae::SoundSystemLogging::Resume(unsigned int soundIdx)
{
    std::cout << "Resuming sound with id " << soundIdx << "\n";
    m_pSoundSystem->Resume(soundIdx);
}

void dae::SoundSystemLogging::SetVolume(unsigned int soundIdx, int volume)
{
    std::cout << "Changing volume of sound with " << soundIdx << " to " << volume << "\n";
    m_pSoundSystem->SetVolume(soundIdx, volume);
}

void dae::SoundSystemLogging::Stop(unsigned int idx)
{
    std::cout << "Stopping sound with id " << idx << "\n";
    m_pSoundSystem->Stop(idx);
}

void dae::SoundSystemLogging::LoadSound(const std::string& soundPath)
{
    std::cout << "Loading sound file " << soundPath << "\n";
    m_pSoundSystem->LoadSound(soundPath);
}

unsigned int dae::SoundSystemLogging::FindSoundId(const std::string soundName)
{
    std::cout << "Lookup of id of " << soundName << "\n";
    return m_pSoundSystem->FindSoundId(soundName);
}
