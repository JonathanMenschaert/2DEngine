#pragma once
#include "Observer.h"
#include "Event.h"
#include <vector>
namespace dae
{
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		void NotifyObservers(const Event& event);
	private:
		std::vector<Observer*> m_Observers;
	};
}

