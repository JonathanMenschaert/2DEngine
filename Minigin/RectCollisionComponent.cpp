#include "RectCollisionComponent.h"
#include "Physics.h"
#include "GameObject.h"

dae::RectCollisionComponent::RectCollisionComponent(std::shared_ptr<GameObject> pGameObject)
    :BaseComponent(pGameObject)
{
}
void dae::RectCollisionComponent::Init()
{
    Physics::GetInstance().AddPhysicsCollider(this);
}

void dae::RectCollisionComponent::SetExtend(const glm::vec2& extend)
{
    m_Extend = extend;
}

void dae::RectCollisionComponent::SetLayers(const std::vector<std::string>& layers)
{
    m_Layers = layers;
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
        transform.x - m_Extend.x,
        transform.y - m_Extend.y,
        transform.x + m_Extend.x,
        transform.y + m_Extend.y
    };
}

const glm::vec2& dae::RectCollisionComponent::GetExtend() const
{
    return m_Extend;
}

dae::RectCollisionComponent::CollisionType dae::RectCollisionComponent::GetCollisionType() const
{
    return m_CollisonType;
}
