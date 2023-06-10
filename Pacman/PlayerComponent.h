#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "RectCollisionComponent.h"
#include "Subject.h"
#include "PlayerEvents.h"
#include "TransformComponent.h"

namespace dae
{
	class PlayerComponent final : public BaseComponent, public Subject<PlayerEvent>, public Observer<dae::CollisionData>
	{
	public:
		PlayerComponent(GameObject* pGameObject);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& rectComponent) = delete;
		PlayerComponent(PlayerComponent&& rectComponent) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& rectComponent) = delete;
		PlayerComponent& operator=(PlayerComponent&& rectComponent) noexcept = delete;

		virtual void Init() override;
		virtual void Notify(const Event<dae::CollisionData>& e) override;
		void SetSpawnPos(const glm::vec2& spawnPos);

	private:

		void Respawn();
		unsigned int m_PacDotSoundIdx;
		const std::string m_PacDotSoundName;

		unsigned int m_DeathSoundIdx;
		const std::string m_DeathSoundName;

		unsigned int m_EatGhostSoundIdx;
		const std::string m_EatGhostSoundName;

		TransformComponent* m_pTransform{};
		glm::vec2 m_SpawnPos;

	};
}

