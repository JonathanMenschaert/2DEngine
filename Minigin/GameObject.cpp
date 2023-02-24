#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::Update() 
{
	for (std::shared_ptr<BaseComponent>& component : m_Components)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for (const std::shared_ptr<BaseComponent>& pComponent : m_Components)
	{
		pComponent->Render();
	}
}