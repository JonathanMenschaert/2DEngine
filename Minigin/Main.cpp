#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)

#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
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
#include "steam_api.h"
#include <iostream>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& inputManager = dae::InputManager::GetInstance();
	//Background object
	auto bgObj = std::make_shared<dae::GameObject>();
	auto bgRender = bgObj->AddComponent<dae::RenderComponent>();
	bgRender->SetTexture("background.tga");

	auto bgTrans = bgObj->AddComponent<dae::TransformComponent>();
	bgTrans->SetLocalPosition(glm::vec3{ 0.f, 0.f, 0.f });
	scene.Add(bgObj);

	//Fps Object
	auto fpsObj = std::make_shared<dae::GameObject>();
	auto fpsTrans = fpsObj->AddComponent<dae::TransformComponent>();
	fpsTrans->SetLocalPosition(glm::vec2{ 10.f, 10.f });	
	
	auto fpsRender = fpsObj->AddComponent<dae::RenderComponent>();

	auto fpsText = fpsObj->AddComponent<dae::TextComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	fpsText->SetFont(font);
	fpsText->SetColor(255, 255, 0, 255);

	auto fpsComponent = fpsObj->AddComponent<dae::FPSComponent>();	
	scene.Add(fpsObj);

	//Pacman
	auto player1Obj = std::make_shared<dae::GameObject>();
	auto player1Col = player1Obj->AddComponent<dae::RectCollisionComponent>();
	player1Col->SetCollisionType(dae::RectCollisionComponent::CollisionType::DynamicCollision);
	player1Col->SetExtend(glm::vec2{ 10, 10 });
	player1Col->SetLayers(std::vector<std::string>{"enemy", "pickup", "wall1"});
	auto player1Trans = player1Obj->AddComponent<dae::TransformComponent>();
	player1Trans->SetLocalPosition(glm::vec2{ 250.f, 300.f });

	auto player1Render = player1Obj->AddComponent<dae::RenderComponent>();
	player1Render->SetTexture("pacman.png");

	auto player1Lives = player1Obj->AddComponent<dae::LivesComponent>();
	player1Lives->AddLife(3);

	auto player1Score = player1Obj->AddComponent<dae::ScoreComponent>();

	scene.Add(player1Obj);

	//Bind keys
	const float speed{ 100.f };
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_w, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, 1.f }));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_a, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ -1.f, 0.f }));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_s, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, -1.f }));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Hold, SDLK_d, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 1.f, 0.f }));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Press, SDLK_e, std::make_unique<dae::DebugLivesCommand>(player1Obj.get()));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Press, SDLK_o, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 10));
	inputManager.BindKeyboardCommand(dae::InputManager::InteractionType::Press, SDLK_p, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 50));

	//Bind Controller keys
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadUp, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, 1.f }));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadDown, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 0.f, -1.f }));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadLeft, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ -1.f, 0.f }));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadRight, std::make_unique<dae::MoveCommand>(player1Obj.get(), speed, glm::vec2{ 1.f, 0.f }));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonA, std::make_unique<dae::DebugLivesCommand>(player1Obj.get()));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonX, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 10));
	inputManager.BindDigitalCommand(0, dae::InputManager::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonY, std::make_unique<dae::DebugScoreCommand>(player1Obj.get(), 50));
	
	//Pacman 2
	auto player2Obj = std::make_shared<dae::GameObject>();
	auto player2Col = player2Obj->AddComponent<dae::RectCollisionComponent>();
	player2Col->SetCollisionType(dae::RectCollisionComponent::CollisionType::DynamicCollision);
	player2Col->SetExtend(glm::vec2{ 10, 10 });
	player2Col->SetLayers(std::vector<std::string>{"enemy", "pickup", "wall1"});
	auto player2Trans = player2Obj->AddComponent<dae::TransformComponent>();
	player2Trans->SetLocalPosition(glm::vec2{ 250.f, 300.f });

	auto player2Render = player2Obj->AddComponent<dae::RenderComponent>();
	player2Render->SetTexture("pacman.png");

	auto player2Lives = player2Obj->AddComponent<dae::LivesComponent>();
	player2Lives->AddLife(3);

	auto player2Score = player2Obj->AddComponent<dae::ScoreComponent>();

	scene.Add(player2Obj);

	//Bind Controller keys
	inputManager.BindDigitalCommand(1, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadUp, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ 0.f, 1.f }));
	inputManager.BindDigitalCommand(1, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadDown, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ 0.f, -1.f }));
	inputManager.BindDigitalCommand(1, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadLeft, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ -1.f, 0.f }));
	inputManager.BindDigitalCommand(1, dae::InputManager::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadRight, std::make_unique<dae::MoveCommand>(player2Obj.get(), speed, glm::vec2{ 1.f, 0.f }));
	inputManager.BindDigitalCommand(1, dae::InputManager::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonA, std::make_unique<dae::DebugLivesCommand>(player2Obj.get()));
	inputManager.BindDigitalCommand(1, dae::InputManager::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonX, std::make_unique<dae::DebugScoreCommand>(player2Obj.get(), 10));
	inputManager.BindDigitalCommand(1, dae::InputManager::InteractionType::Press, dae::Gamepad::DigitalButton::ButtonY, std::make_unique<dae::DebugScoreCommand>(player2Obj.get(), 50));


	//Pacdot
	auto pacdotObj = std::make_shared<dae::GameObject>();
	auto pacdotCol = pacdotObj->AddComponent<dae::RectCollisionComponent>();
	pacdotCol->SetCollisionType(dae::RectCollisionComponent::CollisionType::Trigger);
	pacdotCol->SetExtend(glm::vec2{ 5, 5 });
	pacdotCol->SetLayers(std::vector<std::string>{"enemy", "pickup", "wall1"});
	auto pacdotTrans = pacdotObj->AddComponent<dae::TransformComponent>();
	pacdotTrans->SetLocalPosition(glm::vec2{ 300.f, 250.f });

	auto pacdotRender = pacdotObj->AddComponent<dae::RenderComponent>();
	pacdotRender->SetTexture("pacdot.png");
	scene.Add(pacdotObj);
	
	//Ghost
	auto ghostObj = std::make_shared<dae::GameObject>();
	auto ghostCol = ghostObj->AddComponent<dae::RectCollisionComponent>();
	ghostCol->SetCollisionType(dae::RectCollisionComponent::CollisionType::Trigger);
	ghostCol->SetExtend(glm::vec2{ 10, 10 });
	ghostCol->SetLayers(std::vector<std::string>{"enemy", "wall2"});
	auto ghostTrans = ghostObj->AddComponent<dae::TransformComponent>();
	ghostTrans->SetLocalPosition(glm::vec2{ 300.f, 350.f });

	auto ghostRender = ghostObj->AddComponent<dae::RenderComponent>();
	ghostRender->SetTexture("ghost.png");
	scene.Add(ghostObj);

	//Hud Player 1
	auto hud1Obj = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto hud1Trans = hud1Obj->AddComponent<dae::TransformComponent>();
	hud1Trans->SetLocalPosition(glm::vec2{ 10.f, 100.f });

	auto lives1Obj = std::make_shared < dae::GameObject>();
	auto lives1Text = lives1Obj->AddComponent<dae::TextComponent>();
	lives1Text->SetFont(font);
	lives1Text->SetColor(255, 255, 255, 255);
	std::stringstream lives1StreamText{};
	lives1StreamText << "Lives: " << player1Lives->GetLives();
	lives1Text->SetText(lives1StreamText.str());

	auto lives1Render = lives1Obj->AddComponent<dae::RenderComponent>();
	auto lives1Trans = lives1Obj->AddComponent<dae::TransformComponent>();
	auto lives1 = lives1Obj->AddComponent<dae::LivesDisplayComponent>();
	lives1Trans->SetLocalPosition(glm::vec2{ 0.f, 100.f });
	
	lives1Obj->SetParent(hud1Obj, true);
	player1Lives->AddObserver(lives1.get());

	auto score1Obj = std::make_shared < dae::GameObject>();
	auto score1Text = score1Obj->AddComponent<dae::TextComponent>();
	score1Text->SetFont(font);
	score1Text->SetColor(255, 255, 255, 255);
	std::stringstream score1StreamText{};
	score1StreamText << "Score: " << player1Score->GetScore();
	score1Text->SetText(score1StreamText.str());

	auto score1Render = score1Obj->AddComponent<dae::RenderComponent>();
	auto score1Trans = score1Obj->AddComponent<dae::TransformComponent>();
	auto score1 = score1Obj->AddComponent<dae::ScoreDisplayComponent>();
	score1Trans->SetLocalPosition(glm::vec2{ 0.f, 120.f });

	score1Obj->SetParent(hud1Obj, true);
	player1Score->AddObserver(score1.get());
	scene.Add(hud1Obj);

	//Hud Player 2
	auto hud2Obj = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto hud2Trans = hud2Obj->AddComponent<dae::TransformComponent>();
	hud2Trans->SetLocalPosition(glm::vec2{ 10.f, 100.f });

	auto lives2Obj = std::make_shared < dae::GameObject>();
	auto lives2Text = lives2Obj->AddComponent<dae::TextComponent>();
	lives2Text->SetFont(font);
	lives2Text->SetColor(255, 255, 0, 255);
	std::stringstream lives2StreamText{};
	lives2StreamText << "Lives: " << player2Lives->GetLives();
	lives2Text->SetText(lives2StreamText.str());

	auto lives2Render = lives2Obj->AddComponent<dae::RenderComponent>();
	auto lives2Trans = lives2Obj->AddComponent<dae::TransformComponent>();
	auto lives2 = lives2Obj->AddComponent<dae::LivesDisplayComponent>();
	lives2Trans->SetLocalPosition(glm::vec2{ 0.f, 160.f });

	lives2Obj->SetParent(hud2Obj, true);
	player2Lives->AddObserver(lives2.get());

	auto score2Obj = std::make_shared < dae::GameObject>();
	auto score2Text = score2Obj->AddComponent<dae::TextComponent>();
	score2Text->SetFont(font);
	score2Text->SetColor(255, 255, 0, 255);
	std::stringstream score2StreamText{};
	score2StreamText << "Score: " << player2Score->GetScore();
	score2Text->SetText(score2StreamText.str());

	auto score2Render = score2Obj->AddComponent<dae::RenderComponent>();
	auto score2Trans = score2Obj->AddComponent<dae::TransformComponent>();
	auto score2 = score2Obj->AddComponent<dae::ScoreDisplayComponent>();
	score2Trans->SetLocalPosition(glm::vec2{ 0.f, 180.f });

	score2Obj->SetParent(hud2Obj, true);
	player2Score->AddObserver(score2.get());
	scene.Add(hud2Obj);
}

int main(int, char*[]) {
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
	}
	dae::Minigin engine("../Data/");
	engine.Run(load);
	SteamAPI_Shutdown();
    return 0;
}