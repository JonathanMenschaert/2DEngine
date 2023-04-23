#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include <string>

namespace dae
{
	class RenderComponent final : public BaseComponent
	{
	public:
		RenderComponent(GameObject* pGameObject);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& component) = delete;
		RenderComponent(RenderComponent&& component) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& component) = delete;
		RenderComponent& operator=(RenderComponent&& component) noexcept = delete;

		void Render() const override;
		void Init() override;
		void SetTexture(std::shared_ptr<Texture2D> pTexture);
		void SetTexture(const std::string& fileName);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		TransformComponent* m_pTransform{};
	};
}

