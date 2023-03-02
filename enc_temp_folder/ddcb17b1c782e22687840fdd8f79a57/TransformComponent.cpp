#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(std::shared_ptr<GameObject> pGameObject)
	:BaseComponent(pGameObject)
{
}

void dae::TransformComponent::Init()
{
	m_Magnitude = glm::length(m_LocalPosition);
}

void dae::TransformComponent::SetLocalPosition(const glm::vec2& position)
{
	SetLocalPosition(glm::vec3{ position.x, position.y, 0.f });
}

void dae::TransformComponent::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
	m_NeedsUpdate = true;

	for (auto& child : GetGameObject()->GetChildren())
	{
		child.lock()->GetComponent<TransformComponent>().lock()->SetFlagDirty();
	}
}

const glm::vec3& dae::TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_NeedsUpdate)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}

float dae::TransformComponent::GetDistanceToParent() const
{
	return m_Magnitude;
}

void dae::TransformComponent::SetFlagDirty()
{
	m_NeedsUpdate = true;
}

void dae::TransformComponent::UpdateWorldPosition()
{
	std::shared_ptr<GameObject> pParentObj{ GetGameObject()->GetParent()};


	if (!pParentObj)
	{
		m_WorldPosition = m_LocalPosition;
	}
	else
	{
		m_WorldPosition = pParentObj->GetComponent<TransformComponent>().lock()->GetWorldPosition() + m_LocalPosition;
	}
	m_Magnitude = glm::length(m_LocalPosition);
	m_NeedsUpdate = false;
}
