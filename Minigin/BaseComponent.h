#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(GameObject* pGameObject);
		~BaseComponent() = default;
		BaseComponent(const BaseComponent& baseComponent) = delete;
		BaseComponent(BaseComponent&& baseComponent) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& baseComponent) = delete;
		BaseComponent& operator=(BaseComponent&& baseComponent) noexcept = delete;

		virtual void Update();
		virtual void Render() const;

		void MarkForDeath();
		bool IsMarkedForDeath();

	protected:
		GameObject* m_GameObject{ nullptr };

		bool m_Alive = true;
	};
}

