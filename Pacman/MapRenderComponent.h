#pragma once
#include "RenderComponent.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include "Texture2D.h"

namespace dae
{
	class MapRenderComponent final : public RenderComponent
	{
	public:
		MapRenderComponent(GameObject* pGameObject);
		virtual ~MapRenderComponent() = default;
		MapRenderComponent(const MapRenderComponent& component) = delete;
		MapRenderComponent(MapRenderComponent&& component) noexcept = delete;
		MapRenderComponent& operator=(const MapRenderComponent& component) = delete;
		MapRenderComponent& operator=(MapRenderComponent&& component) noexcept = delete;

		void Render() const override;

		void SetMapData(int tileSize, const glm::vec2& dimensions, const std::vector<int>& tileData, const std::vector<std::string>& textureFiles);
	private:

		glm::vec2 m_Dimensions{};
		std::vector<std::shared_ptr<Texture2D>> m_Textures{};
		std::vector<int> m_TileData{};
		int m_TileSize{};

	};
}

