#include "GhostWanderState.h"

std::unique_ptr<dae::GhostState> dae::GhostWanderState::UpdateState() const
{
	return std::unique_ptr<dae::GhostState>();
}

glm::vec2 dae::GhostWanderState::GetNextDestination(const GraphComponent* /*pGraph*/, const glm::vec2& currentPos) const
{
	return currentPos;
}
