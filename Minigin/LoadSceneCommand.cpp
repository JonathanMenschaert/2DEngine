#include "LoadSceneCommand.h"

dae::LoadSceneCommand::LoadSceneCommand(LoadSceneComponent* pLoadScene)
	:m_pLoadScene{pLoadScene}
{
}

void dae::LoadSceneCommand::Execute()
{
	m_pLoadScene->LoadScene();
}
