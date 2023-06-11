#pragma once
#include "BaseComponent.h"
#include "HighScoreIO.h"

namespace dae
{
	class HighScoreComponent final : public BaseComponent
	{
	public:
		HighScoreComponent(GameObject* pGameObject);
		~HighScoreComponent() = default;
		HighScoreComponent(const HighScoreComponent& other) = delete;
		HighScoreComponent(HighScoreComponent&& other) noexcept = delete;
		HighScoreComponent& operator=(const HighScoreComponent& other) = delete;
		HighScoreComponent& operator=(HighScoreComponent&& other) noexcept = delete;

		void Init() override;
		void SetLevel(int level);
		int GetLives() const;
		int GetScore() const;

		bool CanSaveHighScore() const;
		void SaveHighScore();
		void SetLives(int lives);
		

	private:

		void SetScore(int score);

		const std::string m_Path;
		std::vector<HighScoreData> m_HighScores{};
		HighScoreData m_CurrentData{};
		int m_Lives{};
		int m_MaxEntries{};
	};
}

