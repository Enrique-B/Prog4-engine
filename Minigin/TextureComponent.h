#pragma once
#include "BaseComponent.h"

struct SDL_Texture;
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
namespace Fried
{
	struct float2;
}


class TextureComponent : public BaseComponent
{
public:
	SDL_Texture* GetSDLTexture() const;
	explicit TextureComponent(SDL_Texture* texture);
	~TextureComponent();
	virtual void Update(float elapsedSec);
	virtual void Render(const Fried::float2& pos)const;

	TextureComponent(const TextureComponent&) = delete;
	TextureComponent(TextureComponent&&) = delete;
	TextureComponent& operator= (const TextureComponent&) = delete;
	TextureComponent& operator= (const TextureComponent&&) = delete;
private:
	SDL_Texture* m_Texture;
};