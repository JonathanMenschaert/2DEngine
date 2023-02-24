#include <stdexcept>
#include "TextComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate) CreateTexture();
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

const std::string& dae::TextComponent::GetText()
{
	return m_Text;
}

void dae::TextComponent::SetFont(const std::shared_ptr<Font> font)
{
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_TextColor = SDL_Color{ r, g, b, a };
	m_NeedsUpdate = true;
}

void dae::TextComponent::CreateTexture()
{
	const auto surface = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_TextColor);
	if (!surface)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);

	if (!texture)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		
	}
	SDL_FreeSurface(surface);

	//renderer here
	m_NeedsUpdate = false;
}
