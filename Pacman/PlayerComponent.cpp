#include "PlayerComponent.h"
#include "GameObject.h"
#include "PickupComponent.h"
#include <iostream>
dae::PlayerComponent::PlayerComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

void dae::PlayerComponent::Notify(const Event<dae::CollisionData>& e)
{
	CollisionData data{ e.GetPayload() };

	if (data.type != CollisionType::Trigger)
	{
		return;
	}

	auto pickup{ data.pGameObject->GetComponent<PickupComponent>() };

	if (pickup)
	{
		auto pos{ GetGameObject()->GetTransform()->GetWorldPosition()};
		//add score
		//std::cout << "Triggered! :" << pos.x << ", " << pos.y << "\n";
		data.pGameObject->Destroy();
		
	}
	//
}


