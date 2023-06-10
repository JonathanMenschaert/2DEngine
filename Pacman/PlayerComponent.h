#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "RectCollisionComponent.h"
#include "Subject.h"
#include "PlayerEvents.h"

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

		void Notify(const Event<dae::CollisionData>& e) override;
	private:
		unsigned int m_PacDotSoundIdx;
		const std::string m_PacDotSoundName;

	};
}

