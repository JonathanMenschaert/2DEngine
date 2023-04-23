#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(GameObject* pGameObject)
	:BaseComponent{ pGameObject }
{
}

void dae::TransformComponent::Init()
{
	m_Magnitude = glm::length(m_LocalPosition);
}

void dae::TransformComponent::SetLocalPosition(const glm::vec2& position)
{
	m_LocalPosition = position;
	m_NeedsUpdate = true;

	//Propagate dirty flag down to children
	for (auto& child : GetGameObject()->GetChildren())
	{
		child->GetComponent<TransformComponent>()->SetFlagDirty();
	}
}

void dae::TransformComponent::Translate(const glm::vec2& offset)
{
	SetLocalPosition(m_LocalPosition + offset);
}

const glm::vec2& dae::TransformComponent::GetLocalPosition() const
{
	return m_LocalPosition;
}

const glm::vec2& dae::TransformComponent::GetWorldPosition()
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
		m_WorldPosition = pParentObj->GetComponent<TransformComponent>()->GetWorldPosition() + m_LocalPosition;
	}
	m_Magnitude = glm::length(m_LocalPosition);
	m_NeedsUpdate = false;
}
