#pragma once
#include "BaseComponent.h"
#include "TextComponent.h"
namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent() = default;
		~FPSComponent() = default;
		FPSComponent(const FPSComponent& component) = delete;
		FPSComponent(FPSComponent&& component) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& component) = delete;
		FPSComponent& operator=(FPSComponent&& component) noexcept = delete;

		void Update() override;
		void SetUpdateTimer(float seconds);

	private:
		std::weak_ptr<TextComponent> m_TextComponent{};
		float m_UpdateTimer;
		float m_MaxTimer;
	};
}

