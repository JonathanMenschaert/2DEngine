#include "MuteCommand.h"
#include "ServiceLocator.h"

void dae::MuteCommand::Execute()
{
	ServiceLocator::GetSoundSystem().Mute(!ServiceLocator::GetSoundSystem().IsMuted());
}
