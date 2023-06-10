#include "GhostScaredState.h"
#include "GhostWanderState.h"
std::unique_ptr<dae::GhostState> dae::GhostScaredState::UpdateState(const GhostComponent* pGhost) const
{
    if (!pGhost->IsScared())
    {
        return std::make_unique<GhostWanderState>();
    }
    return nullptr;
}

glm::vec2 dae::GhostScaredState::GetNextDestination(GraphComponent* pGraph, const glm::vec2& currentPos) const
{
    return pGraph->GetRandomNextPosition(currentPos);
}
