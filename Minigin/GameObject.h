#pragma once
#include <memory>
#include "Transform.h"
#include "vector"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject
	{
	public:
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <typename T>
		void AddComponent(std::shared_ptr<T> component)
		{
			//Compile time check to make sure T is a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");
			m_Components.push_back(component);
		}

		template<typename T>
		std::weak_ptr<T> GetComponent() const
		{
			//Compile time check to make sure T is a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");

			//Loop over all components to find the requested component
			for (const std::shared_ptr<BaseComponent>& pComponent : m_Components)
			{
				std::shared_ptr<T> pRequestedComponent{ std::dynamic_pointer_cast<T>(pComponent) };
				if (pRequestedComponent)
				{
					std::weak_ptr<T> pWeakComponent{ pRequestedComponent };
					return pWeakComponent;
				}
			}
			return nullptr;
		}

		template<typename T>
		void RemoveComponent()
		{
			//Compile time check to make sure T is a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");

			//Loop over all components to find the correct component to remove
			//All instances of the component T will be marked for death
			for (const std::shared_ptr<BaseComponent>& pComponent : m_Components)
			{
				std::shared_ptr<T> pRequestedComponent{ std::dynamic_pointer_cast<T>(pComponent) };
				if (pRequestedComponent)
				{
					pRequestedComponent->MarkForDeath();
				}
			}
		}

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
	};
}
