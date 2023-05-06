#pragma once
#include "BaseComponent.h"
#include "RenderComponent.h"
#include "Texture2D.h"
#include "TransformComponent.h"
#include <string>

namespace dae
{
	class TextureRenderComponent : public RenderComponent
	{
	public:
		TextureRenderComponent(GameObject* pGameObject);
		virtual ~TextureRenderComponent() = default;
		TextureRenderComponent(const TextureRenderComponent& component) = delete;
		TextureRenderComponent(TextureRenderComponent&& component) noexcept = delete;
		TextureRenderComponent& operator=(const TextureRenderComponent& component) = delete;
		TextureRenderComponent& operator=(TextureRenderComponent&& component) noexcept = delete;

		void Render() const override;
		void SetTexture(std::shared_ptr<Texture2D> pTexture);
		void SetTexture(const std::string& fileName);

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		
	};
}

