#include "ButtonComponent.h"
#include "GameObject.h"

dae::ButtonComponent::ButtonComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
	,m_IsSelected{false}
	,m_Extend{}
	,m_HighlightColor{}
	,m_NormalColor{}
	,m_pButtonText{ pGameObject->AddComponent<TextComponent>() }
{
}

void dae::ButtonComponent::SetButtonText(const std::string& text)
{
	if (m_pButtonText)
	{
		m_pButtonText->SetText(text);
	}
}

void dae::ButtonComponent::SetButtonFont(const std::shared_ptr<Font> pFont)
{
	if (m_pButtonText)
	{
		m_pButtonText->SetFont(pFont);
	}
}

void dae::ButtonComponent::SetNormalColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_NormalColor = SDL_Color{ r, g, b, a };
}

void dae::ButtonComponent::SetHighlightColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_HighlightColor = SDL_Color{ r, g, b, a };
}

void dae::ButtonComponent::SetSelected(bool selected)
{
	m_IsSelected = selected;
	if (m_pButtonText)
	{
		m_pButtonText->SetColor((selected ? m_HighlightColor : m_NormalColor));
	}
}

void dae::ButtonComponent::SetOnClick(const std::function<void()>& onClick)
{
	m_OnClick = onClick;
}

void dae::ButtonComponent::SetButtonExtend(const glm::vec2& extend)
{
	m_Extend = extend;
}

void dae::ButtonComponent::OnClick() const
{
	if (m_IsSelected)
	{
		m_OnClick();
	}
}

bool dae::ButtonComponent::IsPointOnButton(const glm::vec2& point) const
{
	const glm::vec2& pos {m_pTransform->GetWorldPosition()};

	return point.x > pos.x - m_Extend.x && point.x < pos.x + m_Extend.x &&
		point.y > pos.y - m_Extend.y && point.y < pos.y + m_Extend.y;
}

void dae::ButtonComponent::Init()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
	SetSelected(m_IsSelected);
}

const glm::vec2& dae::ButtonComponent::GetButtonPos() const
{
	return m_pTransform->GetWorldPosition();
}
