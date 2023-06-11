#pragma once
#include "BaseComponent.h"
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "GraphComponent.h"
#include "PlayerEvents.h"
#include "Subject.h"
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

	class MapGeneratorComponent final : public BaseComponent, public Subject<PlayerEvent>
	{
	public:
		MapGeneratorComponent(GameObject* pGameObject);
		virtual ~MapGeneratorComponent() = default;
		MapGeneratorComponent(const MapGeneratorComponent& other) = delete;
		MapGeneratorComponent(MapGeneratorComponent&& other) noexcept = delete;
		MapGeneratorComponent& operator=(const MapGeneratorComponent& other) = delete;
		MapGeneratorComponent& operator=(MapGeneratorComponent&& other) noexcept = delete;


		const std::vector<glm::vec2>& GetPlayerSpawns() const;
		const std::vector<glm::vec2>& GetGhostSpawns() const;

		void LoadMap(int columns, int rows, int tileSize, const std::vector<unsigned char>& tileData, const std::vector<std::string>& textureFiles);
		void ReducePacdots();

	private:

		void ConnectNode(const std::vector<unsigned char>& tileData, size_t currentIdx, GraphComponent* pGraph, dae::Node* pNode, int width) const;

		int m_TotalPacDots{};

		int m_Columns{};
		int m_Rows{};
		int m_TileSize{};

		std::vector<glm::vec2> m_PlayerSpawns{};
		std::vector<glm::vec2> m_GhostSpawns{};
	};


}

