#include "RenderComponent.h"
#include "GameObject.h"

dae::RenderComponent::RenderComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

void dae::RenderComponent::Init()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}


