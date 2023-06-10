#pragma once
#include "GhostState.h"

namespace dae
{
	class GhostWanderState final : public GhostState
	{
	public:
		GhostWanderState() = default;
		virtual ~GhostWanderState() = default;
		GhostWanderState(const GhostWanderState& other) = delete;
		GhostWanderState(GhostWanderState&& other) noexcept = delete;
		GhostWanderState& operator=(const GhostWanderState& other) = delete;
		GhostWanderState& operator=(GhostWanderState&& other) noexcept = delete;

		virtual std::unique_ptr<GhostState> UpdateState() const override;
		virtual glm::vec2 GetNextDestination(const GraphComponent* pGraph, const glm::vec2& currentPos) const override;

	};
}

