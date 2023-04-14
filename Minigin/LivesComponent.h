#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class LivesComponent : public BaseComponent, public Subject<int>
	{
	public:
		LivesComponent(std::shared_ptr<GameObject> pGameObject);
		~LivesComponent() = default;
		LivesComponent(const LivesComponent& rectComponent) = delete;
		LivesComponent(LivesComponent&& rectComponent) noexcept = delete;
		LivesComponent& operator=(const LivesComponent& rectComponent) = delete;
		LivesComponent& operator=(LivesComponent&& rectComponent) noexcept = delete;

		void AddLife(int lives = 1);
		void UpdateLives();
		int GetLives() const;

	private:
		int m_Lives;
	};
}
