#include "FPSComponent.h"
#include "GameObject.h"
#include <sstream>
#include "Time.h"

void dae::FPSComponent::Update()
{
	if (m_TextComponent.expired())
	{
		m_TextComponent = m_GameObject.lock()->GetComponent<TextComponent>();
	}

	const int fps{ static_cast<int>(1.f / Time::GetInstance().GetElapsedTime()) };
	std::stringstream text{};
	text << fps << " FPS";

	m_TextComponent.lock()->SetText(text.str());
}

void dae::FPSComponent::SetUpdateTimer(float seconds)
{
	m_MaxTimer = seconds;
}
