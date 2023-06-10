#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"
#include "PlayerEvents.h"
namespace dae
{
	class ScoreDisplayComponent : public BaseComponent, public Observer<PlayerEvent>
	{
	public:
		ScoreDisplayComponent(GameObject* pGameObject);
		~ScoreDisplayComponent() = default;
		ScoreDisplayComponent(const ScoreDisplayComponent& rectComponent) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& rectComponent) noexcept = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& rectComponent) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& rectComponent) noexcept = delete;

		void Init() override;
		void Notify(const Event<PlayerEvent>& e) override;

	private:
		TextComponent* m_pText;
	};
}

