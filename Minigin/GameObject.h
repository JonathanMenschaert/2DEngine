#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <list>
#include <unordered_map>
#include "BaseComponent.h"
#include <string>
#include "UpdateComponent.h"
#include "RenderComponent.h"

namespace dae
{
	enum class ComponentType
	{
		Update,
		Render,
		Data,

		//Define components types above
		COUNT
	};

	class Texture2D;
	class GameObject final
	{
	public:
		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void BeginUpdate();
		void EndUpdate();
		void Render() const;


		template <typename T>
		std::shared_ptr<T> AddComponent()
		{
			//Compile time check to make sure T is a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");

			ComponentType componentType{ ComponentType::Data };
			if (std::is_base_of<UpdateComponent, T>::value) componentType = ComponentType::Update;
			if (std::is_base_of<RenderComponent, T>::value) componentType = ComponentType::Render;
			
			std::shared_ptr<T> pComponent{ std::make_shared<T>()};
			//m_Components[componentType]
			std::list<std::shared_ptr<BaseComponent>>& componentList{ m_Components[componentType] };
			componentList.push_back(pComponent);
			return pComponent;			
		}

		template<typename T>
		std::weak_ptr<T> GetComponent() const
		{
			//Compile time check to make sure T is a component
			static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");

			ComponentType componentType{ ComponentType::Data };
			if (std::is_base_of<UpdateComponent, T>::value) componentType = ComponentType::Update;
			if (std::is_base_of<RenderComponent, T>::value) componentType = ComponentType::Render;

			//Loop over all components to find the requested component
			for (const auto& pComponent : m_Components.at(componentType))
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
					m_ComponentsMarkedForDeath = true;
				}
			}
		}

	private:
		void DestroyComponents();
		bool m_ComponentsMarkedForDeath;

		std::unordered_map<ComponentType, std::list<std::shared_ptr<BaseComponent>>> m_Components;

		static const int m_NrOfComponentTypes;
	};
}
