#include "PlayerComponent.h"
#include "GameObject.h"
#include "PickupComponent.h"
#include <iostream>
#include <ServiceLocator.h>
dae::PlayerComponent::PlayerComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
	, m_PacDotSoundIdx{UINT32_MAX}
	, m_PacDotSoundName{ "pacman_chomp" }
{
	ServiceLocator::GetSoundSystem().LoadSound(m_PacDotSoundName);
}

void dae::PlayerComponent::Notify(const Event<dae::CollisionData>& e)
{
	//This code should be moved to the pacdot gameobject
	CollisionData data{ e.GetPayload() };

	if (data.type != CollisionType::Trigger)
	{
		return;
	}

	auto pickup{ data.pGameObject->GetComponent<PickupComponent>() };

	if (pickup)
	{
		auto pos{ GetGameObject()->GetTransform()->GetWorldPosition()};
		
		data.pGameObject->Destroy();
		if (m_PacDotSoundIdx == UINT32_MAX)
		{
			m_PacDotSoundIdx = ServiceLocator::GetSoundSystem().FindSoundId(m_PacDotSoundName);
		}
		ServiceLocator::GetSoundSystem().Play(m_PacDotSoundIdx, 100);
	}	
}


