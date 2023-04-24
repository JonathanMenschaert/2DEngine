#pragma once
#include "BaseComponent.h"
#include "Observer.h"
#include "TextComponent.h"

namespace dae
{

	class LivesDisplayComponent final : public BaseComponent, public Observer<int>
	{
	public:
		LivesDisplayComponent(GameObject* pGameObject);
		virtual ~LivesDisplayComponent() = default;
		LivesDisplayComponent(const LivesDisplayComponent& rectComponent) = delete;
		LivesDisplayComponent(LivesDisplayComponent&& rectComponent) noexcept = delete;
		LivesDisplayComponent& operator=(const LivesDisplayComponent& rectComponent) = delete;
		LivesDisplayComponent& operator=(LivesDisplayComponent&& rectComponent) noexcept = delete;

		void Init() override;
		void Notify(const Event<int>& e) override;

	private:
		TextComponent* m_pText;
	};
}

