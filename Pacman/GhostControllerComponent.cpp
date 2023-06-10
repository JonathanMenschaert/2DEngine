#include "GhostControllerComponent.h"
#include <iostream>
#include "GhostWanderState.h"
dae::GhostControllerComponent::GhostControllerComponent(GameObject* pGameObject)
	:UpdateComponent{ pGameObject }
	, m_Speed{ 75.f }
	, m_AcceptanceRadius{ 0.5f }
{
	GameObject* pGameObj{ GetGameObject() };
	m_pUpCommand = std::make_unique<MoveCommand>(pGameObj, m_Speed, glm::vec2{0.f, 1.f});
	m_pDownCommand = std::make_unique<MoveCommand>(pGameObj, m_Speed, glm::vec2{ 0.f, -1.f });
	m_pRightCommand = std::make_unique<MoveCommand>(pGameObj, m_Speed, glm::vec2{ 1.f, 0.f });
	m_pLeftCommand = std::make_unique<MoveCommand>(pGameObj, m_Speed, glm::vec2{ -1.f, 0.f });
}
void dae::GhostControllerComponent::Init()
{
	m_pGraph = GetGameObject()->GetComponentInParent<GraphComponent>();
	m_pTransform = GetGameObject()->GetTransform();
	m_Destination = m_pGraph->GetRandomNextPosition(m_pTransform->GetLocalPosition());
	m_pState = std::make_unique<GhostWanderState>();
	m_pControlledGhost = GetGameObject()->GetComponent<GhostComponent>();
}

void dae::GhostControllerComponent::Update()
{
	const glm::vec2& localPos{ m_pTransform->GetLocalPosition() };
	std::unique_ptr<GhostState> newState = m_pState->UpdateState(m_pControlledGhost);
	if (newState)
	{
		m_pState = std::move(newState);
		const glm::vec2 nextPos {m_pState->GetNextDestination(m_pGraph, localPos)};
		if (nextPos != localPos)
		{
			m_Destination = nextPos;
		}
	}

	const glm::vec2 movementVector{ m_Destination - localPos };
	if (movementVector.x > m_AcceptanceRadius)
	{
		m_pRightCommand->Execute();
	}
	else if (movementVector.x < -m_AcceptanceRadius)
	{
		m_pLeftCommand->Execute();
	}
	else
	{
		m_pTransform->SetLocalPosition(glm::vec2{m_Destination.x, localPos.y});
	}

	if (movementVector.y > m_AcceptanceRadius)
	{
		m_pDownCommand->Execute();
	}
	else if (movementVector.y < -m_AcceptanceRadius)
	{
		m_pUpCommand->Execute();
	}
	else
	{
		m_pTransform->SetLocalPosition(glm::vec2{localPos.x, m_Destination.y});
	}

	if (localPos == m_Destination)
	{
		m_Destination = m_pState->GetNextDestination(m_pGraph, localPos);
	}
}
