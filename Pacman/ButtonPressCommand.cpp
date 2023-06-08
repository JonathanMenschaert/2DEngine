#include "ButtonPressCommand.h"

dae::ButtonPressCommand::ButtonPressCommand(ButtonGroupComponent* pButtonGroup)
	:m_pButtonGroup{pButtonGroup}
{
}

void dae::ButtonPressCommand::Execute()
{
	m_pButtonGroup->PressSelectedButton();
}
