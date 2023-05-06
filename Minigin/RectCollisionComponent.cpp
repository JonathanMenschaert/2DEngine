#include "RectCollisionComponent.h"
#include "Physics.h"
#include "GameObject.h"
#include <algorithm>
#include "Renderer.h"
#include "SDL.h"

dae::RectCollisionComponent::RectCollisionComponent(GameObject* pGameObject)
    :RenderComponent{ pGameObject }
{
}
dae::RectCollisionComponent::~RectCollisionComponent()
{
    Physics::GetInstance().RemovePhysicsCollider(this);
}
void dae::RectCollisionComponent::Init()
{
    Physics::GetInstance().AddPhysicsCollider(this);
}

void dae::RectCollisionComponent::SetCollisionBox(const glm::vec2& size, const glm::vec2& offset)
{
    m_Size = size;
    m_Offset = offset;
}

void dae::RectCollisionComponent::SetLayers(const std::vector<std::string>& layers)
{
    m_Layers = layers;
    std::sort(m_Layers.begin(), m_Layers.end());
}

void dae::RectCollisionComponent::SetCollisionType(CollisionType type)
{
    m_CollisonType = type;
}

void dae::RectCollisionComponent::AddCollisionOffset(const glm::vec2& offset)
{
    GetGameObject()->GetTransform()->Translate(offset);

}

const std::vector<std::string>& dae::RectCollisionComponent::GetLayers() const
{
    return m_Layers;
}

glm::vec4 dae::RectCollisionComponent::GetCollisionBox() const
{
    auto transform = GetGameObject()->GetTransform()->GetWorldPosition();
    //Return bottom left and top right corners
    return glm::vec4{
        transform.x + m_Offset.x,
        transform.y + m_Offset.y,
        transform.x + m_Size.x + m_Offset.x,
        transform.y + m_Size.y + m_Offset.y
    };
}

const glm::vec2& dae::RectCollisionComponent::GetExtend() const
{
    return m_Size;
}

dae::CollisionType dae::RectCollisionComponent::GetCollisionType() const
{
    return m_CollisonType;
}

void dae::RectCollisionComponent::TriggerCollisionEvent(GameObject* pGameObj, CollisionType type)
{
    CollisionData data{};
    data.type = type;
    data.pGameObject = pGameObj;

    Event<dae::CollisionData> collisionEvent{data};

    NotifyObservers(collisionEvent);
}

void dae::RectCollisionComponent::Render() const
{
    /*auto transform = GetGameObject()->GetTransform()->GetWorldPosition();
    SDL_SetRenderDrawColor(Renderer::GetInstance().GetSDLRenderer(), 255, 255, 255, 255);
    SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(),
        static_cast<int>(transform.x + m_Offset.x),
        static_cast<int>(transform.y + m_Offset.y), 
        static_cast<int>(transform.x + m_Offset.x),
        static_cast<int>(transform.y + m_Size.y + m_Offset.y));

    SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(),
        static_cast<int>(transform.x + m_Offset.x),
        static_cast<int>(transform.y + m_Offset.y),
        static_cast<int>(transform.x + m_Size.x + m_Offset.x),
        static_cast<int>(transform.y + m_Offset.y));

    SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(),
        static_cast<int>(transform.x + m_Size.x + m_Offset.x),
        static_cast<int>(transform.y + m_Offset.y),
        static_cast<int>(transform.x + m_Size.x + m_Offset.x),
        static_cast<int>(transform.y + m_Size.y + m_Offset.y));

    SDL_RenderDrawLine(Renderer::GetInstance().GetSDLRenderer(),
        static_cast<int>(transform.x + m_Offset.x),
        static_cast<int>(transform.y + m_Size.y + m_Offset.y),
        static_cast<int>(transform.x + m_Size.x + m_Offset.x),
        static_cast<int>(transform.y + m_Size.y + m_Offset.y));*/
}
