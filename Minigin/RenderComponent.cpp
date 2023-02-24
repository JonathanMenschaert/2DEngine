#include "RenderComponent.h"
#include "GameObject.h"
#include "Renderer.h"

#include <glm/glm.hpp>

void dae::RenderComponent::Render() const
{
	if (!m_Texture) return;
	auto transform{ m_GameObject.lock()->GetComponent<TransformComponent>() };
	if (transform.expired()) return;

	auto translation{ transform.lock()->GetTranslation() };

	Renderer::GetInstance().RenderTexture(*m_Texture, translation.x, translation.y);
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}
