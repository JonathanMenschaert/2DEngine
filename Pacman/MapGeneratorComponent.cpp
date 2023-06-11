#include "MapGeneratorComponent.h"
#include "GameObject.h"
#include "MapRenderComponent.h"
#include "RectCollisionComponent.h"
#include "TextureRenderComponent.h"
#include "PickupComponent.h"


dae::MapGeneratorComponent::MapGeneratorComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

const glm::vec2& dae::MapGeneratorComponent::GetPlayerSpawns() const
{
	return m_PlayerSpawns;
}

const std::vector<glm::vec2>& dae::MapGeneratorComponent::GetGhostSpawns() const
{
	return m_GhostSpawns;
}

void dae::MapGeneratorComponent::LoadMap(int columns, int rows, int tileSize, const std::vector<unsigned char>& tileData, const std::vector<std::string>& textureFiles)
{

	m_TileSize = tileSize;
	m_Columns = columns;
	m_Rows = rows;
	auto pGameObject{ GetGameObject() };
	
	auto pMapRenderer{ pGameObject->AddComponent<MapRenderComponent>() };
	pMapRenderer->SetMapData(tileSize, glm::vec2{ columns, rows }, tileData, textureFiles);
	
	auto pGraph{ pGameObject->AddComponent<GraphComponent>() };
	
	for (size_t idx{}; idx < tileData.size(); ++idx)
	{
		TileData data{ static_cast<TileData>(tileData[idx]) };
		const glm::vec2 relativePosition{ glm::vec2{ (idx % columns) * tileSize, (idx / columns) * tileSize } };

		switch (data)
		{
		//case TileData::PathCollision:
		case TileData::WallCollision:
			{
				auto pWallCollision = pGameObject->AddComponent<RectCollisionComponent>();
				pWallCollision->SetCollisionBox(glm::vec2{ tileSize, tileSize }, relativePosition);
				pWallCollision->SetCollisionType(CollisionType::StaticCollision);
				pWallCollision->SetLayers(std::vector<std::string>{ "player1", "player2", "enemy" });
			}
		break;
		case TileData::PowerPellet_AI:
		case TileData::PacDot_AI:
		{
			Node* pNode{ pGraph->CreateNode(relativePosition) };
			ConnectNode(tileData, idx, pGraph, pNode, 1);
			ConnectNode(tileData, idx, pGraph, pNode, -1);
			ConnectNode(tileData, idx, pGraph, pNode, columns);
			ConnectNode(tileData, idx, pGraph, pNode, -columns);
		}
		case TileData::PacDot:
		{
			//Pacdot:
			auto pacdotObj = std::make_shared<dae::GameObject>();
			auto pacdotCol = pacdotObj->AddComponent<dae::RectCollisionComponent>();
			pacdotCol->SetCollisionType(dae::CollisionType::Trigger);
			pacdotCol->SetCollisionBox(glm::vec2{ 11, 11 }, glm::vec2{ 2, 2 });
			pacdotCol->SetLayers(std::vector<std::string>{"player1", "player2"});
			auto pacdotTrans = pacdotObj->AddComponent<dae::TransformComponent>();
			pacdotTrans->SetLocalPosition(relativePosition);

			auto pacdotRender = pacdotObj->AddComponent<dae::TextureRenderComponent>();
			//pacdotRender->SetTexture("pacdot.png");

			auto pacDotPickup = pacdotObj->AddComponent<dae::PickupComponent>();
			if (data == TileData::PowerPellet_AI)
			{
				pacdotRender->SetTexture("powerpellet.png");
				pacDotPickup->SetType(PickupType::PowerPellet);
			}
			else
			{
				pacdotRender->SetTexture("pacdot.png");
			}

			pacdotObj->SetParent(pGameObject, false);
		}
		break;
		case TileData::PlayerSpawn:
			m_PlayerSpawns = relativePosition;
			break;	
		case TileData::GhostSpawn:
			m_GhostSpawns.emplace_back(relativePosition);
		case TileData::Path_AI:
		{
			Node* pNode{ pGraph->CreateNode(relativePosition) };
			ConnectNode(tileData, idx, pGraph, pNode, 1);
			ConnectNode(tileData, idx, pGraph, pNode, -1);
			ConnectNode(tileData, idx, pGraph, pNode, columns);
			ConnectNode(tileData, idx, pGraph, pNode, -columns);
		}
			break;
		default:
			break;
		}			
	}
}

void dae::MapGeneratorComponent::ConnectNode(const std::vector<unsigned char>& tileData, size_t idx, GraphComponent* pGraph, dae::Node* pNode, int offset) const
{
	//bool foundNode{ false };
	while (true)
	{	
		idx += offset;		
		if (idx >= tileData.size())
		{
			return;
		}

		switch (static_cast<TileData>(tileData[idx]))
		{
		case TileData::Wall:
		case TileData::WallCollision:
			idx = UINT16_MAX;
			break;
		case TileData::PacDot_AI:
		case TileData::PowerPellet_AI:
		case TileData::Path_AI:
		case TileData::GhostSpawn:
		{
			Node* pEndNode{ pGraph->CreateNode(glm::vec2{ (idx % m_Columns) * m_TileSize, (idx / m_Columns) * m_TileSize }) };
			pGraph->SetConnection(pNode, pEndNode, 0);
			return;
		}
		break;
		default:
			break;
			
		}
	}

	
}
