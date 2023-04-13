#pragma once

namespace dae
{
	class Event
	{
	public:
		Event(const char* eventName);
		virtual ~Event() = default;
		Event(const Event& other) = delete;
		Event(Event&& other) noexcept = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) = delete;

		bool operator==(const Event& rhs) const;

	private:
		const char* m_EventName;
	};
}


