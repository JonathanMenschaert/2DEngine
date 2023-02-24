#pragma once
#include <memory>
namespace dae
{
	class Time
	{
	public:
		~Time() = default;
		Time(const Time& time) = delete;
		Time(Time&& time) noexcept = delete;
		Time& operator=(const Time& time) = delete;
		Time& operator=(Time& time) noexcept = delete;

		static std::unique_ptr<Time*>& GetInstance();

	private:
		Time() = default;

		static std::unique_ptr<Time*> m_Instance;

	};
}

