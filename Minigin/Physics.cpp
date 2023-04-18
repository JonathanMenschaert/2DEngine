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
				other->AddCollisionOffset(-collisionOffset);
			}
		}

		for (auto other : m_StaticColliders)
		{
			if (!HasCollided(collisionBox, other->GetCollisionBox(), collisionOffset))
			{
				continue;
			}
			if (CompareLayers(layers, other->GetLayers()))
			{
				collider->AddCollisionOffset(CalculateCollisionOffset(collisionBox, other->GetCollisionBox()));
			}
		}

		for (auto other : m_TriggerColliders)
		{
			if (HasTriggered(collisionBox, other->GetCollisionBox()))
			{
				if (CompareLayers(layers, other->GetLayers()))
				{				
					
				}
			}
		}
	}
}


void dae::Physics::AddPhysicsCollider(RectCollisionComponent* rectCollider)
{
	switch (rectCollider->GetCollisionType())
	{
	case RectCollisionComponent::CollisionType::DynamicCollision:
		m_DynamicColliders.push_back(rectCollider);
		break;
	case RectCollisionComponent::CollisionType::Trigger:
		m_TriggerColliders.push_back(rectCollider);
		break;
	case RectCollisionComponent::CollisionType::StaticCollision:
		m_StaticColliders.push_back(rectCollider);
		break;
	default:
		break;
	}
}


glm::vec2 dae::Physics::CalculateCollisionOffset(const glm::vec4& box1, const glm::vec4& box2)
{
	glm::vec2 offset{};
	const bool isBoxCollidingLeft{ box1.x >= box2.x && box1.x <= box2.z };
	const bool isBoxCollidingRight{ box1.z >= box2.x && box1.z <= box2.z };
	const bool isBoxCollidingTop{ box1.y >= box2.y && box1.y <= box2.w };
	const bool isBoxCollidingBottom{ box1.w >= box2.y && box1.w <= box2.w };

	float offsetX = 0.0f;
	float offsetY = 0.0f;

	if (isBoxCollidingRight && (isBoxCollidingBottom || isBoxCollidingTop))
	{
		offsetX = box2.x - box1.z;
	}
	else if (isBoxCollidingLeft && (isBoxCollidingBottom || isBoxCollidingTop))
	{
		offsetX = box2.z - box1.x;
	}
	
	if (isBoxCollidingBottom && (isBoxCollidingRight || isBoxCollidingLeft))
	{
		offsetY = box2.y - box1.w;
	}
	else if (isBoxCollidingTop && (isBoxCollidingRight || isBoxCollidingLeft))
	{
		offsetY = box2.w - box1.y;
	}

	if (!(offsetX == offsetY && offsetX == 0.f))
	{
		if (abs(offsetX) < abs(offsetY))
		{
			offset.x = offsetX;
		}
		else
		{
			offset.y = offsetY;
		}
	}

	return offset;
}

bool dae::Physics::HasTriggered(const glm::vec4& box1, const glm::vec4& box2)
{
	glm::vec2 collisionOffset = CalculateCollisionOffset(box1, box2);
	return collisionOffset != m_ZeroOffset;
}

bool dae::Physics::HasCollided(const glm::vec4& box1, const glm::vec4& box2, glm::vec2& collisionOffset)
{
	collisionOffset = CalculateCollisionOffset(box1, box2);
	return collisionOffset != m_ZeroOffset;
}

bool dae::Physics::CompareLayers(const std::vector<std::string>& layers1, const std::vector<std::string>& layers2) const
{
	std::vector<std::string> result;
	std::set_intersection(layers1.begin(), layers1.end(), layers2.begin(), layers2.end(), std::back_inserter(result));
	return !result.empty();
}
