#include "PickupComponent.h"
#include "MapGeneratorComponent.h"
dae::PickupComponent::PickupComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
	,m_pMap{nullptr}
{
}

dae::PickupComponent::~PickupComponent()
{
	if (m_pMap)
	{
		m_pMap->ReducePacdots();
	}
}

void dae::PickupComponent::SetType(PickupType type)
{
	m_PickupType = type;
}

void dae::PickupComponent::SetMap(MapGeneratorComponent* pMap)
{
	m_pMap = pMap;
}

dae::PickupType dae::PickupComponent::GetType() const
{
	return m_PickupType;
}

