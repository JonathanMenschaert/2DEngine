#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>
#include <iostream>

bool dae::InputManager::ProcessInput()
{
	m_KeyboardKeysUp.clear();
	m_KeyboardKeysDown.clear();
	SDL_Event e;
	
	while (SDL_PollEvent(&e)) {
		
		SDL_Keycode key{ e.key.keysym.sym };
		switch (e.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			if (!m_KeyboardKeysHold.contains(key))
			{
				m_KeyboardKeysDown.insert(key);
				m_KeyboardKeysHold.insert(key);
			}
			break;
		case SDL_KEYUP:
			if (m_KeyboardKeysHold.contains(key))
			{
				m_KeyboardKeysDown.insert(key);
				m_KeyboardKeysHold.erase(key);
			}
			break;
		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}	

	for (const auto& pGamepad : m_Gamepads)
	{
		pGamepad->Update();
	}

	for (const auto& keyboardButton : m_KeyboardCommands)
	{
		const auto& keyboardCommand{ keyboardButton.second };
		if (ShouldExecuteCommand(keyboardCommand.first, keyboardButton.first))
		{
			keyboardCommand.second->Execute();
		}
	}

	for (const auto& gamepadCommand : m_DigitalGamepadCommands)
	{
		const auto& gamepadButton{ gamepadCommand.first };
		const unsigned int gamepadIdx{ gamepadCommand.second.first };
		auto& command{ gamepadCommand.second.second };
		if (ShouldExecuteCommand(gamepadButton.second, gamepadButton.first, gamepadIdx))
		{
			command->Execute();
		}
	}

	for (const auto& gamepadCommand : m_AnalogGamepadCommands)
	{
		const auto& gamepadButton{ gamepadCommand.first };
		const unsigned int gamepadIdx{ gamepadCommand.second.first };
		if (abs(m_Gamepads[gamepadIdx]->GetAxis(gamepadButton)) > 0.f)
		{
			gamepadCommand.second.second->Execute();
		}
	}

	return true;
}

bool dae::InputManager::ShouldExecuteCommand(InteractionType type, SDL_Keycode key) const
{	
	SDL_Keycode keyboardKey{ static_cast<SDL_KeyCode>(key) };
	switch (type)
	{
	case InteractionType::Press:
		if (m_KeyboardKeysDown.contains(keyboardKey)) return true;
		break;
	case InteractionType::Release:
		if (m_KeyboardKeysUp.contains(keyboardKey)) return true;
		break;
	case InteractionType::Hold:
		if (m_KeyboardKeysHold.contains(keyboardKey)) return true;
		break;
	}
	
	return false;
}

bool dae::InputManager::ShouldExecuteCommand(InteractionType type, Gamepad::DigitalButton key, unsigned int gamepadIdx) const
{
	switch (type)
	{
	case InteractionType::Press:
		if (m_Gamepads[gamepadIdx]->IsDown(key)) return true;
		break;
	case InteractionType::Release:
		if (m_Gamepads[gamepadIdx]->IsUp(key)) return true;
		break;
	case InteractionType::Hold:
		if (m_Gamepads[gamepadIdx]->IsPressed(key)) return true;
		break;
	}
	return false;
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

void dae::InputManager::BindDigitalCommand(unsigned int gamepadIdx, InteractionType type, Gamepad::DigitalButton key, std::unique_ptr<Command> pCommand)
{
	AddControllerById(gamepadIdx);
	m_DigitalGamepadCommands[std::make_pair(key, type)] = std::make_pair(gamepadIdx, std::move(pCommand));
}

void dae::InputManager::BindAnalogCommand(unsigned int gamepadIdx, dae::Gamepad::AnalogButton key, std::unique_ptr<Command> pCommand)
{
	AddControllerById(gamepadIdx);
	m_AnalogGamepadCommands[key] = std::make_pair(gamepadIdx, std::move(pCommand));
}

float dae::InputManager::GetAnalogValue(Gamepad::AnalogButton button, unsigned int gamepadIdx) const
{
	return m_Gamepads[gamepadIdx]->GetAxis(button);
}
