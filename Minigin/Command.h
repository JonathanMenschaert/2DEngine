#pragma once
namespace dae
{
	class GameObject;
	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};
}
