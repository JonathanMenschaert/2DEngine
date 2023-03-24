#pragma once
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
	};
}
//up, down, left, right command => merge into move command
//member vars
//game obj
//speed
//Direction

//execute
//gettransform += direction * speed * Time::deltatime
