#pragma once
#include "UpdateComponent.h"
#include "TransformComponent.h"
namespace dae
{
	class RotatorComponent final : public UpdateComponent
	{
	public:
		RotatorComponent(GameObject* pGameObject);
		virtual ~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& component) = delete;
		RotatorComponent(RotatorComponent&& component) noexcept = delete;
		RotatorComponent& operator=(const RotatorComponent& component) = delete;
		RotatorComponent& operator=(RotatorComponent&& component) noexcept = delete;

		void Init() override;
		void Update() override;

		void SetRotationSpeed(float degPerSec);

	private:
		TransformComponent* m_pTransform{};		
		float m_RotationSpeed;
	};
}

