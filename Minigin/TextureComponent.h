#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <SDL_rect.h>

struct SDL_Texture;
class TextureComponent : public BaseComponent
{
public:
	explicit TextureComponent(const std::string& textureName);
	TextureComponent(const std::string& textureName, SDL_Rect dstRect,SDL_Rect resourceRect);
	~TextureComponent();
	virtual void Render(const Fried::float2& pos)const;
	TextureComponent(const TextureComponent&) = delete;
	TextureComponent(TextureComponent&&) = delete;
	TextureComponent& operator= (const TextureComponent&) = delete;
	TextureComponent& operator= (const TextureComponent&&) = delete;
private:
	SDL_Texture* m_pTexture;
	Fried::int2 m_WidthHeight;
	SDL_Rect m_RcsRect;
	SDL_Rect m_DstRect;
	bool m_UseResource; 
};