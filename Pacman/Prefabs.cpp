#include "Prefabs.h"
#include "MoveCommand.h"
#include <memory>
#include "Gamepad.h"
void dae::InputPrefabs::AttachPlayerKeyboard(InputManager& inputManager, GameObject* pGameObj)
{
	//Bind keys
	constexpr float speed{ 90.f };
	inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_w, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ 0.f, 1.f }));
	inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_a, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ -1.f, 0.f }));
	inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_s, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ 0.f, -1.f }));
	inputManager.BindKeyboardCommand(dae::InteractionType::Hold, SDLK_d, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ 1.f, 0.f }));
}

void dae::InputPrefabs::AttachPlayerController(InputManager& inputManager, GameObject* pGameObj, int Idx)
{
	//Bind controller keys
	constexpr float speed{ 90.f };
	inputManager.BindDigitalCommand(Idx, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadUp, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ 0.f, 1.f }));
	inputManager.BindDigitalCommand(Idx, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadDown, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ 0.f, -1.f }));
	inputManager.BindDigitalCommand(Idx, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadLeft, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ -1.f, 0.f }));
	inputManager.BindDigitalCommand(Idx, dae::InteractionType::Hold, dae::Gamepad::DigitalButton::DPadRight, std::make_unique<dae::MoveCommand>(pGameObj, speed, glm::vec2{ 1.f, 0.f }));
}
