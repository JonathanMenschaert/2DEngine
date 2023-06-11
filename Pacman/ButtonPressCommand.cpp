#include "ButtonPressCommand.h"

dae::ButtonPressCommand::ButtonPressCommand(ButtonComponent* pButton)
	:m_pButton{pButton}
{
}

void dae::ButtonPressCommand::Execute()
{
	m_pButton->OnClick();
}
