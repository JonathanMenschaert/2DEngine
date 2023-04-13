#include "Event.h"

dae::Event::Event(const char* eventName)
    :m_EventName{eventName}
{
}

bool dae::Event::operator==(const Event& rhs) const
{
    return m_EventName == rhs;
}
