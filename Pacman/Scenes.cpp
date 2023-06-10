#include "Scenes.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "TextureRenderComponent.h"
#include "RotatorComponent.h"
#include "DearImGuiComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "glm/glm.hpp"
#include "RectCollisionComponent.h"
#include "LivesComponent.h"
#include "LivesDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "DebugLivesCommand.h"
#include "DebugScoreCommand.h"
#include "Gamepad.h"
#include <sstream>
#include "ScoreComponent.h"
#include <iostream>
#include <unordered_map>
#include "Achievement.h"
#include "HowToPlayComponent.h"
#include "PickupComponent.h"
#include "PlayerComponent.h"
#include "MapGeneratorComponent.h"
#include "GhostControllerComponent.h"
#include "ButtonGroupComponent.h"
#include "ButtonComponent.h"
#include "ButtonNavCommand.h"
#include "ButtonPressCommand.h"
#include "LevelIO.h"
#include "GhostComponent.h"
#include "ScaredTimerComponent.h"

namespace dae
{
	void SingleOne::LoadScene()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Single1");
		auto& inputManager = dae::InputManager::GetInstance();
		auto sceneRoot = std::make_shared<dae::GameObject>();
		sceneRoot->AddComponent<dae::TransformComponent>();
		scene.Add(sceneRoot);


		////Background object
		auto bgObj = std::make_shared<dae::GameObject>();
		auto bgRender = bgObj->AddComponent<dae::TextureRenderComponent>();
		bgRender->SetTexture("background.tga");

		auto bgTrans = bgObj->AddComponent<dae::TransformComponent>();
		bgTrans->SetLocalPosition(glm::vec3{ 0.f, 0.f, 0.f });
		bgObj->SetParent(sceneRoot);

		//Map gameobject

		auto mapObj = std::make_shared<dae::GameObject>();
		auto mapTrans = mapObj->AddComponent<dae::TransformComponent>();
		mapTrans->SetLocalPosition(glm::vec2{ 75.f, 50.f });
		auto mapGen = mapObj->AddComponent<dae::MapGeneratorComponent>();

		//dae::LevelIO::SaveLevelLayout(LevelLayout{ 28, 31, tileData }, "../Data/level0.level");
		LevelLayout layout{ dae::LevelIO::LoadLevelLayout("../Data/level0.level") };
		mapGen->LoadMap(layout.columns, layout.rows, 16, layout.levelData, std::vector<std::string>{"wall.png", "path.png"});

		mapObj->SetParent(sceneRoot);


		//How to play
		auto howToPlayObj = std::make_shared < dae::GameObject>();
		auto htpTrans = howToPlayObj->AddComponent<dae::TransformComponent>();
		htpTrans->SetLocalPosition(glm::vec2{ 10.f, 30.f });
		howToPlayObj->AddComponent<dae::HowToPlayComponent>();
		howToPlayObj->SetParent(sceneRoot);

		//Fps Object
		auto fpsObj = std::make_shared<dae::GameObject>();
		auto fpsTrans = fpsObj->AddComponent<dae::TransformComponent>();
		fpsTrans->SetLocalPosition(glm::vec2{ 10.f, 10.f });

		fpsObj->AddComponent<dae::TextureRenderComponent>();

		auto fpsText = fpsObj->AddComponent<dae::TextComponent>();
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
		fpsText->SetFont(font);
		fpsText->SetColor(255, 255, 0, 255);

		fpsObj->AddComponent<dae::FPSComponent>();
		fpsObj->SetParent(sceneRoot);

		//Pacman
		auto player1Obj = std::make_shared<dae::GameObject>();
		auto player1Col = player1Obj->AddComponent<dae::RectCollisionComponent>();
		player1Col->SetCollisionType(dae::CollisionType::DynamicCollision);
		player1Col->SetCollisionBox(glm::vec2{ 16, 16 });
		player1Col->SetLayers(std::vector<std::string>{"player1"});
		auto player1Trans = player1Obj->AddComponent<dae::TransformComponent>();
		player1Trans->SetLocalPosition(mapGen->GetPlayerSpawns());

		auto player1Render = player1Obj->AddComponent<dae::TextureRenderComponent>();
		player1Render->SetTexture("pacman.png");

		auto player1Lives = player1Obj->AddComponent<dae::LivesComponent>();
		player1Lives->AddLife(3);

		auto player1Score = player1Obj->AddComponent<dae::ScoreComponent>();

		auto player1Player = player1Obj->AddComponent<dae::PlayerComponent>();
		player1Col->AddObserver(player1Player);
		player1Obj->SetParent(mapObj, false);

		//Bind keys
		const float speed{ 75.f };
		inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_w, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, 1.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_a, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ -1.f, 0.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_s, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, -1.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_d, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 1.f, 0.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_e, std::make_unique<dae::DebugLivesCommand>(player1Obj.get()));
		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_o, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 10));
		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_p, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 50));

		//Bind Controller keys
		inputManager.BindDigitalCommand(0, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadUp, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, 1.f }));
		inputManager.BindDigitalCommand(0, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadDown, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, -1.f }));
		inputManager.BindDigitalCommand(0, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadLeft, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ -1.f, 0.f }));
		inputManager.BindDigitalCommand(0, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadRight, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 1.f, 0.f }));
		inputManager.BindDigitalCommand(0, dae::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonA, std::make_unique<dae::DebugLivesCommand>(player1Obj.get()));
		inputManager.BindDigitalCommand(0, dae::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonX, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 10));
		inputManager.BindDigitalCommand(0, dae::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonY, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 50));

		//Pacman 2
		/*auto player2Obj = std::make_shared<dae::GameObject>();
		auto player2Col = player2Obj->AddComponent<dae::RectCollisionComponent>();
		player2Col->SetCollisionType(dae::CollisionType::DynamicCollision);
		player2Col->SetCollisionBox(glm::vec2{ 16, 16 });
		player2Col->SetLayers(std::vector<std::string>{"player2"});
		auto player2Trans = player2Obj->AddComponent<dae::TransformComponent>();
		player2Trans->SetLocalPosition(glm::vec2{ 250.f, 300.f });

		auto player2Render = player2Obj->AddComponent<dae::TextureRenderComponent>();
		player2Render->SetTexture("pacman.png");

		auto player2Lives = player2Obj->AddComponent<dae::LivesComponent>();
		player2Lives->AddLife(3);

		auto player2Score = player2Obj->AddComponent<dae::ScoreComponent>();

		auto player2Player = player2Obj->AddComponent<dae::PlayerComponent>();
		player2Col->AddObserver(player2Player);

		player2Obj->SetParent(sceneRoot);*/

		//Bind Controller keys
		/*inputManager.BindDigitalCommand(1, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadUp, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ 0.f, 1.f }));
		inputManager.BindDigitalCommand(1, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadDown, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ 0.f, -1.f }));
		inputManager.BindDigitalCommand(1, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadLeft, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ -1.f, 0.f }));
		inputManager.BindDigitalCommand(1, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadRight, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ 1.f, 0.f }));
		inputManager.BindDigitalCommand(1, dae::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonA, std::make_unique<dae::DebugLivesCommand>(player2Obj.get()));
		inputManager.BindDigitalCommand(1, dae::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonX, std::make_unique<dae::DebugScoreCommand>(player2Obj.get(), 10));
		inputManager.BindDigitalCommand(1, dae::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonY, std::make_unique<dae::DebugScoreCommand>(player2Obj.get(), 50));*/

		//Timer for scared ghosts
		auto timerObj = std::make_shared<dae::GameObject>();
		timerObj->AddComponent<dae::TransformComponent>();
		auto scaredTimer = timerObj->AddComponent<dae::ScaredTimerComponent>();
		player1Player->AddObserver(scaredTimer);
		timerObj->SetParent(sceneRoot);
		//Ghosts
		int ghostTexIdx{0};
		std::shared_ptr<Texture2D> pScaredGhostTexture{ResourceManager::GetInstance().LoadTexture("scaredghost.png")};
		for (auto& position : mapGen->GetGhostSpawns())
		{
			auto ghostObj = std::make_shared<dae::GameObject>();
			auto ghostCol = ghostObj->AddComponent<dae::RectCollisionComponent>();
			ghostCol->SetCollisionType(dae::CollisionType::Trigger);
			ghostCol->SetCollisionBox(glm::vec2{ 16, 16 });
			ghostCol->SetLayers(std::vector<std::string>{"player1", "player2"});

			auto ghostTrans = ghostObj->AddComponent<dae::TransformComponent>();
			ghostTrans->SetLocalPosition(position);

			ghostObj->AddComponent<dae::GhostControllerComponent>();
			ghostObj->SetParent(mapObj, false);

			auto ghost = ghostObj->AddComponent<dae::GhostComponent>();
			ghost->SetSpawnPos(position);
			player1Player->AddObserver(ghost);
			ghostCol->AddObserver(ghost);

			ghostObj->AddComponent<dae::TextureRenderComponent>();
			std::stringstream ghostTexPath{};
			ghostTexPath << "ghost" << ghostTexIdx++ << ".png";
			
			std::shared_ptr<Texture2D> pNormalGhosttTexture {ResourceManager::GetInstance().LoadTexture(ghostTexPath.str())};
			ghost->SetNormalTexture(pNormalGhosttTexture);
			ghost->SetScaredTexture(pScaredGhostTexture);

			scaredTimer->AddObserver(ghost);
		}

		//Hud Player 1
		auto hud1Obj = std::make_shared<dae::GameObject>();
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
		auto hud1Trans = hud1Obj->AddComponent<dae::TransformComponent>();
		hud1Trans->SetLocalPosition(glm::vec2{ 10.f, 0.f });

		auto lives1Obj = std::make_shared < dae::GameObject>();
		auto lives1Text = lives1Obj->AddComponent<dae::TextComponent>();
		lives1Text->SetFont(font);
		lives1Text->SetColor(255, 255, 255, 255);
		std::stringstream lives1StreamText{};
		lives1StreamText << "Lives: " << player1Lives->GetLives();
		lives1Text->SetText(lives1StreamText.str());

		lives1Obj->AddComponent<dae::TextureRenderComponent>();
		auto lives1Trans = lives1Obj->AddComponent<dae::TransformComponent>();
		auto lives1 = lives1Obj->AddComponent<dae::LivesDisplayComponent>();
		lives1Trans->SetLocalPosition(glm::vec2{ 0.f, 100.f });

		lives1Obj->SetParent(hud1Obj, false);
		player1Lives->AddObserver(lives1);

		auto score1Obj = std::make_shared < dae::GameObject>();
		auto score1Text = score1Obj->AddComponent<dae::TextComponent>();
		score1Text->SetFont(font);
		score1Text->SetColor(255, 255, 255, 255);
		std::stringstream score1StreamText{};
		score1StreamText << "Score: " << player1Score->GetScore();
		score1Text->SetText(score1StreamText.str());

		score1Obj->AddComponent<dae::TextureRenderComponent>();
		auto score1Trans = score1Obj->AddComponent<dae::TransformComponent>();
		auto score1 = score1Obj->AddComponent<dae::ScoreDisplayComponent>();
		score1Trans->SetLocalPosition(glm::vec2{ 0.f, 120.f });

		score1Obj->SetParent(hud1Obj, false);
		player1Score->AddObserver(score1);
		player1Player->AddObserver(player1Score);
		hud1Obj->SetParent(sceneRoot);

		//Hud Player 2
		/*auto hud2Obj = std::make_shared<dae::GameObject>();
		font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
		auto hud2Trans = hud2Obj->AddComponent<dae::TransformComponent>();
		hud2Trans->SetLocalPosition(glm::vec2{ 10.f, 0.f });

		auto lives2Obj = std::make_shared < dae::GameObject>();
		auto lives2Text = lives2Obj->AddComponent<dae::TextComponent>();
		lives2Text->SetFont(font);
		lives2Text->SetColor(255, 255, 0, 255);
		std::stringstream lives2StreamText{};
		lives2StreamText << "Lives: " << player2Lives->GetLives();
		lives2Text->SetText(lives2StreamText.str());

		lives2Obj->AddComponent<dae::TextureRenderComponent>();
		auto lives2Trans = lives2Obj->AddComponent<dae::TransformComponent>();
		auto lives2 = lives2Obj->AddComponent<dae::LivesDisplayComponent>();
		lives2Trans->SetLocalPosition(glm::vec2{ 0.f, 160.f });

		lives2Obj->SetParent(hud2Obj, false);
		player2Lives->AddObserver(lives2);

		auto score2Obj = std::make_shared<dae::GameObject>();
		auto score2Text = score2Obj->AddComponent<dae::TextComponent>();
		score2Text->SetFont(font);
		score2Text->SetColor(255, 255, 0, 255);
		std::stringstream score2StreamText{};
		score2StreamText << "Score: " << player2Score->GetScore();
		score2Text->SetText(score2StreamText.str());

		score2Obj->AddComponent<dae::TextureRenderComponent>();
		auto score2Trans = score2Obj->AddComponent<dae::TransformComponent>();
		auto score2 = score2Obj->AddComponent<dae::ScoreDisplayComponent>();
		score2Trans->SetLocalPosition(glm::vec2{ 0.f, 180.f });

		score2Obj->SetParent(hud2Obj, false);
		player2Score->AddObserver(score2);
		hud2Obj->SetParent(sceneRoot);*/
	}

	void LevelTester::LoadScene()
	{

		auto& scene = dae::SceneManager::GetInstance().CreateScene("LevelTester");
		//auto& inputManager = dae::InputManager::GetInstance();
		auto sceneRoot = std::make_shared<dae::GameObject>();
		sceneRoot->AddComponent<dae::TransformComponent>();
		scene.Add(sceneRoot);

		/*std::vector<unsigned char> tileData
		{
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
				2, 5, 4, 4, 4, 4, 6, 4, 4, 4, 4, 4, 6, 2, 2, 6, 4, 4, 4, 4, 4, 6, 4, 4, 4, 4, 5, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 0, 0, 2, 4, 2, 0, 0, 0, 2, 4, 2, 2, 4, 2, 0, 0, 0, 2, 4, 2, 0, 0, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 6, 4, 4, 4, 4, 6, 4, 4, 6, 4, 4, 6, 4, 4, 6, 4, 4, 6, 4, 4, 6, 4, 4, 4, 4, 6, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 6, 4, 4, 4, 4, 6, 2, 2, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 2, 2, 6, 4, 4, 4, 4, 6, 2,
				2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2,
				0, 0, 0, 0, 0, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 2, 4, 2, 2, 6, 4, 4, 6, 6, 6, 6, 4, 4, 6, 2, 2, 4, 2, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 2, 4, 2, 2, 4, 2, 2, 2, 1, 1, 2, 2, 2, 4, 2, 2, 4, 2, 0, 0, 0, 0, 0,
				2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 8, 1, 3, 3, 1, 8, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2,
				2, 1, 1, 1, 1, 1, 6, 4, 4, 6, 2, 1, 1, 1, 1, 1, 1, 2, 6, 4, 4, 6, 1, 1, 1, 1, 1, 2,
				2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 8, 1, 3, 3, 1, 8, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2,
				0, 0, 0, 0, 0, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 2, 4, 2, 2, 6, 4, 4, 4, 4, 4, 4, 4, 4, 6, 2, 2, 4, 2, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 0, 0, 0, 0, 0,
				2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2,
				2, 6, 4, 4, 4, 4, 6, 4, 4, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 4, 4, 6, 4, 4, 4, 4, 6, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 5, 4, 6, 2, 2, 6, 4, 4, 6, 4, 4, 6, 7, 7, 6, 4, 4, 6, 4, 4, 6, 2, 2, 6, 4, 5, 2,
				2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2,
				2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2,
				2, 6, 4, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 4, 6, 2,
				2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2,
				2, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 4, 4, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 2,
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2

		};*/

		std::vector<unsigned char> tileData
		{
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
				2, 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 2, 2, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 2,
				2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2,
				2, 6, 4, 4, 4, 4, 6, 2, 2, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 2, 2, 6, 4, 4, 4, 4, 6, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 6, 4, 6, 4, 4, 6, 4, 4, 4, 4, 4, 4, 4, 4, 6, 4, 4, 6, 4, 6, 2, 2, 4, 2,
				2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2,
				2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2,
				2, 6, 4, 4, 6, 4, 6, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 6, 4, 6, 4, 4, 6, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 6, 4, 4, 4, 6, 6, 4, 4, 4, 6, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 1, 1, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 6, 4, 6, 2, 2, 6, 4, 4, 6, 2, 8, 1, 3, 3, 1, 8, 2, 6, 4, 4, 6, 2, 2, 6, 4, 6, 2,
				2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 1, 1, 1, 1, 1, 1, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2,
				2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 8, 1, 3, 3, 1, 8, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2,
				2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2,
				2, 1, 1, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 4, 4, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 1, 1, 2,
				2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2,
				2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2,
				2, 6, 4, 6, 2, 2, 6, 4, 4, 6, 4, 4, 6, 2, 2, 6, 4, 4, 6, 4, 4, 6, 2, 2, 6, 4, 6, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 4, 2,
				2, 6, 4, 4, 6, 4, 6, 2, 2, 6, 4, 4, 6, 7, 7, 6, 4, 4, 6, 2, 2, 6, 4, 6, 4, 4, 6, 2,
				2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2,
				2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2,
				2, 4, 2, 2, 6, 4, 4, 6, 4, 4, 6, 4, 6, 2, 2, 6, 4, 6, 4, 4, 6, 4, 4, 6, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2,
				2, 4, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 4, 2,
				2, 5, 4, 4, 4, 4, 4, 6, 2, 2, 6, 4, 4, 4, 4, 4, 4, 6, 2, 2, 6, 4, 4, 4, 4, 4, 5, 2,
				2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2

		};

		auto mapObj = std::make_shared<dae::GameObject>();
		auto mapTrans = mapObj->AddComponent<dae::TransformComponent>();
		mapTrans->SetLocalPosition(glm::vec2{ 75.f, 50.f });
		auto mapGen = mapObj->AddComponent<dae::MapGeneratorComponent>();

		dae::LevelIO::SaveLevelLayout(LevelLayout{ 28, static_cast<int>(tileData.size()) / 28, tileData}, "../Data/level1.level");
		LevelLayout layout{ dae::LevelIO::LoadLevelLayout("../Data/level1.level") };
		mapGen->LoadMap(layout.columns, layout.rows, 16, layout.levelData, std::vector<std::string>{"wall.png", "path.png"});

		mapObj->SetParent(sceneRoot);

		//dae::LevelIO::SaveLevelLayout(LevelLayout{ 28, 31, tileData }, "../Data/level1.level");
		//LevelLayout layout{ dae::LevelIO::LoadLevelLayout("../Data/level1.level") };
	}

	void MainMenu::LoadScene()
	{
		auto& scene = dae::SceneManager::GetInstance().CreateScene("Main Menu");
		auto& inputManager = dae::InputManager::GetInstance();
		auto sceneRoot = std::make_shared<dae::GameObject>();
		sceneRoot->AddComponent<dae::TransformComponent>();
		scene.Add(sceneRoot);

		////Background object
		auto logoObj = std::make_shared<dae::GameObject>();
		auto logoRender = logoObj->AddComponent<dae::TextureRenderComponent>();
		logoRender->SetTexture("pacmanlogo.png");

		auto logoTrans = logoObj->AddComponent<dae::TransformComponent>();
		logoTrans->SetLocalPosition(glm::vec3{ 0.f, 0.f, 0.f });
		logoObj->SetParent(sceneRoot);

		//Font
		auto font = dae::ResourceManager::GetInstance().LoadFont("ArcadeFont.ttf", 32);

		//Button group
		auto buttonGrObj = std::make_shared<dae::GameObject>();
		buttonGrObj->AddComponent<dae::TransformComponent>();
		auto buttonGr = buttonGrObj->AddComponent<dae::ButtonGroupComponent>();
		buttonGrObj->SetParent(sceneRoot);

		//Button 1
		auto button1Obj = std::make_shared<dae::GameObject>();
		auto button1Trans = button1Obj->AddComponent<dae::TransformComponent>();
		button1Trans->SetLocalPosition(glm::vec2{200.f, 300.f});
		auto button1 = button1Obj->AddComponent<dae::ButtonComponent>();
		button1->SetButtonExtend(glm::vec2{10.f, 10.f});
		button1->SetButtonFont(font);
		button1->SetButtonText("Single Player");
		button1->SetNormalColor(255, 255, 255, 255);
		button1->SetHighlightColor(255, 255, 0, 255);
		button1->SetOnClick([]() {
			dae::SceneManager::GetInstance().LoadScene("Single1");
			}
		);
		button1Obj->SetParent(buttonGrObj);

		//Button 2
		auto button2Obj = std::make_shared<dae::GameObject>();
		auto button2Trans = button2Obj->AddComponent<dae::TransformComponent>();
		button2Trans->SetLocalPosition(glm::vec2{200.f, 340.f});
		auto button2 = button2Obj->AddComponent<dae::ButtonComponent>();
		button2->SetButtonExtend(glm::vec2{10.f, 10.f});
		button2->SetButtonFont(font);
		button2->SetButtonText("Co-op");
		button2->SetNormalColor(255, 255, 255, 255);
		button2->SetHighlightColor(255, 255, 0, 255);
		button2->SetOnClick([]() {
			std::cout << "Button2\n";
			}
		);
		button2Obj->SetParent(buttonGrObj);

		//Button 3
		auto button3Obj = std::make_shared<dae::GameObject>();
		auto button3Trans = button3Obj->AddComponent<dae::TransformComponent>();
		button3Trans->SetLocalPosition(glm::vec2{200.f, 380.f});
		auto button3 = button3Obj->AddComponent<dae::ButtonComponent>();
		button3->SetButtonExtend(glm::vec2{10.f, 10.f});
		button3->SetButtonFont(font);
		button3->SetButtonText("Versus");
		button3->SetNormalColor(255, 255, 255, 255);
		button3->SetHighlightColor(255, 255, 0, 255);
		button3->SetOnClick([]() {
			std::cout << "Button3\n";
			}
		);
		button3Obj->SetParent(buttonGrObj);

		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_w, std::make_unique<dae::ButtonNavCommand>(buttonGr, glm::vec2{ 0.f, -1.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_s, std::make_unique<dae::ButtonNavCommand>(buttonGr, glm::vec2{ 0.f, 1.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_d, std::make_unique<dae::ButtonNavCommand>(buttonGr, glm::vec2{ 1.f, 0.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_a, std::make_unique<dae::ButtonNavCommand>(buttonGr, glm::vec2{ -1.f, 0.f }));
		inputManager.BindKeyboardCommand(dae::InteractionType::Press, SDLK_KP_ENTER, std::make_unique<dae::ButtonPressCommand>(buttonGr));
		
	}
}
