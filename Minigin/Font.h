#pragma once

struct _TTF_Font;
class Font
{
public:
	explicit Font(const std::string& fullPath, unsigned int size)noexcept(false);
	~Font();
	Font(const Font&) = delete;
	Font(Font&&) = delete;
	Font& operator= (const Font&) = delete;
	Font& operator= (const Font&&) = delete;

	_TTF_Font* GetFont() const noexcept { return m_Font; };
private:
	_TTF_Font* m_Font;
	size_t m_Size;
};