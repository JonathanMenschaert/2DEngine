#include "Subject.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), observer));
}

void dae::Subject::NotifyObservers(const Event& event)
{
	for (auto observer : m_Observers)
	{
		observer->Notify(event);
	}
}
