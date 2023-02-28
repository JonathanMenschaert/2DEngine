#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

const int dae::GameObject::m_NrOfComponentTypes{ static_cast<int>(ComponentType::COUNT) };

dae::GameObject::GameObject()
	:m_ComponentsMarkedForDeath{false}
{
	
	for (int i{}; i < m_NrOfComponentTypes; ++i)
	{
		//Initialize a list in the map per component type
		m_Components[static_cast<ComponentType>(i)];
	}
}

void dae::GameObject::BeginUpdate()
{
	for (auto& pComponent : m_Components[ComponentType::Update])
	{
		pComponent->Update();
	}
}

void dae::GameObject::EndUpdate()
{
	if (m_ComponentsMarkedForDeath) DestroyComponents();
}

void dae::GameObject::Render() const
{
	for (const auto& pComponent : m_Components.at(ComponentType::Render))
	{
		pComponent->Render();
	}
}

void dae::GameObject::DestroyComponents()
{
	for (auto& componentPair : m_Components)
	{
		auto& componentList{ componentPair.second };
		if (componentList.size() > 0)
		{
			componentList.erase(std::remove_if(componentList.begin(), componentList.end(), [](auto& element)
				{
					return element->IsMarkedForDeath();
				}));
		}
	}
	m_ComponentsMarkedForDeath = false;
}
