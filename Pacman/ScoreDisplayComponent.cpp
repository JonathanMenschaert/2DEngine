#include "ScoreDisplayComponent.h"
#include "Gameobject.h"
#include <sstream>

dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pGameObject)
	:BaseComponent(pGameObject)
	,m_pText{nullptr}
{
}

void dae::ScoreDisplayComponent::Init()
{
	m_pText = GetGameObject()->GetComponent<TextComponent>();
}

void dae::ScoreDisplayComponent::Notify(const Event<unsigned int>& e)
{
	std::stringstream text{};

	text << "Score: " << e.GetPayload();
	m_pText->SetText(text.str());
}
