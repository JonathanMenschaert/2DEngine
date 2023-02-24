#include "BaseComponent.h"

namespace dae
{
	BaseComponent::BaseComponent()
	{
	}

	void BaseComponent::SetParent(std::weak_ptr<GameObject> pGameObject)
	{
		m_GameObject = pGameObject;
	}

	void BaseComponent::Update()
	{
	}

	void BaseComponent::Render() const
	{
	}
	void BaseComponent::MarkForDeath()
	{
		m_Alive = false;
	}
	bool BaseComponent::IsMarkedForDeath()
	{
		return m_Alive;
	}
}
