#include "TransformComponent.h"

void dae::TransformComponent::SetTranslation(const glm::vec2& translation)
{
	m_Translation = translation;
}

const glm::vec2& dae::TransformComponent::GetTranslation()
{
	return m_Translation;
}
