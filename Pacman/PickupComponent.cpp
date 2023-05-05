#include "PickupComponent.h"

dae::PickupComponent::PickupComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

void dae::PickupComponent::SetPoints(int points)
{
	m_Points = points;
}

int dae::PickupComponent::GetPoints() const
{
	return m_Points;
}
