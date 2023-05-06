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

void dae::MapGeneratorComponent::LoadMap(int width, int height, int tileSize, const std::vector<int>& tileData, const std::vector<std::string>& textureFiles)
{
	auto pGameObject{ GetGameObject() };
	
	auto pMapRenderer = pGameObject->AddComponent<MapRenderComponent>();
	pMapRenderer->SetMapData(tileSize, glm::vec2{ width, height }, tileData, textureFiles);
	

	
	for (size_t idx{}; idx < tileData.size(); ++idx)
	{
		TileData data{ static_cast<TileData>(tileData[idx]) };

		switch (data)
		{
		//case TileData::PathCollision:
		case TileData::WallCollision:
			{
				auto pWallCollision = pGameObject->AddComponent<RectCollisionComponent>();
				pWallCollision->SetCollisionBox(glm::vec2{ tileSize, tileSize }, glm::vec2{ (idx % width) * tileSize, (idx / width) * tileSize });
				pWallCollision->SetCollisionType(CollisionType::StaticCollision);
				pWallCollision->SetLayers(std::vector<std::string>{ "player1", "player2" });
			}
		break;
		case TileData::PacDot:
		{
			//Pacdot
			auto pacdotObj = std::make_shared<dae::GameObject>();
			auto pacdotCol = pacdotObj->AddComponent<dae::RectCollisionComponent>();
			pacdotCol->SetCollisionType(dae::CollisionType::Trigger);
			pacdotCol->SetCollisionBox(glm::vec2{ 11, 11 }, glm::vec2{ 2, 2 });
			pacdotCol->SetLayers(std::vector<std::string>{"player1", "player2"});
			auto pacdotTrans = pacdotObj->AddComponent<dae::TransformComponent>();
			pacdotTrans->SetLocalPosition(glm::vec2{ (idx % width) * tileSize, (idx / width) * tileSize });

			auto pacdotRender = pacdotObj->AddComponent<dae::TextureRenderComponent>();
			pacdotRender->SetTexture("pacdot.png");

			auto pacDotPoints = pacdotObj->AddComponent<dae::PickupComponent>();
			pacDotPoints->SetPoints(10);

			pacdotObj->SetParent(pGameObject->shared_from_this(), false);
		}
		}			
	}
}
