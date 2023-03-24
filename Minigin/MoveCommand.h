#pragma once
#include "Command.h"
#include "glm/glm.hpp"
#include "GameObject.h"
namespace dae
{
	
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* gameObj, float speed, const glm::vec2& direction);
		~MoveCommand() = default;
		void Execute() override;

	private:
		GameObject* m_pGameObject{ nullptr };
		const float m_Speed;
		const glm::vec2 m_Direction;
	};
}
