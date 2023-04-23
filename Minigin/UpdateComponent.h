#pragma once
#include "BaseComponent.h"

namespace dae
{
	class UpdateComponent : public BaseComponent
	{
	public:

		UpdateComponent(GameObject* pGameObject);
		virtual ~UpdateComponent() = default;
		UpdateComponent(const UpdateComponent& component) = delete;
		UpdateComponent(UpdateComponent&& component) noexcept = delete;
		UpdateComponent& operator=(const UpdateComponent& component) = delete;
		UpdateComponent& operator=(UpdateComponent&& component) noexcept = delete;

		void Update() override = 0;
	};
}

