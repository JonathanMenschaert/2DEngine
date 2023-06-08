#include "ButtonNavCommand.h"

dae::ButtonNavCommand::ButtonNavCommand(ButtonGroupComponent* pButtonGroup, const glm::vec2& navDir)
	:m_pButtonGroup{pButtonGroup}
	,m_NavDir{navDir}
{
}

void dae::ButtonNavCommand::Execute()
{
	m_pButtonGroup->NavigateToClosestButton(m_NavDir);
}
