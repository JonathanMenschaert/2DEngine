#include "FPSComponent.h"
#include "GameObject.h"
#include <sstream>
#include "Time.h"

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
		std::stringstream text{};
		text << fps << " FPS";

		m_pTextComponent.lock()->SetText(text.str());

		m_UpdateTimer -= m_MaxTimer;
	}
}

void dae::FPSComponent::SetUpdateTimer(float seconds)
{
	m_MaxTimer = seconds;
}
