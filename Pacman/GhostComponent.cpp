#include "GhostComponent.h"
#include "GameObject.h"
dae::GhostComponent::GhostComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

void dae::GhostComponent::Init()
{
	m_pTextureRenderer = GetGameObject()->GetComponent<TextureRenderComponent>();
	if (!m_pTextureRenderer)
	{
		m_pTextureRenderer = GetGameObject()->AddComponent<TextureRenderComponent>();
	}
	if (m_pNormalTexture)
	{
		m_pTextureRenderer->SetTexture(m_pNormalTexture);
	}
}

void dae::GhostComponent::SetSpawnPos(const glm::vec2& pos)
{
	m_SpawnPos = pos;
}

void dae::GhostComponent::SetNormalTexture(std::shared_ptr<Texture2D>& pNormalTexture)
{
	m_pNormalTexture = pNormalTexture;
}

void dae::GhostComponent::SetScaredTexture(std::shared_ptr<Texture2D>& pScaredTexture)
{
	m_pScaredTexture = pScaredTexture;
}

void dae::GhostComponent::SetScared(bool isScared)
{
	m_IsScared = isScared;

	if (isScared)
	{
		if (m_pScaredTexture)
		{
			m_pTextureRenderer->SetTexture(m_pScaredTexture);
		}
	}
	else
	{
		if (m_pNormalTexture)
		{
			m_pTextureRenderer->SetTexture(m_pNormalTexture);
		}
	}
}

bool dae::GhostComponent::IsScared() const
{
	return m_IsScared;
}
