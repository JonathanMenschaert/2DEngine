#pragma once
#include <memory>
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		Time() = default;
		~Time() = default;
		Time(const Time& time) = delete;
		Time(Time&& time) noexcept = delete;
		Time& operator=(const Time& time) = delete;
		Time& operator=(Time& time) noexcept = delete;

		void Reset();
		void Update();
		
		float GetElapsedTime() const;

	protected:
		

		std::chrono::high_resolution_clock::time_point m_CurrTime{};
		std::chrono::high_resolution_clock::time_point m_PrevTime{};
		float m_ElapsedTime;


	};
}

