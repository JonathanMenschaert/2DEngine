#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <iostream>

void dae::RenderComponent::Render() const
{
	if (!m_Texture) return;
	auto transform{ m_GameObject.lock()->GetComponent<TransformComponent>() };
	if (transform.expired()) return;

	const auto translation{ transform.lock()->GetTranslation() };

	Renderer::GetInstance().RenderTexture(*m_Texture, translation.x, translation.y);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}

void dae::RenderComponent::SetTexture(const std::string& fileName)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
}
