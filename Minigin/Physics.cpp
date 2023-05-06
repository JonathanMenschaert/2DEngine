#include "Physics.h"
#include <algorithm>
#include <iterator>
#include <iostream>
dae::Physics::Physics()
	:m_ZeroOffset{glm::vec2{0.f, 0.f}}
{
}
void dae::Physics::HandleCollision()
{
	for (auto collider : m_DynamicColliders)
	{
		const std::vector<std::string>& layers{ collider->GetLayers() };
		const glm::vec4 collisionBox{ collider->GetCollisionBox() };
		glm::vec2 collisionOffset{ };

		for (auto other : m_DynamicColliders)
		{
			if (collider == other || !HasCollided(collisionBox, other->GetCollisionBox(), collisionOffset))
			{
				continue;
			}
			
			if (CompareLayers(layers, other->GetLayers()))
			{
				collisionOffset *= 0.5f;
				collider->AddCollisionOffset(collisionOffset);
				collider->TriggerCollisionEvent(other->GetGameObject(), CollisionType::DynamicCollision);
				other->AddCollisionOffset(-collisionOffset);
				other->TriggerCollisionEvent(collider->GetGameObject(), CollisionType::DynamicCollision);
			}
		}

		for (auto other : m_StaticColliders)
		{
			if (!HasCollided(collisionBox, other->GetCollisionBox(), collisionOffset))
			{
				continue;
			}
			auto test = other->GetCollisionBox();
			if (CompareLayers(layers, other->GetLayers()))
			{
				collider->AddCollisionOffset(collisionOffset);
				collider->TriggerCollisionEvent(other->GetGameObject(), CollisionType::StaticCollision);
			}
		}

		for (auto other : m_TriggerColliders)
		{
			if (HasTriggered(collisionBox, other->GetCollisionBox()))
			{
				if (CompareLayers(layers, other->GetLayers()))
				{				
					collider->TriggerCollisionEvent(other->GetGameObject(), CollisionType::Trigger);
					//std::cout << "Trigger hit\n";
				}
			}
		}
	}
}


void dae::Physics::AddPhysicsCollider(RectCollisionComponent* rectCollider)
{
	switch (rectCollider->GetCollisionType())
	{
	case CollisionType::DynamicCollision:
		m_DynamicColliders.push_back(rectCollider);
		break;
	case CollisionType::Trigger:
		m_TriggerColliders.push_back(rectCollider);
		break;
	case CollisionType::StaticCollision:
		m_StaticColliders.push_back(rectCollider);
		break;
	default:
		break;
	}
}

void dae::Physics::RemovePhysicsCollider(RectCollisionComponent* rectCollider)
{
	switch (rectCollider->GetCollisionType())
	{
	case CollisionType::DynamicCollision:
		if (m_DynamicColliders.size() == 0)
		{
			return;
		}
		m_DynamicColliders.erase(std::remove(m_DynamicColliders.begin(), m_DynamicColliders.end(), rectCollider), m_DynamicColliders.end());
		break;
	case CollisionType::Trigger:
		if (m_TriggerColliders.size() == 0)
		{
			return;
		}
		m_TriggerColliders.erase(std::remove(m_TriggerColliders.begin(), m_TriggerColliders.end(), rectCollider), m_TriggerColliders.end());
		break;
	case CollisionType::StaticCollision:
		if (m_StaticColliders.size() == 0)
		{
			return;
		}
		m_StaticColliders.erase(std::remove(m_StaticColliders.begin(), m_StaticColliders.end(), rectCollider), m_StaticColliders.end());
		break;
	default:
		break;
	}
}


bool dae::Physics::CalculateCollisionOffset(const glm::vec4& box1, const glm::vec4& box2, glm::vec2& collisionOffset)
{
	glm::vec2 offset{};
	const bool isBoxCollidingLeft{ box1.x >= box2.x && box1.x <= box2.z };
	const bool isBoxCollidingRight{ box1.z >= box2.x && box1.z <= box2.z };
	const bool isBoxCollidingTop{ box1.y >= box2.y && box1.y <= box2.w };
	const bool isBoxCollidingBottom{ box1.w >= box2.y && box1.w <= box2.w };
	const bool isBoxCollidingLeftRight{ box1.x <= box2.x && box1.z >= box2.z };
	const bool isBoxCollidingTopBottom{ box1.y <= box2.y && box1.w >= box2.w };

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	if (isBoxCollidingRight && (isBoxCollidingBottom || isBoxCollidingTop || isBoxCollidingTopBottom))
	{
		offsetX = box2.x - box1.z;
	}
	else if (isBoxCollidingLeft && (isBoxCollidingBottom || isBoxCollidingTop || isBoxCollidingTopBottom))
	{
		offsetX = box2.z - box1.x;
	}
	
	if (isBoxCollidingBottom && (isBoxCollidingRight || isBoxCollidingLeft || isBoxCollidingLeftRight))
	{
		offsetY = box2.y - box1.w;
	}
	else if (isBoxCollidingTop && (isBoxCollidingRight || isBoxCollidingLeft || isBoxCollidingLeftRight))
	{
		offsetY = box2.w - box1.y;
	}

	if (!(offsetX == offsetY && offsetX == 0.f))
	{
		
		if (isBoxCollidingLeftRight)
		{
			offset.y = offsetY;
		}
		else if (isBoxCollidingTopBottom)
		{
			offset.x = offsetX;
		}
		else if (abs(offsetX) < abs(offsetY))
		{
			offset.x = offsetX;
		}
		else
		{
			offset.y = offsetY;
		}
		collisionOffset = offset;
		return true;
	}

	collisionOffset = offset;
	return false;	
}

bool dae::Physics::HasTriggered(const glm::vec4& box1, const glm::vec4& box2)
{
	glm::vec2 collisionOffset{};
	return CalculateCollisionOffset(box1, box2, collisionOffset);
}

bool dae::Physics::HasCollided(const glm::vec4& box1, const glm::vec4& box2, glm::vec2& collisionOffset)
{	
	return CalculateCollisionOffset(box1, box2, collisionOffset);
}

bool dae::Physics::CompareLayers(const std::vector<std::string>& layers1, const std::vector<std::string>& layers2) const
{
	std::vector<std::string> result;
	std::set_intersection(layers1.begin(), layers1.end(), layers2.begin(), layers2.end(), std::back_inserter(result));
	return !result.empty();
}
