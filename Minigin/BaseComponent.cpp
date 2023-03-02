#include "BaseComponent.h"

namespace dae
{
	BaseComponent::BaseComponent(std::shared_ptr<GameObject> pGameObject)
		:m_pGameObject{pGameObject}
	{
	}

	std::shared_ptr<GameObject> BaseComponent::GetGameObject() const
	{
		return m_pGameObject.lock();
	}

	/*void BaseComponent::SetParent(std::weak_ptr<GameObject> pGameObject)
	{
		m_pGameObject = pGameObject;
	}*/

	void BaseComponent::Init()
	{
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
