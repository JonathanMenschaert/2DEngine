#include "Physics.h"
#include <algorithm>
#include <iterator>
void dae::Physics::HandleCollision()
{
	for (auto collider : m_DynamicColliders)
	{
		for (auto other : m_DynamicColliders)
		{
			if (collider == other)
			{
				continue;
			}
			if (CompareLayers(collider->GetLayers(), other->GetLayers()))
			{
				collider->AddCollisionOffset(CalculateCollisionOffset(collider->GetCollisionBox(), other->GetCollisionBox()));
			}
		}

		for (auto other : m_StaticColliders)
		{
			if (CompareLayers(collider->GetLayers(), other->GetLayers()))
			{
				collider->AddCollisionOffset(CalculateCollisionOffset(collider->GetCollisionBox(), other->GetCollisionBox()));
			}
		}

		for (auto other : m_TriggerColliders)
		{
			if (CompareLayers(collider->GetLayers(), other->GetLayers()))
			{

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
	if (box1.z > box2.x && box1.z < box2.z)
	{
		offset.x = box2.x - box1.z;
	}
	else if (box1.x > box2.x && box1.x < box2.z)
	{
		offset.x = box2.z - box1.x;
	}

	if (box1.w > box2.y && box1.w < box2.w)
	{
		offset.y = box2.y - box1.w;
	}
	else if (box1.y > box2.y && box1.y < box2.w)
	{
		offset.y = box2.w - box1.y;
	}
	return offset;
}

bool dae::Physics::CompareLayers(const std::vector<std::string>& layers1, const std::vector<std::string>& layers2) const
{
	std::vector<std::string> result;
	std::set_intersection(layers1.begin(), layers1.end(), layers2.begin(), layers2.end(), std::back_inserter(result));
	return !result.empty();
}
