#include "ScoreComponent.h"
#include "Achievement.h"

dae::ScoreComponent::ScoreComponent(GameObject* pGameObject)
	:BaseComponent(pGameObject)
	,m_Score{0}
{
}

void dae::ScoreComponent::AddScore(unsigned int score)
{
	m_Score += score;
	if (m_Score < 0)
	{
		m_Score = 0;
	}
	UpdateScore();
}

void dae::ScoreComponent::UpdateScore()
{
	Event<unsigned int> e{ m_Score };
	NotifyObservers(e);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}

void dae::ScoreComponent::Notify(const Event<PlayerEvent>& e)
{
	switch (e.GetPayload())
	{
	case PlayerEvent::GhostKilled:
		AddScore(m_GhostKillScore);
		m_GhostKillScore *= 2;
		break;
	case PlayerEvent::PowerpelletCollected:
		AddScore(50);
		break;
	case PlayerEvent::PacdotCollected:
		AddScore(10);
		break;
	case PlayerEvent::PowerpelletTimeout:
		m_GhostKillScore = 200;
	}
}
