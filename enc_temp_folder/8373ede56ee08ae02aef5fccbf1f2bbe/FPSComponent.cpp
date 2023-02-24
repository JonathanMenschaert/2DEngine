#include "FPSComponent.h"
#include "GameObject.h"
#include <sstream>
#include "Time.h"

dae::FPSComponent::FPSComponent()
	:m_TextComponent{}
	,m_MaxTimer{1.f}
{
	//Initializing updatetimer at almost the MaxTimer value to ensure the fps appear 
	//on screen instantly
	m_UpdateTimer = m_MaxTimer * 0.99f;
}

void dae::FPSComponent::Update()
{
	if (m_TextComponent.expired())
	{
		m_TextComponent = m_GameObject.lock()->GetComponent<TextComponent>();
	}

	const float elapsedTime{ Time::GetInstance().GetElapsedTime() };
	m_UpdateTimer += elapsedTime;
	if (m_UpdateTimer >= m_MaxTimer)
	{
		const int fps{ static_cast<int>(1.f / elapsedTime) };
		std::stringstream text{};
		text << fps << " FPS";

		m_TextComponent.lock()->SetText(text.str());

		m_UpdateTimer -= m_MaxTimer;
	}
}

void dae::FPSComponent::SetUpdateTimer(float seconds)
{
	m_MaxTimer = seconds;
}
