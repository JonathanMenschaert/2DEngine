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
		RenderComponent() = default;
		~RenderComponent() = default;
		RenderComponent(const RenderComponent& component) = delete;
		RenderComponent(RenderComponent&& component) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& component) = delete;
		RenderComponent& operator=(RenderComponent&& component) noexcept = delete;

		void Render() const override;
		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetTexture(const std::string& fileName);

	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}

