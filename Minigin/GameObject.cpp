#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

const int dae::GameObject::m_NrOfComponentTypes{ static_cast<int>(ComponentType::COUNT) };

dae::GameObject::GameObject()
	:m_ComponentsMarkedForDeath{false}
	,m_ObjectMarkedForDeath{false}
{	
	for (int i{}; i < m_NrOfComponentTypes; ++i)
	{
		//Initialize a list in the map per component type
		m_Components[static_cast<ComponentType>(i)] = std::list<std::shared_ptr<BaseComponent>>{};
	}
}

void dae::GameObject::Init()
{

	if (!HasComponent<TransformComponent>())
	{
		AddComponent<TransformComponent>();
	}
	m_pTransform = GetComponent<TransformComponent>().lock();
	for (int i{}; i < m_NrOfComponentTypes; ++i)
	{
		ComponentType componentType{ static_cast<ComponentType>(i) };
		for (auto& pComponent : m_Components[componentType])
		{
			pComponent->Init();
		}
	}

	for (auto& pChild : m_Children)
	{
		pChild->Init();
	}
}

void dae::GameObject::Update()
{
	for (auto& pComponent : m_Components[ComponentType::Update])
	{
		pComponent->Update();
	}

	for (auto& pChild : m_Children)
	{
		pChild->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	if (m_ComponentsMarkedForDeath) DestroyComponents();
	DestroyChildren();
}

void dae::GameObject::Render() const
{
	for (const auto& pComponent : m_Components.at(ComponentType::Render))
	{
		pComponent->Render();
	}

	for (auto& pChild : m_Children)
	{
		pChild->Render();
	}
}

void dae::GameObject::OnGui()
{
	for (auto& componentPair : m_Components)
	{
		auto& componentList{ componentPair.second };
		for (auto& component : componentList)
		{
			component->OnGui();
		}
	}

	for (auto& pChild : m_Children)
	{
		pChild->OnGui();
	}
}

dae::TransformComponent* dae::GameObject::GetTransform() const
{
	return m_pTransform.get();
}


std::shared_ptr<dae::GameObject> dae::GameObject::GetParent()
{
	return m_pParent.lock();
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition)
{
	if (!IsValidParentOrNull(pParent)) return;
	
	
	std::shared_ptr<TransformComponent> pTransform{ GetComponent<TransformComponent>() };

	if (!pParent)
	{
		pTransform->SetLocalPosition(pTransform->GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
		{
			std::shared_ptr<TransformComponent> pParentTransform{ pParent->GetComponent<TransformComponent>() };
			pTransform->SetLocalPosition(pTransform->GetLocalPosition() - pParentTransform->GetWorldPosition());
		}
	}

	if (!m_pParent.expired())
	{
		m_pParent.lock()->RemoveChild(shared_from_this());
	}
	m_pParent = pParent;
	if (!m_pParent.expired())
	{
		m_pParent.lock()->AddChild(shared_from_this());
	}
}

void dae::GameObject::Destroy()
{
	m_ObjectMarkedForDeath = true;
	for (auto& pChild : m_Children)
	{
		pChild->Destroy();
	}
}

bool dae::GameObject::IsValidParentOrNull(std::weak_ptr<GameObject> pParent)
{
	return true;
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	m_Children.erase(std::remove_if(m_Children.begin(), m_Children.end(), [&child](const auto& childObj) {
		return childObj == child;
		}), m_Children.end());
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_Children.push_back(child);
}

std::list<std::shared_ptr<dae::GameObject>>& dae::GameObject::GetChildren()
{
	return m_Children;
}



void dae::GameObject::DestroyComponents()
{
	for (auto& componentPair : m_Components)
	{
		auto& componentList{ componentPair.second };
		if (componentList.size() > 0)
		{
			componentList.erase(std::remove_if(componentList.begin(), componentList.end(), [](auto& pElement)
				{
					return pElement->IsMarkedForDeath();
				}), componentList.end());
		}
	}
	m_ComponentsMarkedForDeath = false;
}

void dae::GameObject::DestroyChildren()
{	
	m_Children.erase(std::remove_if(m_Children.begin(), m_Children.end(), [](const auto& pElement)
		{
			return pElement->m_ObjectMarkedForDeath;
		}), m_Children.end());
}
