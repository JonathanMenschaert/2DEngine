#include "Time.h"

namespace dae
{
    std::unique_ptr<Time*> Time::m_Instance{ nullptr };

    std::unique_ptr<Time*>& Time::GetInstance()
    {
        if (!m_Instance)
        {
            m_Instance = std::make_unique<Time*>();
        }
        return m_Instance;
    }
}
