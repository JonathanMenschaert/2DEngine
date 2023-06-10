#pragma once
#include "GhostState.h"

namespace dae
{
	class GhostScaredState final : public GhostState
	{
	public:
		GhostScaredState() = default;
		virtual ~GhostScaredState() = default;
		GhostScaredState(const GhostScaredState& other) = delete;
		GhostScaredState(GhostScaredState&& other) noexcept = delete;
		GhostScaredState& operator=(const GhostScaredState& other) = delete;
		GhostScaredState& operator=(GhostScaredState&& other) noexcept = delete;

		virtual std::unique_ptr<GhostState> UpdateState(const GhostComponent* pGhost) const override;
		virtual glm::vec2 GetNextDestination(GraphComponent* pGraph, const glm::vec2& currentPos) const override;

	};
}

