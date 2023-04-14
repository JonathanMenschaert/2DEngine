#include "DebugLivesCommand.h"
#include "LivesComponent.h"

dae::DebugLivesCommand::DebugLivesCommand(GameObject* pActor)
	: m_pActor{pActor}
{
}

void dae::DebugLivesCommand::Execute()
{
	auto pLives{ m_pActor->GetComponent<dae::LivesComponent>().lock()};
	if (pLives)
	{
		pLives->AddLife(-1);
	}
}
