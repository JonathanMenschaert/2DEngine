#include "TextureRenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <iostream>

dae::TextureRenderComponent::TextureRenderComponent(GameObject* pGameObject)
	:RenderComponent(pGameObject)
{
}

void dae::TextureRenderComponent::Render() const
{
	if (!m_pTexture) return;
	
	if (!m_pTransform) return;

	const auto& translation{ m_pTransform->GetWorldPosition() };

	Renderer::GetInstance().RenderTexture(*m_pTexture, translation.x, translation.y);
}

void dae::TextureRenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}

void dae::TextureRenderComponent::SetTexture(const std::string& fileName)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(fileName);
}
