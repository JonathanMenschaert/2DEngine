#include "PickupComponent.h"

dae::PickupComponent::PickupComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

void dae::PickupComponent::SetType(PickupType type)
{
	m_PickupType = type;
}

dae::PickupType dae::PickupComponent::GetType() const
{
	return m_PickupType;
}

