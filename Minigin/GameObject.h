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
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject();
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Init();
		void Update();
		void LateUpdate();
		void Render() const;

		std::list<std::weak_ptr<GameObject>>& GetChildren();

		std::shared_ptr<dae::GameObject> GetParent();

		void SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition);

		template <typename T>
		std::shared_ptr<T> AddComponent();

		template<typename T>
		std::weak_ptr<T> GetComponent() const;

		template<typename T>
		void RemoveComponent();

		template<typename T>
		bool HasComponent() const;

	private:
		void DestroyComponents();

		bool IsValidParentOrNull(std::weak_ptr<GameObject> pParent);
		void RemoveChild(std::weak_ptr<GameObject> child);
		void AddChild(std::weak_ptr<GameObject> child);

		template <typename T>
		void AssertType() const;

		template <typename T>
		ComponentType GetComponentType() const;

		bool m_ComponentsMarkedForDeath;
		std::unordered_map<ComponentType, std::list<std::shared_ptr<BaseComponent>>> m_Components;

		std::weak_ptr<GameObject> m_pParent{};
		std::list<std::weak_ptr<GameObject>> m_Children;

		static const int m_NrOfComponentTypes;
	};

	template <typename T>
	std::shared_ptr<T> GameObject::AddComponent()
	{
		//Compile time check to make sure T is a component
		AssertType<T>();

		//Get Component type
		ComponentType componentType{ GetComponentType<T>() }; 	

		std::shared_ptr<T> pComponent{ std::make_shared<T>(shared_from_this()) };

		std::list<std::shared_ptr<BaseComponent>>& componentList{ m_Components[componentType] };
		componentList.push_back(pComponent);
		return pComponent;
	}

	template<typename T>
	std::weak_ptr<T> GameObject::GetComponent() const
	{
		//Compile time check to make sure T is a component
		AssertType<T>();

		//Get Component type
		ComponentType componentType{ GetComponentType<T>() };

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
	bool GameObject::HasComponent() const
	{
		//Compile time check to make sure T is a component
		AssertType<T>();

		//Get Component type
		ComponentType componentType{ GetComponentType<T>() };

		//Loop over all components to find the requested component
		for (const auto& pComponent : m_Components.at(componentType))
		{
			std::shared_ptr<T> pRequestedComponent{ std::dynamic_pointer_cast<T>(pComponent) };
			if (pRequestedComponent)
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	void GameObject::RemoveComponent()
	{
		//Compile time check to make sure T is a component
		static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");

		//Loop over all components to find the correct component to remove
		//All instances of the component T will be marked for death
		for (auto& componentPair : m_Components)
		{
			for (std::shared_ptr<BaseComponent> pComponent : componentPair.second)
			{
				std::shared_ptr<T> pRequestedComponent{ std::dynamic_pointer_cast<T>(pComponent) };
				if (pRequestedComponent)
				{
					pRequestedComponent->MarkForDeath();
					m_ComponentsMarkedForDeath = true;
				}
			}
		}
	}

	template <typename T>
	void GameObject::AssertType() const
	{
		static_assert(std::is_base_of<BaseComponent, T>::value, "T is not derived from BaseComponent!");
	}

	template <typename T>
	ComponentType GameObject::GetComponentType() const
	{
		ComponentType componentType{ ComponentType::Data };
		if (std::is_base_of<UpdateComponent, T>::value)
		{
			componentType = ComponentType::Update;
		}
		else if (std::is_base_of<RenderComponent, T>::value)
		{
			componentType = ComponentType::Render;
		}
		return componentType;
	}

}
