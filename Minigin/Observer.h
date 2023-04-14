#pragma once

#include "Event.h"
namespace dae
{
	template<typename T>
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event<T>& e) = 0;
	};
}


