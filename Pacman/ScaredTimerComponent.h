#pragma once
#include "UpdateComponent.h"
#include "Observer.h"
#include "PlayerEvents.h"
#include "Subject.h"

namespace dae
{
	class ScaredTimerComponent final : public UpdateComponent, public Observer<PlayerEvent>, public Subject<PlayerEvent>
	{
	public:
		ScaredTimerComponent(GameObject* pGameObject);
		~ScaredTimerComponent() = default;
		ScaredTimerComponent(const ScaredTimerComponent& other) = delete;
		ScaredTimerComponent(ScaredTimerComponent&& other) noexcept = delete;
		ScaredTimerComponent& operator=(const ScaredTimerComponent& other) = delete;
		ScaredTimerComponent& operator=(ScaredTimerComponent&& other) noexcept = delete;

		virtual void Update() override;

		void Notify(const Event<PlayerEvent>& e) override;
		void SetMaxTime(float time);
	private:

		float m_MaxTime{};
		float m_Timer{};
		bool m_IsTimerActivated{ false };
	};
}

