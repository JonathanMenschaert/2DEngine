#pragma once
#include "GameObject.h"
#include "InputManager.h"

namespace dae
{
	class InputPrefabs
	{
	public:
		static void AttachPlayerKeyboard(InputManager& inputManager, GameObject* pGameObj);
		static void AttachPlayerController(InputManager& inputManager, GameObject* pGameObj, int Idx);
	};
}

