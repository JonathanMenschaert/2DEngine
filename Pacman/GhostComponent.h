#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "glm/glm.hpp"
#include "TextureRenderComponent.h"
#include "Observer.h"
#include "RectCollisionComponent.h"
#include "TransformComponent.h"
#include "PlayerEvents.h"

namespace dae
{
	class GhostComponent final : public BaseComponent, public Observer<dae::CollisionData>, public Observer<PlayerEvent>
	{
	public:
		GhostComponent(GameObject* pGameObject);
		virtual ~GhostComponent() noexcept = default;
		GhostComponent(const GhostComponent& other) = delete;
		GhostComponent(GhostComponent&& other) noexcept = delete;
		GhostComponent& operator=(const GhostComponent& other) = delete;
		GhostComponent& operator=(GhostComponent&& other) noexcept = delete;


		virtual void Init() override;
		
		void Notify(const Event<PlayerEvent>& e) override;
		void Notify(const Event<dae::CollisionData>& e) override;
		void SetSpawnPos(const glm::vec2& pos);
		void SetNormalTexture(std::shared_ptr<Texture2D>& pNormalTexture);
		void SetScaredTexture(std::shared_ptr<Texture2D>& pScaredTexture);

		bool IsScared() const;

	private:


		void SetScared(bool isScared);
		glm::vec2 m_SpawnPos{};
		std::shared_ptr<Texture2D> m_pNormalTexture{};
		std::shared_ptr<Texture2D> m_pScaredTexture{};
		
		TransformComponent* m_pTransform{};
		TextureRenderComponent* m_pTextureRenderer{};
		bool m_IsScared;
	};
}

