#pragma once
#include "Command.h"
#include "glm/glm.hpp"
#include "GameObject.h"
namespace dae
{
	
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* pActor, float speed, const glm::vec2& direction);
		virtual ~MoveCommand() = default;
		virtual void Execute() override;

	private:
		GameObject* m_pActor;
		const float m_Speed;
		const glm::vec2 m_Direction;
	};
}
