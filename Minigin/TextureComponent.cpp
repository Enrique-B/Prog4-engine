#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>
#include "Renderer.h"
#include "Structs.h"
#include "ResourceManager.h"

TextureComponent::TextureComponent(const std::string& textureName)
	: BaseComponent()
	,m_pTexture{ Fried::ResourceManager::GetInstance()->LoadTexture(textureName) }
	, m_RcsRect{}
{
	m_UseResource = false;
	SetComponentName(ComponentName::Texture);
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_WidthHeight.x, &m_WidthHeight.y);
}

TextureComponent::TextureComponent(const std::string& textureName, SDL_Rect dstRect, SDL_Rect resourceRect)
	:TextureComponent(textureName)
{
	m_UseResource = true;
	m_DstRect = dstRect;
	m_RcsRect = resourceRect;
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::Render(const Fried::float2& pos) const
{
	if (m_pTexture == nullptr)
		return;
	SDL_Rect dstRect;
	dstRect.x = static_cast<int>(pos.x);
	dstRect.y = static_cast<int>(pos.y);
	dstRect.w = m_WidthHeight.x;
	dstRect.h = m_WidthHeight.y;
	if (m_UseResource)
		Fried::Renderer::GetInstance()->RenderTexture(m_pTexture, m_RcsRect, m_DstRect);
	else
		Fried::Renderer::GetInstance()->RenderTexture(m_pTexture, dstRect);

}