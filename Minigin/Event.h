#pragma once

namespace dae
{
	template<typename T>
	class Event
	{
	public:
		Event(T Payload);
		virtual ~Event() = default;
		Event(const Event& other) = delete;
		Event(Event&& other) noexcept = delete;
		Event& operator=(const Event& other) = delete;
		Event& operator=(Event&& other) = delete;

		T GetPayload() const;

	private:
		T m_Payload;
	};

	template<typename T>
	dae::Event<T>::Event(T Payload)
		:m_Payload(Payload)
	{
	}
	

	template<typename T>
	inline T Event<T>::GetPayload() const
	{
		return m_Payload;
	}
}


