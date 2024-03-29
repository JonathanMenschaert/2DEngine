#include "HighScoreComponent.h"
#include "LetterScrollButtonComponent.h"
#include "GameObject.h"
#include <iostream>

dae::HighScoreComponent::HighScoreComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
	,m_Path{"Data/highscores.hs"}
	,m_MaxEntries{10}
{
}

void dae::HighScoreComponent::Init()
{
	m_HighScores = HighScoreIO::LoadHighScoreTable(m_Path);
	if (static_cast<int>(m_HighScores.size()) < m_MaxEntries)
	{
		HighScoreData filler{"___", 0, 0};

		while (static_cast<int>(m_HighScores.size()) < m_MaxEntries)
		{
			m_HighScores.emplace_back(filler);
		}
		HighScoreIO::SaveHighScores(m_HighScores, m_Path);
	}
}

void dae::HighScoreComponent::SetLevel(int level)
{
	m_CurrentData.level = level;
}

int dae::HighScoreComponent::GetLives() const
{
	return m_Lives;
}

int dae::HighScoreComponent::GetScore() const
{
	return m_CurrentData.score;
}

bool dae::HighScoreComponent::CanSaveHighScore() const
{
	for (const auto& highScoreData : m_HighScores)
	{
		if (highScoreData.score < m_CurrentData.score)
		{
			return true;
		}
	}

	return false;
}

void dae::HighScoreComponent::SaveHighScore()
{
	const std::vector<LetterScrollButtonComponent*> letters {GetGameObject()->GetComponentsInChildren<LetterScrollButtonComponent>()};

	if (letters.size() >= m_CurrentData.nameSize - 1)
	{
		for (size_t idx{}; idx < m_CurrentData.nameSize - 1; ++idx)
		{
			m_CurrentData.name[idx] = letters[idx]->GetButtonText().c_str()[0];
		}		
	}

	size_t insertIdx{ m_HighScores.size() };
	
	for (size_t idx{}; idx < m_HighScores.size(); ++idx)
	{
		if (m_HighScores[idx].score <= m_CurrentData.score)
		{
			insertIdx = idx;
			break;
		}
	}

	m_HighScores.insert(m_HighScores.begin() + insertIdx, m_CurrentData);
	m_HighScores.pop_back();

	HighScoreIO::SaveHighScores(m_HighScores, m_Path);
}

void dae::HighScoreComponent::SetScore(int score)
{
	m_CurrentData.score = score;
}

void dae::HighScoreComponent::SetLives(int lives)
{
	m_Lives = lives;
}

void dae::HighScoreComponent::Notify(const Event<int>& e)
{
	m_Lives = e.GetPayload();
}

void dae::HighScoreComponent::Notify(const Event<unsigned int>& e)
{
	m_CurrentData.score = static_cast<int>(e.GetPayload());
}


