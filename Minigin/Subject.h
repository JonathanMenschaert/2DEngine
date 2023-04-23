#pragma once
#include "Observer.h"
#include "Event.h"
#include <vector>
namespace dae
{
	template<typename T>
	class Subject
	{
	public:
		virtual ~Subject() = default;
		void AddObserver(Observer<T>* observer);
		void RemoveObserver(Observer<T>* observer);

	protected:
		
		void NotifyObservers(const Event<T>& event);
	private:
		std::vector<Observer<T>*> m_Observers;
	};

	template<typename T>
	void Subject<T>::NotifyObservers(const Event<T>& event)
	{
		for (auto observer : m_Observers)
		{
			observer->Notify(event);
		}
	}

	template<typename T>
	void Subject<T>::AddObserver(Observer<T>* observer)
	{
		m_Observers.push_back(observer);
	}

	template<typename T>
	void Subject<T>::RemoveObserver(Observer<T>* observer)
	{
		m_Observers.erase(std::remove_if(m_Observers.begin(), m_Observers.end(), observer));
	}
}

