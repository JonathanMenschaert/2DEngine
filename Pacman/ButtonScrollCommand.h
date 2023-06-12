#pragma once
#include "Command.h"
#include "ButtonGroupComponent.h"

namespace dae
{
	class ButtonScrollCommand final : public Command
	{
	public:
		ButtonScrollCommand(ButtonGroupComponent* pScrollButton, int scrollAmount);
		virtual ~ButtonScrollCommand() = default;
		virtual void Execute() override;

	private:
		ButtonGroupComponent* m_pScrollButton;
		const int m_ScrollAmount;
	};
}

