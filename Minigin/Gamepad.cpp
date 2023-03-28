#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#include "Gamepad.h"
#include <algorithm>

using namespace dae;
class Gamepad::GamepadImpl
{
public:
	GamepadImpl(unsigned int controllerIdx)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		m_ControllerIdx = controllerIdx;
	}

	void Update()
	{
		m_PreviousState = m_CurrentState;
		XInputGetState(m_ControllerIdx, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button;
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}

	bool IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	void SetStickDeadzone(float percentage)
	{
		m_StickDeadzone = percentage;
	}

	void SetTriggerDeadzone(float percentage)
	{
		m_TriggerDeadzone = percentage;
	}

	float GetTrigger(BYTE trigger) const
	{
		const BYTE maxValue{ static_cast<BYTE>(MAXBYTE) };
		const BYTE deadZoneValue{ static_cast<BYTE>(m_TriggerDeadzone * maxValue) };
		const BYTE triggerClamped{ std::clamp(trigger, deadZoneValue, maxValue) };
		
		return static_cast<float>(triggerClamped - deadZoneValue) / static_cast<float>(maxValue - deadZoneValue);
	}

	float GetStick(SHORT stick) const
	{
		SHORT maxValue{ static_cast<SHORT>(MAXSHORT) };
		SHORT deadZoneValue{ static_cast<SHORT>(m_StickDeadzone * MAXSHORT) };

		SHORT sign{ stick >= 0 ? 1 : -1 };

		const SHORT stickClamped{ std::clamp(static_cast<SHORT>(abs(stick)), deadZoneValue, maxValue) };
		
		return static_cast<float>(stickClamped - deadZoneValue) / static_cast<float>((maxValue - deadZoneValue) * sign);		
	}

	float GetAnalogValue(AnalogButton axis) const
	{
		switch (axis)
		{
		case AnalogButton::LeftXStick:
			return GetStick(m_CurrentState.Gamepad.sThumbLX);
			break;
		case AnalogButton::LeftYStick:
			return GetStick(m_CurrentState.Gamepad.sThumbLX);
			break;
		case AnalogButton::RightXStick:
			return GetStick(m_CurrentState.Gamepad.sThumbRX);
			break;
		case AnalogButton::RightYStick:
			return GetStick(m_CurrentState.Gamepad.sThumbRX);
			break;
		case AnalogButton::RightTrigger:
			return GetTrigger(m_CurrentState.Gamepad.bRightTrigger);
			break;
		case AnalogButton::LeftTrigger:
			return GetTrigger(m_CurrentState.Gamepad.bLeftTrigger);
			break;
		}

		return 0.f;
	}
private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	unsigned int m_ControllerIdx{};
	float m_StickDeadzone{0.2f};
	float m_TriggerDeadzone{0.2f};
};

Gamepad::Gamepad(unsigned int controllerIdx)
	: m_pImpl{ std::make_unique<GamepadImpl>(controllerIdx)}
{	
}

Gamepad::~Gamepad()
{
	//Default constructor needs to be defined, otherwise compiler errors are generated.
}

void Gamepad::Update()
{
	m_pImpl->Update();
}

bool Gamepad::IsDown(DigitalButton button) const
{
	return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool Gamepad::IsUp(DigitalButton button) const
{
	return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool Gamepad::IsPressed(DigitalButton button) const
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

void dae::Gamepad::SetStickDeadzone(float percentage)
{
	m_pImpl->SetStickDeadzone(percentage);
}

float dae::Gamepad::GetAxis(AnalogButton button) const
{
	return m_pImpl->GetAnalogValue(button);
}

void dae::Gamepad::SetTriggerDeadzone(float percentage)
{
	m_pImpl->SetTriggerDeadzone(percentage);
}

