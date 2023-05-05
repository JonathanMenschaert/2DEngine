#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PickupComponent final : public BaseComponent
	{
	public:

		PickupComponent(GameObject* pGameObject);
		virtual ~PickupComponent() = default;
		PickupComponent(const PickupComponent& rectComponent) = delete;
		PickupComponent(PickupComponent&& rectComponent) noexcept = delete;
		PickupComponent& operator=(const PickupComponent& rectComponent) = delete;
		PickupComponent& operator=(PickupComponent&& rectComponent) noexcept = delete;

		void SetPoints(int points);
		int GetPoints() const;

	private:
		int m_Points{ 0 };
	};
}

