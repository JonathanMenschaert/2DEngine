#include "MoveCommand.h"
#include "Time.h"
dae::MoveCommand::MoveCommand(GameObject* pActor, float speed, const glm::vec2& direction)
	: Command(pActor)
	, m_Speed{speed}
	, m_Direction{ direction }
{
}

void dae::MoveCommand::Execute()
{
	auto pTransform{ GetActor()->GetComponent<TransformComponent>().lock()};
	glm::vec2 pos{ pTransform->GetLocalPosition() };
	
	glm::vec2 direction = m_Direction;
	direction.y *= -1;
	pos += direction * m_Speed * Time::GetInstance().GetElapsedTime();
	pTransform->SetLocalPosition(pos);
}
