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

		void Init() override;

		void SetLocalPosition(const glm::vec2& position);
		void Translate(const glm::vec2& offset);
		const glm::vec2& GetLocalPosition() const;
		const glm::vec2& GetWorldPosition();
		float GetDistanceToParent() const;

	private:
		void SetFlagDirty();
		void UpdateWorldPosition();
		float m_Magnitude{};
		bool m_NeedsUpdate{ false };
		glm::vec2 m_WorldPosition{};
		glm::vec2 m_LocalPosition{};
	};
}

