#include "BaseComponent.h"

namespace dae
{
	BaseComponent::BaseComponent(GameObject* pGameObject)
		:m_pGameObject{pGameObject}
	{
	}

	GameObject* BaseComponent::GetGameObject() const
	{
		return m_pGameObject;
	}

	void BaseComponent::Init()
	{
	}

	void BaseComponent::Update()
	{
	}

	void BaseComponent::Render() const
	{
	}
	void BaseComponent::OnGui()
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
