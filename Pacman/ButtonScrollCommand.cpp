#include "ButtonScrollCommand.h"


dae::ButtonScrollCommand::ButtonScrollCommand(LetterScrollButtonComponent* pScrollButton, int scrollAmount)
	:m_pScrollButton{ pScrollButton }
	,m_ScrollAmount{scrollAmount}
{
}

void dae::ButtonScrollCommand::Execute()
{
	m_pScrollButton->Scroll(m_ScrollAmount);
}
