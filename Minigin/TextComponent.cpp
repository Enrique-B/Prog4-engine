#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Structs.h"

TextComponent::TextComponent(const std::string& text, Font* font)
	: BaseComponent(), m_NeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr)
{ }

TextComponent::~TextComponent()
{
	SDL_DestroyTexture(m_Texture);
}

void TextComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		SDL_Surface* surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Fried::Renderer::GetInstance()->GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(m_Texture);
		m_Texture = texture;
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render(const Fried::float2& pos) const
{
	if (m_Texture != nullptr)
	{
		Fried::Renderer::GetInstance()->RenderTexture(m_Texture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void TextComponent::SetText(const std::string& text)
{
	if (m_Text != text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
}
