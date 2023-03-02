#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent();
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& baseComponent) = delete;
		BaseComponent(BaseComponent&& baseComponent) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& baseComponent) = delete;
		BaseComponent& operator=(BaseComponent&& baseComponent) noexcept = delete;

		void SetParent(std::weak_ptr<GameObject> pGameObject);

		virtual void Update();
		virtual void Render() const;

		void MarkForDeath();
		bool IsMarkedForDeath();

	protected:
		std::weak_ptr<GameObject> m_GameObject;

		bool m_Alive = true;
	};
}

