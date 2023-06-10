#include "GhostControllerComponent.h"
#include <iostream>

dae::GhostControllerComponent::GhostControllerComponent(GameObject* pGameObject)
	:UpdateComponent{pGameObject}
	,m_Speed{25.f}
	,m_AcceptanceRadius{0.5f}
{
	m_pUpCommand = std::make_unique<MoveCommand>(GetGameObject(), m_Speed, glm::vec2{0.f, 1.f});
	m_pDownCommand = std::make_unique<MoveCommand>(GetGameObject(), m_Speed, glm::vec2{ 0.f, -1.f });
	m_pRightCommand = std::make_unique<MoveCommand>(GetGameObject(), m_Speed, glm::vec2{ 1.f, 0.f });
	m_pLeftCommand = std::make_unique<MoveCommand>(GetGameObject(), m_Speed, glm::vec2{ -1.f, 0.f });
}
void dae::GhostControllerComponent::Init()
{
	m_pGraph = GetGameObject()->GetComponentInParent<GraphComponent>();
	m_pTransform = GetGameObject()->GetTransform();
	m_Destination = m_pGraph->GetRandomNextPosition(m_pTransform->GetLocalPosition());
}

void dae::GhostControllerComponent::Update()
{
	const glm::vec2& localPos{ m_pTransform->GetLocalPosition() };
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
		m_Destination = m_pGraph->GetRandomNextPosition(m_pTransform->GetLocalPosition());
		std::cout << "Switch Direction\n";
		std::cout << "x: " << m_Destination.x << ", y: " << m_Destination.y << "\n";
		std::cout << "x: " << localPos.x << ", y: " << localPos.y << "\n";
	}
}
