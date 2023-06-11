#pragma once
#include "Command.h"
#include "LoadSceneComponent.h"

namespace dae
{
	class LoadSceneCommand final : public Command
	{
	public:
		LoadSceneCommand(LoadSceneComponent* pLoadScene);
		virtual ~LoadSceneCommand() = default;
		virtual void Execute() override;

	private:
		LoadSceneComponent* m_pLoadScene;
	};
}

