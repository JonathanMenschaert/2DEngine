#pragma once
#include "UpdateComponent.h"
namespace dae
{
	class TimerComponent : public UpdateComponent
	{
	public:
		TimerComponent(GameObject* pGameObject);
		~TimerComponent() = default;
		TimerComponent(const TimerComponent& other) = delete;
		TimerComponent(TimerComponent&& other) noexcept = delete;
		TimerComponent& operator=(const TimerComponent& other) = delete;
		TimerComponent& operator=(TimerComponent&& other) noexcept = delete;

		virtual void Update() override;
		void SetMaxTime(float time);

	protected:

		float m_MaxTime{};
		float m_Timer{};
		bool m_IsTimerActivated{ false };
	};
}
