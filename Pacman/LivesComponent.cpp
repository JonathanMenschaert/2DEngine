#include "LivesComponent.h"

dae::LivesComponent::LivesComponent(GameObject* pGameObject)
	:BaseComponent{ pGameObject }
	,m_Lives{0}
{
}

void dae::LivesComponent::Notify(const Event<PlayerEvent>& e)
{
	switch (e.GetPayload())
	{
	case PlayerEvent::PacmanLiveLost:
		AddLife(-1);
	default:
		break;
	}
}

void dae::LivesComponent::AddLife(int lives)
{
	m_Lives += lives;
	if (m_Lives < 0)
	{
		m_Lives = 0;
	}
	UpdateLives();
}

void dae::LivesComponent::UpdateLives()
{
	Event<int> e{ m_Lives };
	NotifyObservers(e);
}

int dae::LivesComponent::GetLives() const
{
	return m_Lives;
}


