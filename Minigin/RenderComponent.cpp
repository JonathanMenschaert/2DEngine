#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <iostream>

dae::RenderComponent::RenderComponent(GameObject* pGameObject)
	:BaseComponent(pGameObject)
{
}

void dae::RenderComponent::Init()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}

void dae::RenderComponent::Render() const
{
	if (!m_pTexture) return;
	
	if (!m_pTransform) return;

	const auto& translation{ m_pTransform->GetWorldPosition() };

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
