#include "ButtonGroupComponent.h"
#include "GameObject.h"
#include "glm/geometric.hpp"
dae::ButtonGroupComponent::ButtonGroupComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
	,m_SelectedButtonIdx{0}
{
}

void dae::ButtonGroupComponent::Init()
{
	m_Buttons = GetGameObject()->GetComponentsInChildren<ButtonComponent>();
	if (m_Buttons.size() > 0)
	{
		m_Buttons[m_SelectedButtonIdx]->SetSelected(true);
	}
}

void dae::ButtonGroupComponent::PressSelectedButton()
{
	for (auto& button : m_Buttons)
	{
		button->OnClick();
	}
}

void dae::ButtonGroupComponent::NavigateToClosestButton(const glm::vec2& direction)
{
	size_t closestIdx{ 0 };
	float closestDistance{ FLT_MAX };

	glm::vec2 posWithOffset{m_Buttons[m_SelectedButtonIdx]->GetButtonPos() + direction};

	for (size_t idx{}; idx < m_Buttons.size(); ++idx)
	{
		if (idx == m_SelectedButtonIdx)
		{
			continue;
		}

		const glm::vec2& nextButton {m_Buttons[idx]->GetButtonPos()};
		const float distance{ glm::length(nextButton - posWithOffset) };
		if (distance < closestDistance)
		{
			closestIdx = idx;
			closestDistance = distance;
		}
	}
	m_Buttons[m_SelectedButtonIdx]->SetSelected(false);
	m_SelectedButtonIdx = closestIdx;
	m_Buttons[m_SelectedButtonIdx]->SetSelected(true);
}

void dae::ButtonGroupComponent::NavigateToButtonAtPos(const glm::vec2& pos)
{
	for (size_t idx{}; idx < m_Buttons.size(); ++idx)
	{
		if (idx == m_SelectedButtonIdx)
		{
			continue;
		}
		if (m_Buttons[idx]->IsPointOnButton(pos))
		{
			m_Buttons[m_SelectedButtonIdx]->SetSelected(false);
			m_SelectedButtonIdx = idx;
			m_Buttons[m_SelectedButtonIdx]->SetSelected(true);
			break;
		}
	}
}

