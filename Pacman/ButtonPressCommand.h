#pragma once
#include "ButtonGroupComponent.h"
#include "Command.h"

namespace dae
{
	class ButtonPressCommand final : public Command
	{
	public:
		ButtonPressCommand(ButtonGroupComponent* pButtonGroup);
		virtual ~ButtonPressCommand() = default;
		virtual void Execute() override;

	private:
		ButtonGroupComponent* m_pButton;
	};
}

