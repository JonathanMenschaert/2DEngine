#include "GameTime.h"

namespace dae
{
    GameTime::GameTime()
        :m_ElapsedTime{0.f}
    {
    }
    void GameTime::Reset()
    {
        m_CurrTime = std::chrono::high_resolution_clock::now();
        m_PrevTime = m_CurrTime;
        m_ElapsedTime = 0.f;
    }

    void GameTime::Update()
    {
        m_CurrTime = std::chrono::high_resolution_clock::now();
        m_ElapsedTime = std::chrono::duration<float>(m_CurrTime - m_PrevTime).count();
        m_PrevTime = m_CurrTime;
    }

    float GameTime::GetElapsedTime() const
    {
        return m_ElapsedTime;
    }

    const std::chrono::high_resolution_clock::time_point& GameTime::CurrentTime() const
    {
        return m_CurrTime;
    }

    const std::chrono::high_resolution_clock::time_point GameTime::Now() const
    {
        return std::chrono::high_resolution_clock::now();
    }

    
}
