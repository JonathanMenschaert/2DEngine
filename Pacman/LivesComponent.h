#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Observer.h"
#include "PlayerEvents.h"

namespace dae
{
	class LivesComponent : public BaseComponent, public Subject<int>, public Observer<PlayerEvent>
	{
	public:
		LivesComponent(GameObject* pGameObject);
		~LivesComponent() = default;
		LivesComponent(const LivesComponent& rectComponent) = delete;
		LivesComponent(LivesComponent&& rectComponent) noexcept = delete;
		LivesComponent& operator=(const LivesComponent& rectComponent) = delete;
		LivesComponent& operator=(LivesComponent&& rectComponent) noexcept = delete;


		void Notify(const Event<PlayerEvent>& e) override;
		void AddLife(int lives = 1);
		void UpdateLives();
		int GetLives() const;

	private:
		int m_Lives;
	};
}
