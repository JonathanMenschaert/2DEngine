#include "GhostWanderState.h"
#include "GhostScaredState.h"

std::unique_ptr<dae::GhostState> dae::GhostWanderState::UpdateState(const GhostComponent* pGhost) const
{
	if (pGhost->IsScared())
	{
		return std::make_unique<GhostScaredState>();
	}
	return nullptr;
}

glm::vec2 dae::GhostWanderState::GetNextDestination(GraphComponent* pGraph, const glm::vec2& currentPos) const
{	
	return pGraph->GetRandomNextPosition(currentPos);
}
