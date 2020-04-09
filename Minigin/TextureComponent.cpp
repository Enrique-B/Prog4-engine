#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>
#include "Renderer.h"
#include "Structs.h"
#include "ResourceManager.h"

TextureComponent::TextureComponent(const std::string& textureName)
	: BaseComponent()
	,m_pTexture{ Fried::ResourceManager::GetInstance()->LoadTexture(textureName) }
{
	SetComponentName(ComponentName::Texture);
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_WidthHeight.x, &m_WidthHeight.y);
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void TextureComponent::Render(const Fried::float2& pos) const
{
	if (m_pTexture)
	{
		Fried::Renderer::GetInstance()->RenderTexture(m_pTexture, pos.x, pos.y, m_WidthHeight.x, m_WidthHeight.y);
	}
}