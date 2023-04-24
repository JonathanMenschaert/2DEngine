#include "DebugScoreCommand.h"
#include "ScoreComponent.h"
dae::DebugScoreCommand::DebugScoreCommand(GameObject* pActor, int score)
	:m_pActor{pActor}
	,m_Score{score}
{
}

void dae::DebugScoreCommand::Execute()
{
	auto pScore{ m_pActor->GetComponent<dae::ScoreComponent>() };
	if (pScore)
	{
		pScore->AddScore(m_Score);
	}
}
