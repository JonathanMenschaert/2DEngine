#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(std::shared_ptr<GameObject> pGameObject);
		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& component) = delete;
		TransformComponent(TransformComponent&& component) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& component) = delete;
		TransformComponent& operator=(TransformComponent&& component) noexcept = delete;

		void SetLocalPosition(const glm::vec2& position);
		void SetLocalPosition(const glm::vec3& position);
		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

	private:
		void UpdateWorldPosition();

		bool m_NeedsUpdate{ false };
		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
	};
}

