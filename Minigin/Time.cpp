#include "Time.h"
#include <iostream>
namespace dae
{
    Time::Time()
        :m_ElapsedTime{0.f}
    {
    }
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
        std::cout << m_ElapsedTime << "\n";
        m_PrevTime = m_CurrTime;
    }

    float Time::GetElapsedTime() const
    {
        return m_ElapsedTime;
    }

    const std::chrono::high_resolution_clock::time_point& Time::GetTime() const
    {
        return m_CurrTime;
    }

    const std::chrono::high_resolution_clock::time_point Time::Now() const
    {
        return std::chrono::high_resolution_clock::now();
    }

    
}
