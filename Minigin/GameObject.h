#pragma once
#include <memory>
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
		void OnGui();

		TransformComponent* GetTransform() const;

		std::list<std::shared_ptr<GameObject>>& GetChildren();

		std::shared_ptr<dae::GameObject> GetParent();

		void SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition = true);

		void Destroy();

		template <typename T>
		T* AddComponent();

		template<typename T>
		T* GetComponent() const;

		template<typename T>
		std::vector<T*> GetComponents() const;

		template<typename T>
		T* GetComponentInParent() const;

		template<typename T>
		void RemoveComponent();

		template<typename T>
		bool HasComponent() const;

	private:
		void DestroyComponents();
		void DestroyChildren();
		bool IsValidParentOrNull(std::weak_ptr<GameObject> pParent);
		void RemoveChild(std::shared_ptr<GameObject> child);
		void AddChild(std::shared_ptr<GameObject> child);

		template <typename T>
		void AssertType() const;

		template <typename T>
		ComponentType GetComponentType() const;

		bool m_ObjectMarkedForDeath;
		bool m_ComponentsMarkedForDeath;
		std::unordered_map<ComponentType, std::list<std::unique_ptr<BaseComponent>>> m_Components;

		std::weak_ptr<GameObject> m_pParent{};
		std::list<std::shared_ptr<GameObject>> m_Children;

		TransformComponent* m_pTransform;

		static const int m_NrOfComponentTypes;
	};

	template <typename T>
	T* GameObject::AddComponent()
	{
		//Compile time check to make sure T is a component
		AssertType<T>();

		//Get Component type
		ComponentType componentType{ GetComponentType<T>() }; 	

		std::unique_ptr<T> pComponent{ std::make_unique<T>(shared_from_this().get())};

		T* pComponentRaw = pComponent.get();

		std::list<std::unique_ptr<BaseComponent>>& componentList{ m_Components[componentType] };
		componentList.push_back(std::move(pComponent));
		return pComponentRaw;
	}

	template<typename T>
	T* GameObject::GetComponent() const
	{
		//Compile time check to make sure T is a component
		AssertType<T>();

		//Get Component type
		ComponentType componentType{ GetComponentType<T>() };

		//Loop over all components to find the requested component
		for (const auto& pComponent : m_Components.at(componentType))
		{
			T* pRequestedComponent{ dynamic_cast<T*>(pComponent.get()) };
			if (pRequestedComponent)
			{
				return pRequestedComponent;
			}
		}
		return nullptr;
	}

	template<typename T>
	std::vector<T*> GameObject::GetComponents() const
	{
		//Compile time check to make sure T is a component
		AssertType<T>();

		//Get Component type
		ComponentType componentType{ GetComponentType<T>() };
		std::vector<T*> requestedComponents{};
		//Loop over all components to find the requested component
		for (const auto& pComponent : m_Components.at(componentType))
		{
			T* pRequestedComponent{ dynamic_cast<T*>(pComponent.get()) };
			if (pRequestedComponent)
			{
				requestedComponents.emplace_back(pRequestedComponent);
			}
		}
		return requestedComponents;
	}

	template<typename T>
	T* GameObject::GetComponentInParent() const
	{
		if (!m_pParent.expired())
		{
			return m_pParent.lock()->GetComponent<T>();
		}
		
		return nullptr;
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
			T* pRequestedComponent{ dynamic_cast<T*>(pComponent.get()) };
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
		AssertType<T>();

		T* pComponentRaw{ GetComponent<T>() };
		if (pComponentRaw)
		{
			pComponentRaw->MarkForDeath();
			m_ComponentsMarkedForDeath = true;
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
