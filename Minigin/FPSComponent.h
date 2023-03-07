#pragma once
#include "UpdateComponent.h"
#include "TextComponent.h"
#include <deque>
namespace dae
{
	class FPSComponent final : public UpdateComponent
	{
	public:
		FPSComponent(std::shared_ptr<GameObject> pGameObject);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& component) = delete;
		FPSComponent(FPSComponent&& component) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& component) = delete;
		FPSComponent& operator=(FPSComponent&& component) noexcept = delete;

		void Update() override;
		void SetUpdateTimer(float seconds);

	private:
		const int m_MaxStoredFPS{ 10 };
		std::deque<int> m_FPSRollingAverage{};
		std::weak_ptr<TextComponent> m_pTextComponent{};
		float m_UpdateTimer;
		float m_MaxTimer;
	};
}

