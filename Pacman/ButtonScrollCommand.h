#pragma once
#include "Command.h"
#include "LetterScrollButtonComponent.h"

namespace dae
{
	class ButtonScrollCommand final : public Command
	{
	public:
		ButtonScrollCommand(LetterScrollButtonComponent* pScrollButton, int scrollAmount);
		virtual ~ButtonScrollCommand() = default;
		virtual void Execute() override;

	private:
		LetterScrollButtonComponent* m_pScrollButton;
		const int m_ScrollAmount;
	};
}

