#include "LivesDisplayComponent.h"
#include "GameObject.h"
#include <sstream>
dae::LivesDisplayComponent::LivesDisplayComponent(std::shared_ptr<GameObject> pGameObject)
	:BaseComponent(pGameObject)
	,m_pText{nullptr}
{
}

void dae::LivesDisplayComponent::Init()
{
	m_pText = GetGameObject()->GetComponent<TextComponent>().lock().get();
}

void dae::LivesDisplayComponent::Notify(const Event<int>& e)
{
	std::stringstream text{};

	text << "Lives: " << e.GetPayload();
	m_pText->SetText(text.str());
}
