#pragma once
#include "TimerComponent.h"
#include "Observer.h"
#include "PlayerEvents.h"
#include "Subject.h"

namespace dae
{
	class ScaredTimerComponent final : public TimerComponent, public Observer<PlayerEvent>, public Subject<PlayerEvent>
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
	};
}

