#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "glm/glm.hpp"
#include "TextureRenderComponent.h"

namespace dae
{
	class GhostComponent final : public BaseComponent
	{
	public:
		GhostComponent(GameObject* pGameObject);
		virtual ~GhostComponent() noexcept = default;
		GhostComponent(const GhostComponent& other) = delete;
		GhostComponent(GhostComponent&& other) noexcept = delete;
		GhostComponent& operator=(const GhostComponent& other) = delete;
		GhostComponent& operator=(GhostComponent&& other) noexcept = delete;


		virtual void Init() override;

		void SetSpawnPos(const glm::vec2& pos);
		void SetNormalTexture(std::shared_ptr<Texture2D>& pNormalTexture);
		void SetScaredTexture(std::shared_ptr<Texture2D>& pScaredTexture);

		void SetScared(bool isScared);
		bool IsScared() const;

	private:
		glm::vec2 m_SpawnPos{};
		std::shared_ptr<Texture2D> m_pNormalTexture{};
		std::shared_ptr<Texture2D> m_pScaredTexture{};
		
		TextureRenderComponent* m_pTextureRenderer{};
		bool m_IsScared;
	};
}

