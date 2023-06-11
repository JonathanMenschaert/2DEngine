#include "ScaredTimerComponent.h"
#include "GameTime.h"

dae::ScaredTimerComponent::ScaredTimerComponent(GameObject* pGameObject)
	:TimerComponent{pGameObject}
{
}

void dae::ScaredTimerComponent::Update()
{
	if (m_IsTimerActivated)
	{
		m_Timer -= GameTime::GetInstance().GetElapsedTime();
		if (m_Timer <= 0.f)
		{
			m_Timer = 0.f;
			m_IsTimerActivated = false;
			const Event<PlayerEvent> timerFinishedEvent{PlayerEvent::PowerpelletTimeout};
			NotifyObservers(timerFinishedEvent);
		}
	}
}

void dae::ScaredTimerComponent::Notify(const Event<PlayerEvent>& e)
{
	switch (e.GetPayload())
	{
	case PlayerEvent::PowerpelletCollected:
		m_Timer = m_MaxTime;
		m_IsTimerActivated = true;
	default:
		break;
	}
}

