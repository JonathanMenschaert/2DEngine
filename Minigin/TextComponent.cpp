#include <stdexcept>
#include "TextComponent.h"
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "RenderComponent.h"

dae::TextComponent::TextComponent()
	:m_TextColor{SDL_Color{}}
	,m_NeedsUpdate{true}
{
}

void dae::TextComponent::Update()
{
	if (m_NeedsUpdate && m_Text.size() > 0) CreateTexture();
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

void dae::TextComponent::SetFont(const std::shared_ptr<Font> pFont)
{
	m_pFont = pFont;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	m_TextColor = SDL_Color{ r, g, b, a };
	m_NeedsUpdate = true;
}

void dae::TextComponent::CreateTexture()
{
	const auto pSurface = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_TextColor);
	if (!pSurface)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}

	auto pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), pSurface);

	if (!pTexture)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		
	}
	SDL_FreeSurface(pSurface);

	m_GameObject.lock()->GetComponent<RenderComponent>().lock()->SetTexture(std::make_shared<Texture2D>(pTexture));
	m_NeedsUpdate = false;
}
