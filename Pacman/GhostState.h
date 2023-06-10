#pragma once
namespace dae
{
	class GhostState
	{
	public:
		virtual void OnEnter();
		virtual void OnExit();
		virtual void Update() = 0;
	};
}

