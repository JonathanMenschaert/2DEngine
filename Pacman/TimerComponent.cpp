#include "TimerComponent.h"
#include "GameTime.h"
dae::TimerComponent::TimerComponent(GameObject* pGameObject)
	:UpdateComponent{pGameObject}
	, m_MaxTime{ 6.f }
{
}
void dae::TimerComponent::Update()
{
	if (m_IsTimerActivated)
	{
		m_Timer -= GameTime::GetInstance().GetElapsedTime();
		if (m_Timer <= 0.f)
		{
			m_Timer = 0.f;
			m_IsTimerActivated = false;
		}
	}
}

void dae::TimerComponent::SetMaxTime(float time)
{
	m_MaxTime = time;
}
