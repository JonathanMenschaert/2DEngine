#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
{
}

void dae::TransformComponent::SetTranslation(const glm::vec2& translation)
{
	m_Translation = translation;
}

glm::vec2& dae::TransformComponent::GetTranslation()
{
	return m_Translation;
}
