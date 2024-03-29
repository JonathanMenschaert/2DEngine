#include "MoveCommand.h"
#include "GameTime.h"
dae::MoveCommand::MoveCommand(GameObject* pActor, float speed, const glm::vec2& direction)
	: m_pActor{ pActor }
	, m_Speed{speed}
	, m_Direction{ direction }
{
}

void dae::MoveCommand::Execute()
{
	auto pTransform{ m_pActor->GetComponent<TransformComponent>()};
	glm::vec2 pos{ pTransform->GetLocalPosition() };
	
	glm::vec2 direction = m_Direction;
	direction.y *= -1;
	pos += direction * m_Speed * GameTime::GetInstance().GetElapsedTime();
	pTransform->SetLocalPosition(pos);
}
