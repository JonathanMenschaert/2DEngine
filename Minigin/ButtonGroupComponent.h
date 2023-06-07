#pragma once
#include "BaseComponent.h"
#include "ButtonComponent.h"
#include "glm/glm.hpp"
#include <vector>
namespace dae
{
	class ButtonGroupComponent final : public BaseComponent
	{
	public:
		ButtonGroupComponent(GameObject* pGameObject);
		virtual ~ButtonGroupComponent() = default;
		ButtonGroupComponent(const ButtonGroupComponent& component) = delete;
		ButtonGroupComponent(ButtonGroupComponent&& component) noexcept = delete;
		ButtonGroupComponent& operator=(const ButtonGroupComponent& component) = delete;
		ButtonGroupComponent& operator=(ButtonGroupComponent&& component) noexcept = delete;

		void NavigateToClosestButton(const glm::vec2& direction);
		void NavigateToButtonAtPos(const glm::vec2& pos);

		void Init() override;

	private:
		
		std::vector<ButtonComponent*> m_Buttons;
		size_t m_SelectedButtonIdx;
	};
}

