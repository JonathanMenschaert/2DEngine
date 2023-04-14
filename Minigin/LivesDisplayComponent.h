#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class LivesDisplayComponent : public BaseComponent, public Observer
	{
	public:
		LivesDisplayComponent(std::shared_ptr<GameObject> pGameObject);
		~LivesDisplayComponent() = default;
		LivesDisplayComponent(const LivesDisplayComponent& rectComponent) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& rectComponent) noexcept = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& rectComponent) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& rectComponent) noexcept = delete;

		void Notify(const Event& e);
	};
}

