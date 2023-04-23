#pragma once
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& baseComponent) = delete;
		BaseComponent(BaseComponent&& baseComponent) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& baseComponent) = delete;
		BaseComponent& operator=(BaseComponent&& baseComponent) noexcept = delete;
		
		virtual void Init();
		virtual void Update();
		virtual void Render() const;
		virtual void OnGui();

		void MarkForDeath();
		bool IsMarkedForDeath();

	protected:
		explicit BaseComponent(GameObject* pGameObject);
		GameObject* GetGameObject() const;

	private:
		GameObject* m_pGameObject;
		bool m_Alive = true;
	};
}

