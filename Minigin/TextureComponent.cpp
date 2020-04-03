#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>
#include "Renderer.h"

TextureComponent::~TextureComponent()
{
}

void TextureComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void TextureComponent::Render(const float2& pos) const
{
	if (m_Texture)
	{
		Renderer::GetInstance()->RenderTexture(m_Texture, pos.x, pos.y);
	}
}

SDL_Texture* TextureComponent::GetSDLTexture() const
{
	return m_Texture;
}

TextureComponent::TextureComponent(SDL_Texture* texture)
	:BaseComponent()
{
	m_Texture = texture;
}
