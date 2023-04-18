#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"
namespace dae
{
	class HowToPlayComponent : public BaseComponent
	{
	public:
		HowToPlayComponent(std::shared_ptr<GameObject> pGameObject);
		virtual ~HowToPlayComponent() = default;
		HowToPlayComponent(const HowToPlayComponent& component) = delete;
		HowToPlayComponent(HowToPlayComponent&& component) noexcept = delete;
		HowToPlayComponent& operator=(const HowToPlayComponent& component) = delete;
		HowToPlayComponent& operator=(HowToPlayComponent&& component) noexcept = delete;

		virtual void OnGui() override;
		virtual void Init() override;
	private:
		TransformComponent* m_pTransform{ nullptr };
	};
}

