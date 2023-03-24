#pragma once
namespace dae
{
	class Gamepad final
	{
	public:
		class GamepadImpl;
		enum class AnalogButton
		{
			LeftTrigger,
			RightTrigger,
			LeftXStick,
			LeftYStick,
			RightXStick,
			RightYStick
		};

		enum class GamepadButtonType
		{
			Digital,
			Stick,
			Trigger
		};

		enum class DigitalButton
		{
			DPadUp = 0x0001,
			DPadDown = 0x0002,
			DPadLeft = 0x0004,
			DPadRight = 0x0008,
			Start = 0x0010,
			Back = 0x0020,
			LeftThumb = 0x0040,
			RightThumb = 0x0080,
			LeftShoulder = 0x0100,
			RightShoulder = 0x0200,
			ButtonA = 0x1000,
			ButtonB = 0x2000,
			ButtonX = 0x4000,
			ButtonY = 0x8000
		};

		void Update();
		bool IsDown(DigitalButton button) const;
		bool IsUp(DigitalButton button) const;
		float GetAxis(AnalogButton button) const;
		bool IsPressed(DigitalButton button) const;
		void SetStickDeadzone(float percentage);
		void SetTriggerDeadzone(float percentage);

		explicit Gamepad(unsigned int controllerIdx);
		~Gamepad();
	private:		
		GamepadImpl* pImpl;
	};
}

