#include "MapRenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "MapGeneratorComponent.h"
dae::MapRenderComponent::MapRenderComponent(GameObject* pGameObject)
	:RenderComponent{pGameObject}
{
}

void dae::MapRenderComponent::Render() const
{
	const auto& translation{ m_pTransform->GetWorldPosition() };

	for (size_t idx{}; idx < m_TileData.size(); ++idx)
	{
		//glm::vec2{ (idx % width) * tileSize + halfSize, (idx / width) * tileSize + halfSize }
		TileData tileData{ static_cast<TileData>(m_TileData[idx]) };
		std::shared_ptr<Texture2D> texture{};
		switch(tileData)
		{
		case TileData::Wall:
		case TileData::WallCollision:
			texture = m_Textures[0];
			break;
		case TileData::Path:
		case TileData::PathCollision:
		case TileData::PacDot:
		case TileData::PowerPellet:
			texture = m_Textures[1];
			break;
		default:
			continue;
		}
		Renderer::GetInstance().RenderTexture(*texture,
				static_cast<float>(idx % static_cast<size_t>(m_Dimensions.x) * m_TileSize) + translation.x,
				static_cast<float>(idx / static_cast<size_t>(m_Dimensions.x) * m_TileSize) + translation.y);
	}
}

void dae::MapRenderComponent::SetMapData(int tileSize, const glm::vec2& dimensions, const std::vector<int>& tileData, const std::vector<std::string>& textureFiles)
{
	m_TileSize = tileSize;
	m_Dimensions = dimensions;
	m_TileData = tileData;


	for (const auto& file : textureFiles)
	{
		m_Textures.emplace_back(ResourceManager::GetInstance().LoadTexture(file));
	}
}
