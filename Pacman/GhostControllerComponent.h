#pragma once
#include <UpdateComponent.h>
#include "MoveCommand.h"
#include <memory>
#include "GraphComponent.h"
#include "TransformComponent.h"
#include "GhostState.h"
#include "GhostComponent.h"
namespace dae
{
	class GhostControllerComponent : public UpdateComponent
	{
	public:
		GhostControllerComponent(GameObject* pGameObject);
		virtual ~GhostControllerComponent() noexcept = default;
		GhostControllerComponent(const GhostControllerComponent& graphComponent) = delete;
		GhostControllerComponent(GhostControllerComponent&& GhostControllerComponent) noexcept = delete;
		GhostControllerComponent& operator=(const GhostControllerComponent& graphComponent) = delete;
		GhostControllerComponent& operator=(GhostControllerComponent&& graphComponent) noexcept = delete;

		virtual void Init() override;
		virtual void Update() override;

		

	private:

		std::unique_ptr<MoveCommand> m_pUpCommand{};
		std::unique_ptr<MoveCommand> m_pDownCommand{};
		std::unique_ptr<MoveCommand> m_pLeftCommand{};
		std::unique_ptr<MoveCommand> m_pRightCommand{};

		GraphComponent* m_pGraph{};
		TransformComponent* m_pTransform{};
		GhostComponent* m_pControlledGhost{};
		const float m_Speed;
		const float m_AcceptanceRadius{};

		glm::vec2 m_Destination{};	

		std::unique_ptr<GhostState> m_pState{};

    };
}

