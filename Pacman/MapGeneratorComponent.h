#pragma once
#include "BaseComponent.h"
#include <vector>
#include <string>
namespace dae
{

	enum class TileData
	{
		Wall = 0,
		Path = 1,
		WallCollision = 2,
		PathCollision = 3,
		PacDot = 4,
		PowerPellet = 5
	};

	class MapGeneratorComponent final : public BaseComponent
	{
	public:
		MapGeneratorComponent(GameObject* pGameObject);
		virtual ~MapGeneratorComponent() = default;
		MapGeneratorComponent(const MapGeneratorComponent& rectComponent) = delete;
		MapGeneratorComponent(MapGeneratorComponent&& rectComponent) noexcept = delete;
		MapGeneratorComponent& operator=(const MapGeneratorComponent& rectComponent) = delete;
		MapGeneratorComponent& operator=(MapGeneratorComponent&& rectComponent) noexcept = delete;

		void LoadMap(int width, int height, int tileSize, const std::vector<int>& tileData, const std::vector<std::string>& textureFiles);
	};


}

