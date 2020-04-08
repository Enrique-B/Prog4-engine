#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>
#include "Renderer.h"
#include "Structs.h"

TextureComponent::TextureComponent(SDL_Texture* texture)
	:BaseComponent()
{
	m_Texture = texture;
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
	if (m_Texture)
	{
		Fried::Renderer::GetInstance()->RenderTexture(m_Texture, pos.x, pos.y);
	}
}

SDL_Texture* TextureComponent::GetSDLTexture() const
{
	return m_Texture;
}