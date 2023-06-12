#pragma once
#include "Command.h"

namespace dae
{
	class MuteCommand final : public Command
	{
	public:
		MuteCommand() = default;
		virtual ~MuteCommand() = default;
		virtual void Execute() override;
	};
}

