#pragma once
#include "glm/glm.hpp"
#include "BaseComponent.h"
#include <string>
#include <vector>
#include "Subject.h"
#include "RenderComponent.h"
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

	class RectCollisionComponent final : public RenderComponent, public Subject<CollisionData>
	{
	public:
		RectCollisionComponent(GameObject* pGameObject);
		~RectCollisionComponent();
		RectCollisionComponent(const RectCollisionComponent& rectComponent) = delete;
		RectCollisionComponent(RectCollisionComponent&& rectComponent) noexcept = delete;
		RectCollisionComponent& operator=(const RectCollisionComponent& rectComponent) = delete;
		RectCollisionComponent& operator=(RectCollisionComponent&& rectComponent) noexcept = delete;

		virtual void Init() override;

		
		void SetCollisionBox(const glm::vec2& size, const glm::vec2& offset = {});
		void SetLayers(const std::vector<std::string>& layers);
		void SetCollisionType(CollisionType type);
		void AddCollisionOffset(const glm::vec2& offset);

		const std::vector<std::string>& GetLayers() const;
		glm::vec4 GetCollisionBox() const;
		const glm::vec2& GetExtend() const;
		CollisionType GetCollisionType() const;

		void TriggerCollisionEvent(GameObject* pGameObj, CollisionType type);
		virtual void Render() const override;

	private:
		glm::vec2 m_Offset{};
		glm::vec4 m_CollisionBox{};
		glm::vec2 m_Size{};
		std::vector<std::string> m_Layers{};
		CollisionType m_CollisonType{CollisionType::StaticCollision};
	};
}

