#include "TransformComponent.h"

dae::TransformComponent::TransformComponent(std::shared_ptr<GameObject> pGameObject)
	:BaseComponent(pGameObject)
{
}

void dae::TransformComponent::SetTranslation(const glm::vec2& translation)
{
	m_Translation = translation;
}

const glm::vec2& dae::TransformComponent::GetTranslation()
{
	return m_Translation;
}
