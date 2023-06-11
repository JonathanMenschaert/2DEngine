#pragma once
#include "BaseComponent.h"
#include <functional>
#include "glm/glm.hpp"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"

namespace dae
{
	class ButtonComponent : public BaseComponent
	{
	public:
		ButtonComponent(GameObject* pGameObject);
		virtual ~ButtonComponent() = default;
		ButtonComponent(const ButtonComponent& component) = delete;
		ButtonComponent(ButtonComponent&& component) noexcept = delete;
		ButtonComponent& operator=(const ButtonComponent& component) = delete;
		ButtonComponent& operator=(ButtonComponent&& component) noexcept = delete;


		void SetButtonText(const std::string& text);
		void SetButtonFont(const std::shared_ptr<Font> pFont);
		void SetNormalColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void SetHighlightColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void SetSelected(bool selected);
		void SetOnClick(const std::function<void()>& onClick);
		void SetButtonExtend(const glm::vec2& extend);
		void OnClick() const;
		bool IsPointOnButton(const glm::vec2& point) const;
		void Init() override;
		const glm::vec2& GetButtonPos() const;
	
	protected:
		bool m_IsSelected;

	private:
		std::function<void()> m_OnClick;
		TransformComponent* m_pTransform{};
		TextComponent* m_pButtonText{};
		glm::vec2 m_Extend;

		SDL_Color m_NormalColor;
		SDL_Color m_HighlightColor;
	};
}

