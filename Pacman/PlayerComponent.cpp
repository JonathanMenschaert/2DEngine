#include "PlayerComponent.h"
#include "GameObject.h"
#include "PickupComponent.h"
#include <iostream>
#include <ServiceLocator.h>
#include "GhostComponent.h"
dae::PlayerComponent::PlayerComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
	, m_PacDotSoundIdx{UINT32_MAX}
	, m_PacDotSoundName{ "pacman_chomp" }
	,m_DeathSoundIdx{UINT32_MAX}
	, m_DeathSoundName{"pacman_death"}
	,m_EatGhostSoundIdx{UINT32_MAX}
	,m_EatGhostSoundName{"pacman_eatghost"}
	,m_SpawnPos{}
{
	ServiceLocator::GetSoundSystem().LoadSound(m_PacDotSoundName);
	ServiceLocator::GetSoundSystem().LoadSound(m_DeathSoundName);
	ServiceLocator::GetSoundSystem().LoadSound(m_EatGhostSoundName);
}

void dae::PlayerComponent::Notify(const Event<dae::CollisionData>& e)
{
	const CollisionData& data{ e.GetPayload() };

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
		if (pickup->GetType() == PickupType::Pacdot)
		{
			Event<PlayerEvent> pacDotEvent {PlayerEvent::PacdotCollected};
			NotifyObservers(pacDotEvent);
		}
		else
		{
			Event<PlayerEvent> powerPelletEvent {PlayerEvent::PowerpelletCollected};
			NotifyObservers(powerPelletEvent);
		}
		
		ServiceLocator::GetSoundSystem().Play(m_PacDotSoundIdx, 100);
	}	

	auto ghost{ data.pGameObject->GetComponent<GhostComponent>() };

	if (ghost)
	{
		if (ghost->IsScared())
		{
			Event<PlayerEvent> ghostKillEvent {PlayerEvent::GhostKilled};
			NotifyObservers(ghostKillEvent);
			if (m_EatGhostSoundIdx == UINT32_MAX)
			{
				m_EatGhostSoundIdx = ServiceLocator::GetSoundSystem().FindSoundId(m_EatGhostSoundName);
			}
			ServiceLocator::GetSoundSystem().Play(m_EatGhostSoundIdx, 100);
		}
		else
		{
			Event<PlayerEvent> pacmanDiedEvent {PlayerEvent::GhostKilled};
			NotifyObservers(pacmanDiedEvent);
			if (m_DeathSoundIdx == UINT32_MAX)
			{
				m_DeathSoundIdx = ServiceLocator::GetSoundSystem().FindSoundId(m_DeathSoundName);
			}
			ServiceLocator::GetSoundSystem().Play(m_DeathSoundIdx, 100);
		}
	}
}

void dae::PlayerComponent::SetSpawnPos(const glm::vec2& spawnPos)
{
	m_SpawnPos = spawnPos;
}


