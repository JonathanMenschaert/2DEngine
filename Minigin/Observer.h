#pragma once
namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& event) = 0;
	};
}


