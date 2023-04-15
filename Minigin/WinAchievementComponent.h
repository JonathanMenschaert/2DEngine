#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class WinAchievementComponent : public BaseComponent, public Observer<int>
	{
	public:
		WinAchievementComponent(std::shared_ptr<GameObject> pGameObject);
		~WinAchievementComponent() = default;
		WinAchievementComponent(const WinAchievementComponent& rectComponent) = delete;
		WinAchievementComponent(WinAchievementComponent&& rectComponent) noexcept = delete;
		WinAchievementComponent& operator=(const WinAchievementComponent& rectComponent) = delete;
		WinAchievementComponent& operator=(WinAchievementComponent&& rectComponent) noexcept = delete;

		void Notify(const Event<int>& e) override;
	private:
		const int m_WinScore;
	};
}


