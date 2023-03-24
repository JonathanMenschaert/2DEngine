#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include "Gamepad.h"
#include "Command.h"

bool dae::InputManager::ProcessInput()
{
	m_KeyboardKeysUp.clear();
	m_KeyboardKeysDown.clear();
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		ImGui_ImplSDL2_ProcessEvent(&e);
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			if (!m_KeyboardKeysHold.contains(e.key.keysym.sym))
			{
				m_KeyboardKeysDown.insert(e.key.keysym.sym);
				m_KeyboardKeysHold.insert(e.key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			if (m_KeyboardKeysHold.contains(e.key.keysym.sym))
			{
				m_KeyboardKeysDown.insert(e.key.keysym.sym);
				m_KeyboardKeysHold.erase(e.key.keysym.sym);
			}
			break;
		}
	}	

	for (const auto& pGamepad : m_Gamepads)
	{
		pGamepad->Update();
	}

	for (const auto& keyboardButton : m_KeyboardCommands)
	{
		const auto& keyboardCommand{ keyboardButton.second };
		if (keyboardCommand.first == InteractionType::Press && m_KeyboardKeysDown.contains(keyboardButton.first))
		{
			keyboardCommand.second->Execute();
		}
		else if (keyboardCommand.first == InteractionType::Hold && m_KeyboardKeysHold.contains(keyboardButton.first))
		{
			keyboardCommand.second->Execute();
		}
		else if (keyboardCommand.first == InteractionType::Release && m_KeyboardKeysUp.contains(keyboardButton.first))
		{
			keyboardCommand.second->Execute();
		}
	}

	for (const auto& gamepadCommand : m_DigitalGamepadCommands)
	{
		const auto& gamepadButton{ gamepadCommand.first };
		const unsigned int gamepadIdx{ gamepadCommand.second.first };
		if (gamepadButton.second == InteractionType::Hold && m_Gamepads[gamepadIdx]->IsPressed(gamepadButton.first))
		{
			gamepadCommand.second.second->Execute();
		}

		else if (gamepadButton.second == InteractionType::Press && m_Gamepads[gamepadIdx]->IsDown(gamepadButton.first))
		{
			gamepadCommand.second.second->Execute();
		}

		else if (gamepadButton.second == InteractionType::Release && m_Gamepads[gamepadIdx]->IsUp(gamepadButton.first))
		{
			gamepadCommand.second.second->Execute();
		}
	}

	for (const auto& gamepadCommand : m_AnalogGamepadCommands)
	{
		const auto& gamepadButton{ gamepadCommand.first };
		const unsigned int gamepadIdx{ gamepadCommand.second.first };
		if (m_Gamepads[gamepadIdx]->GetAxis(gamepadButton) > 0.f)
		{
			gamepadCommand.second.second->Execute();
		}
	}


	return true;
}

void dae::InputManager::AddControllerById(unsigned int gamepadIdx)
{
	if (gamepadIdx < m_Gamepads.size() || gamepadIdx >= m_MaxControllers)
	{
		return;
	}

	while (m_Gamepads.size() <= gamepadIdx)
	{
		unsigned int nextIdx{ static_cast<unsigned int>(m_Gamepads.size()) };
		m_Gamepads.push_back(std::make_unique<Gamepad>(nextIdx));
	}
}

void dae::InputManager::BindKeyboardCommand(InteractionType type, SDL_Keycode key, std::unique_ptr<Command> pCommand)
{
	m_KeyboardCommands[key] = std::make_pair(type, std::move(pCommand));
}

void dae::InputManager::BindDigitalCommand(unsigned int controllerIdx, InteractionType type, Gamepad::DigitalButton key, std::unique_ptr<Command> pCommand)
{
	AddControllerById(controllerIdx);
	m_DigitalGamepadCommands[std::make_pair(key, type)] = std::make_pair(controllerIdx, std::move(pCommand));
}

void dae::InputManager::BindAnalogCommand(unsigned int controllerIdx, dae::Gamepad::AnalogButton key, std::unique_ptr<dae::Command> pCommand)
{
	AddControllerById(controllerIdx);
	m_AnalogGamepadCommands[key] = std::make_pair(controllerIdx, std::move(pCommand));
}