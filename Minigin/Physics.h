#pragma once
#include "Singleton.h"
#include "glm/glm.hpp"
#include "RectCollisionComponent.h"
#include <vector>

namespace dae
{
	class Physics final : public Singleton<Physics>
	{
	public:		

		Physics();
		~Physics() = default;
		Physics(const Physics& physics) = delete;
		Physics(Physics&& physics) noexcept = delete;
		Physics& operator=(const Physics& physics) = delete;
		Physics& operator=(Physics& physics) noexcept = delete;

		void HandleCollision();

		void AddPhysicsCollider(RectCollisionComponent* rectCollider);
		void RemovePhysicsCollider(RectCollisionComponent* rectCollider);

		//bool HasLineOfSight()

	private:
		bool CalculateCollisionOffset(const glm::vec4& box1, const glm::vec4& box2, glm::vec2& collisionOffset);
		bool HasTriggered(const glm::vec4& box1, const glm::vec4& box2);
		bool HasCollided(const glm::vec4& box1, const glm::vec4& box2, glm::vec2& collisionOffset);
		bool CompareLayers(const std::vector<std::string>& layers1, const std::vector<std::string>& layers2) const;

		std::vector<RectCollisionComponent*> m_DynamicColliders;
		std::vector<RectCollisionComponent*> m_StaticColliders;
		std::vector<RectCollisionComponent*> m_TriggerColliders;

		const glm::vec2 m_ZeroOffset;
	};
}

