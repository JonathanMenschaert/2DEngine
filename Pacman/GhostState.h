#pragma once
#include <memory>
#include "glm/glm.hpp"
#include "GraphComponent.h"
#include "GhostComponent.h"

namespace dae
{
	class GhostState
	{
	public:
		virtual ~GhostState() = default;
		virtual std::unique_ptr<GhostState> UpdateState(const GhostComponent* pGhost) const = 0;
		virtual glm::vec2 GetNextDestination(GraphComponent* pGraph, const glm::vec2& currentPos) const = 0;
 
	};
}

