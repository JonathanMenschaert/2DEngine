#pragma once
#include "ButtonGroupComponent.h"
#include "Command.h"

namespace dae
{

	class ButtonNavCommand final : public Command
	{
	public:
		ButtonNavCommand(ButtonGroupComponent* pButtonGroup, const glm::vec2& navDir);
		virtual ~ButtonNavCommand() = default;
		virtual void Execute() override;

	private:
		ButtonGroupComponent* m_pButtonGroup;
		const glm::vec2 m_NavDir;
	};
}

