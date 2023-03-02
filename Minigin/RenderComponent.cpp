#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <iostream>

dae::RenderComponent::RenderComponent(std::shared_ptr<GameObject> pGameObject)
	:BaseComponent(pGameObject)
{
}

void dae::RenderComponent::Render() const
{
	if (!m_pTexture) return;
	auto pTransform{ GetGameObject()->GetComponent<TransformComponent>()};
	if (pTransform.expired()) return;

	const auto& translation{ pTransform.lock()->GetWorldPosition() };

	Renderer::GetInstance().RenderTexture(*m_pTexture, translation.x, translation.y);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void dae::RenderComponent::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}
