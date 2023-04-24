#pragma once
#include <memory>
#include "Singleton.h"
#include <chrono>

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime();
		~GameTime() = default;
		GameTime(const GameTime& time) = delete;
		GameTime(GameTime&& time) noexcept = delete;
		GameTime& operator=(const GameTime& time) = delete;
		GameTime& operator=(GameTime& time) noexcept = delete;

		void Reset();
		void Update();
		
		float GetElapsedTime() const;
		const std::chrono::high_resolution_clock::time_point& CurrentTime() const;
		const std::chrono::high_resolution_clock::time_point Now() const;

	protected:
		

		std::chrono::high_resolution_clock::time_point m_CurrTime{};
		std::chrono::high_resolution_clock::time_point m_PrevTime{};
		float m_ElapsedTime;


	};
}

