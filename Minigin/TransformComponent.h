#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		~TransformComponent() = default;
		TransformComponent(const TransformComponent& component) = delete;
		TransformComponent(TransformComponent&& component) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& component) = delete;
		TransformComponent& operator=(TransformComponent&& component) noexcept = delete;

		void SetTranslation(const glm::vec2& translation);
		glm::vec2& GetTranslation();

	private:

		glm::vec2 m_Translation{};
	};
}

