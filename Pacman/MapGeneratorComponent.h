#pragma once
#include "BaseComponent.h"
#include <vector>
#include <string>
#include "glm/glm.hpp"
namespace dae
{

	enum class TileData
	{
		Wall = 0,
		Path = 1,
		WallCollision = 2,
		Path_AI = 3,
		PacDot = 4,
		PowerPellet_AI = 5,
		PacDot_AI = 6,
		PlayerSpawn = 7,
		GhostSpawn = 8
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


		const glm::vec2& GetPlayerSpawns() const;
		const std::vector<glm::vec2>& GetGhostSpawns() const;

		void LoadMap(int width, int height, int tileSize, const std::vector<int>& tileData, const std::vector<std::string>& textureFiles);

	private:
		glm::vec2 m_PlayerSpawns{};
		std::vector<glm::vec2> m_GhostSpawns{};
	};


}

