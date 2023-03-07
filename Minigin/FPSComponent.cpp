#include "FPSComponent.h"
#include "GameObject.h"
#include <sstream>
#include "Time.h"
#include <numeric>
#include <algorithm>
#include <functional>
#include <iostream>
dae::FPSComponent::FPSComponent(std::shared_ptr<GameObject> pGameObject)
	:UpdateComponent(pGameObject)
	,m_pTextComponent{}
	,m_MaxTimer{1.f}
{
	//Initializing updatetimer at almost the MaxTimer value to ensure 
	//the fps appear on screen instantly
	m_UpdateTimer = m_MaxTimer * 0.99f;
}

void dae::FPSComponent::Update()
{
	if (m_pTextComponent.expired())
	{
		m_pTextComponent = GetGameObject()->GetComponent<TextComponent>();
	}

	const float elapsedTime{ Time::GetInstance().GetElapsedTime() };
	m_UpdateTimer += elapsedTime;
	if (m_UpdateTimer >= m_MaxTimer)
	{
		const int fps{ static_cast<int>(1.f / elapsedTime) };
		m_FPSRollingAverage.push_back(fps);

		int containerSize{ static_cast<int>(m_FPSRollingAverage.size()) };
		if (containerSize > m_MaxStoredFPS)
		{
			m_FPSRollingAverage.pop_front();
		}

		int averageFps = std::accumulate(m_FPSRollingAverage.begin(), m_FPSRollingAverage.end(), 0) / containerSize;
		std::stringstream text{};

		text << averageFps << " FPS";

		m_pTextComponent.lock()->SetText(text.str());

		m_UpdateTimer -= m_MaxTimer;
	}
}

void dae::FPSComponent::SetUpdateTimer(float seconds)
{
	m_MaxTimer = seconds;
}
