#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class DebugScoreCommand final : public Command
	{
	public:
		DebugScoreCommand(GameObject* pActor, int score);
		virtual ~DebugScoreCommand() = default;
		virtual void Execute() override;
	private:
		GameObject* m_pActor;
		const int m_Score;
	};
}

