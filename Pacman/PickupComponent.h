#pragma once
#include "BaseComponent.h"

namespace dae
{
	enum class PickupType
	{
		Pacdot,
		PowerPellet
	};

	class PickupComponent final : public BaseComponent
	{
	public:

		PickupComponent(GameObject* pGameObject);
		virtual ~PickupComponent() = default;
		PickupComponent(const PickupComponent& rectComponent) = delete;
		PickupComponent(PickupComponent&& rectComponent) noexcept = delete;
		PickupComponent& operator=(const PickupComponent& rectComponent) = delete;
		PickupComponent& operator=(PickupComponent&& rectComponent) noexcept = delete;
		
		void SetType(PickupType type);
		PickupType GetType() const;

	private:
		PickupType m_PickupType{ PickupType::Pacdot };
	};
}

