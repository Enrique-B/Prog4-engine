#pragma once
#include "BaseComponent.h"

class Font;
struct SDL_Texture;
class TextComponent final : public BaseComponent
{
public:
	virtual void Update(float elapsedSec);
	virtual void Render(const float2& pos) const;

	void SetText(const std::string& text);

	explicit TextComponent(const std::string& text, Font* font);
	virtual  ~TextComponent();
	TextComponent(const TextComponent& other) = delete;
	TextComponent(TextComponent&& other) = delete;
	TextComponent& operator=(const TextComponent& other) = delete;
	TextComponent& operator=(TextComponent&& other) = delete;
private:
	bool m_NeedsUpdate;
	std::string m_Text;
	Font* m_Font;
	SDL_Texture* m_Texture;
};
