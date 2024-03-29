#pragma once
#include "Singleton.h"
#include "Gamepad.h"
#include "Command.h"
#include <vector>
#include <memory>
#include <map>
#include <set>
#include "SDL_keycode.h"

namespace dae
{
	enum class InteractionType
	{
		Press,
		Release,
		Hold
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		
		void Reset();
		bool ProcessInput();
		void BindKeyboardCommand(InteractionType type, SDL_Keycode key, std::unique_ptr<Command> pCommand, unsigned int index = 0);
		void BindDigitalCommand(unsigned int gamepadIdx, InteractionType type, Gamepad::DigitalButton key, std::unique_ptr<Command> pCommand);
		void BindAnalogCommand(unsigned int gamepadIdx, Gamepad::AnalogButton key, std::unique_ptr<Command> pCommand);
		float GetAnalogValue(Gamepad::AnalogButton, unsigned int gamepadIdx) const;

	private:

		bool ShouldExecuteCommand(InteractionType type, SDL_Keycode key) const;
		bool ShouldExecuteCommand(InteractionType type, Gamepad::DigitalButton key, unsigned int gamepadIdx) const;
		void AddControllerById(unsigned int gamepadIdx);

		std::vector<std::unique_ptr<Gamepad>> m_Gamepads{};

		std::map<std::pair<unsigned int, SDL_Keycode>, std::pair<InteractionType, std::unique_ptr<Command>>> m_KeyboardCommands{};
		std::map<std::pair<unsigned int, Gamepad::DigitalButton>, std::pair<InteractionType, std::unique_ptr<Command>>> m_DigitalGamepadCommands{};
		std::map<std::pair<unsigned int, Gamepad::AnalogButton>, std::unique_ptr<Command>> m_AnalogGamepadCommands{};

		std::set<SDL_Keycode> m_KeyboardKeysDown{};
		std::set<SDL_Keycode> m_KeyboardKeysUp{};
		std::set<SDL_Keycode> m_KeyboardKeysHold{};

		const unsigned int m_MaxControllers{ 4 };
	};

}
