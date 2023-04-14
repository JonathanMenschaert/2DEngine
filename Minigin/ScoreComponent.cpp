#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(std::shared_ptr<GameObject> pGameObject)
	:BaseComponent(pGameObject)
	,m_Score{0}
{
}

void dae::ScoreComponent::AddScore(int score)
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
	Event<int> e{ "ScoreChangedEvent", m_Score };
	NotifyObservers(e);
}

int dae::ScoreComponent::GetScore() const
{
	return m_Score;
}
