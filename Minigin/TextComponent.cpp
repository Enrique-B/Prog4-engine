#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Structs.h"
#include "ResourceManager.h"

TextComponent::TextComponent(const std::string& text, const std::string& fileName, size_t size)
	: BaseComponent()
	, m_NeedsUpdate(true)
	, m_Text(text)
	, m_Font(Fried::ResourceManager::GetInstance()->LoadFont(fileName,size))
	, m_pTexture(nullptr)
	, m_TextureWidth{}
	, m_TextureHeight{}
{
	SetComponentName(ComponentName::Text);
}

TextComponent::~TextComponent()
{
	SDL_DestroyTexture(m_pTexture);
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
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = texture;
		SDL_QueryTexture(texture, nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);
		m_NeedsUpdate = false;
	}
}

void TextComponent::Render(const Fried::float2& pos) const
{
	if (m_pTexture != nullptr)
	{
		Fried::Renderer::GetInstance()->RenderTexture(m_pTexture, pos.x, pos.y,m_TextureWidth,m_TextureHeight);
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
