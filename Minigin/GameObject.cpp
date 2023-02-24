#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update() 
{
	for (std::shared_ptr<BaseComponent>& component : m_Components)
	{
		component->Update();
	}
}

void dae::GameObject::LateUpdate()
{
	if (m_Components.size() > 0)
	{
		m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(), [](std::shared_ptr<BaseComponent>& element)
			{
				return element->IsMarkedForDeath();
			}));
	}
}



void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);

	for (const std::shared_ptr<BaseComponent>& component : m_Components)
	{
		component->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}