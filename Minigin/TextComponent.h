#pragma once
#include "BaseComponent.h"
struct SDL_Texture;
class Font;
class TextComponent final : public BaseComponent
{
public:
	virtual void Update(float elapsedSec);
	virtual void Render(const Fried::float2& pos) const;

	void SetText(const std::string& text);

	explicit TextComponent(const std::string& text, const std::string& fileName, unsigned int size);
	virtual  ~TextComponent();
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;
private:
	bool m_NeedsUpdate;
	std::string m_Text;
	Font* m_Font;
	SDL_Texture* m_pTexture;
	int m_TextureWidth;
	int m_TextureHeight;
};