#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "PlayerEvents.h"
#include "Observer.h"

namespace dae
{
	class ScoreComponent final : public BaseComponent, public Subject<unsigned int>, public Observer<PlayerEvent>
	{
	public:
		ScoreComponent(GameObject* pGameObject);
		virtual ~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& rectComponent) = delete;
		ScoreComponent(ScoreComponent&& rectComponent) noexcept = delete;
		ScoreComponent& operator=(const ScoreComponent& rectComponent) = delete;
		ScoreComponent& operator=(ScoreComponent&& rectComponent) noexcept = delete;

		void AddScore(unsigned int score = 1);
		void UpdateScore();
		int GetScore() const;
		virtual void Notify(const Event<PlayerEvent>& e) override;

	private:
		unsigned int m_Score;
	};
}

