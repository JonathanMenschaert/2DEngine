#include "GhostHuntState.h"

std::unique_ptr<dae::GhostState> dae::GhostHuntState::UpdateState(const GhostComponent* /*pGhost*/) const
{
    return std::unique_ptr<GhostState>();
}

glm::vec2 dae::GhostHuntState::GetNextDestination(GraphComponent* pGraph, const glm::vec2& currentPos) const
{
    return pGraph->GetRandomNextPosition(currentPos);
}
