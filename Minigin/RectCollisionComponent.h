#pragma once
#include "glm/glm.hpp"
#include "BaseComponent.h"
#include <string>
#include <vector>
#include "Subject.h"

namespace dae
{

	enum class CollisionType
	{
		DynamicCollision,
		Trigger,
		StaticCollision
	};

	struct CollisionData
	{
		CollisionType type;
		GameObject* pGameObject;
	};

	class RectCollisionComponent final : public BaseComponent, public Subject<CollisionData>
	{
	public:
		RectCollisionComponent(GameObject* pGameObject);
		~RectCollisionComponent();
		RectCollisionComponent(const RectCollisionComponent& rectComponent) = delete;
		RectCollisionComponent(RectCollisionComponent&& rectComponent) noexcept = delete;
		RectCollisionComponent& operator=(const RectCollisionComponent& rectComponent) = delete;
		RectCollisionComponent& operator=(RectCollisionComponent&& rectComponent) noexcept = delete;

		virtual void Init() override;

		
		void SetExtend(const glm::vec2& extend);
		void SetLayers(const std::vector<std::string>& layers);
		void SetCollisionType(CollisionType type);
		void AddCollisionOffset(const glm::vec2& offset);

		const std::vector<std::string>& GetLayers() const;
		glm::vec4 GetCollisionBox() const;
		const glm::vec2& GetExtend() const;
		CollisionType GetCollisionType() const;

		void TriggerCollisionEvent(GameObject* pGameObj, CollisionType type);

	private:
		glm::vec4 m_CollisionBox{};
		glm::vec2 m_Extend{};
		std::vector<std::string> m_Layers{};
		CollisionType m_CollisonType{CollisionType::StaticCollision};
	};
}

