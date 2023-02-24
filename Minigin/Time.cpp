#include "Time.h"

namespace dae
{
    
    void Time::Reset()
    {
        m_CurrTime = std::chrono::high_resolution_clock::now();
        m_PrevTime = m_CurrTime;
        m_ElapsedTime = 0.f;
    }

    void Time::Update()
    {
        m_CurrTime = std::chrono::high_resolution_clock::now();
        m_ElapsedTime = std::chrono::duration<float>(m_CurrTime - m_PrevTime).count();
        m_PrevTime = m_CurrTime;
    }

    float Time::GetElapsedTime() const
    {
        return m_ElapsedTime;
    }
}
