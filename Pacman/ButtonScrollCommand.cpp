#include "ButtonScrollCommand.h"


dae::ButtonScrollCommand::ButtonScrollCommand(ButtonGroupComponent* pScrollButton, int scrollAmount)
	:m_pScrollButton{ pScrollButton }
	,m_ScrollAmount{scrollAmount}
{
}

void dae::ButtonScrollCommand::Execute()
{
	m_pScrollButton->ScrollButton(m_ScrollAmount);
}
