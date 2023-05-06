#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent(GameObject* pGameObject);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& component) = delete;
		RenderComponent(RenderComponent&& component) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& component) = delete;
		RenderComponent& operator=(RenderComponent&& component) noexcept = delete;

		void Init() override;

	protected:
		TransformComponent* m_pTransform{};
	};

}

