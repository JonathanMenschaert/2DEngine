#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class DebugLivesCommand final : public Command
	{
	public:
		DebugLivesCommand(GameObject* pActor);
		virtual ~DebugLivesCommand() = default;
		virtual void Execute() override;

	private:
		GameObject* m_pActor;
	};
}
