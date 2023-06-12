#include "ButtonPressCommand.h"

dae::ButtonPressCommand::ButtonPressCommand(ButtonGroupComponent* pButton)
	:m_pButton{pButton}
{
}

void dae::ButtonPressCommand::Execute()
{
	m_pButton->PressSelectedButton();
}
