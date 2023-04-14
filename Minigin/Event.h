#pragma once

namespace dae
{
	template<typename T>
	class Event
	{
	public:
		Event(const char* eventName, T Payload);
		virtual ~Event() = default;
		Event(const Event& other) = delete;
		Event(Event&& other) noexcept = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) = delete;

		bool operator==(const Event& rhs) const;

		T GetPayload() const;

	private:
		const char* m_EventName;
		T m_Payload;
	};

	template<typename T>
	dae::Event<T>::Event(const char* eventName, T Payload)
		:m_EventName{eventName}
		,m_Payload(Payload)
	{
	}
	template<typename T>
	inline bool Event<T>::operator==(const Event& rhs) const
	{
		return m_EventName == rhs.m_EventName;
	}

	template<typename T>
	inline T Event<T>::GetPayload() const
	{
		return m_Payload;
	}
}


