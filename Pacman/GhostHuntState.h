#pragma once
#include "GhostState.h"

namespace dae
{
	class GhostHuntState final : public GhostState
	{
	public:
		GhostHuntState() = default;
		virtual ~GhostHuntState() = default;
		GhostHuntState(const GhostHuntState& other) = delete;
		GhostHuntState(GhostHuntState&& other) noexcept = delete;
		GhostHuntState& operator=(const GhostHuntState& other) = delete;
		GhostHuntState& operator=(GhostHuntState&& other) noexcept = delete;

		virtual std::unique_ptr<GhostState> UpdateState(const GhostComponent* pGhost) const override;
		virtual glm::vec2 GetNextDestination(GraphComponent* pGraph, const glm::vec2& currentPos) const override;

	};
}

