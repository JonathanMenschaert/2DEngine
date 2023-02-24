#pragma once
#include "BaseComponent.h"
#include <string>
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"

namespace dae
{
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent();
		~TextComponent() = default;
		TextComponent(const TextComponent& component) = delete;
		TextComponent(TextComponent&& component) noexcept = delete;
		TextComponent& operator=(const TextComponent& component) = delete;
		TextComponent& operator=(TextComponent&& component) noexcept = delete;

		void Update() override;

		void SetText(const std::string& text);
		const std::string& GetText();

		void SetFont(const std::shared_ptr<Font> font);
		void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
		void CreateTexture();

	private:

		SDL_Color m_TextColor;
		bool m_NeedsUpdate{ true };
		std::string m_Text;
		std::shared_ptr<Font> m_Font{};
	};
}

