#pragma once
#include "ButtonComponent.h"
#include "Command.h"

namespace dae
{
	class ButtonPressCommand final : public Command
	{
	public:
		ButtonPressCommand(ButtonComponent* pButtonGroup);
		virtual ~ButtonPressCommand() = default;
		virtual void Execute() override;

	private:
		ButtonComponent* m_pButton;
	};
}

