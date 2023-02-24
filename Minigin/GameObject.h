#pragma once
#include <memory>
#include "Transform.h"
#include "vector"
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		virtual void Update();
		virtual void Render() const;

		template <typename T>
		void AddComponent(std::shared_ptr<T> pComponent)
		{
			//Compile time check to make sure T is a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");
			m_Components.push_back(pComponent);
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
			return std::weak_ptr<T>();
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
		std::vector<std::shared_ptr<BaseComponent>> m_Components{};
	};
}
