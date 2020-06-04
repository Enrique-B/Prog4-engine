#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "TextureComponent.h"

void Fried::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Fried::Renderer::Render() const noexcept
{
	const Uint8 r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 };
	SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
	SDL_RenderClear(m_Renderer);
	Fried::SceneManager::GetInstance()->Render();
	SDL_RenderPresent(m_Renderer);
}

void Fried::Renderer::Destroy()noexcept
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Fried::Renderer::RenderTexture(SDL_Texture* texture, const SDL_Rect& dest) const noexcept
{
	SDL_RenderCopy(m_Renderer, texture, nullptr, &dest);
}

void Fried::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y, const int width, const int height) const noexcept
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = width;
	dst.h = height;
	SDL_RenderCopy(m_Renderer, texture, nullptr, &dst);
}

void Fried::Renderer::RenderTexture(SDL_Texture* texture, const SDL_Rect& resource, const SDL_Rect& dest) const noexcept
{
	SDL_RenderCopy(m_Renderer, texture, &resource, &dest);
}

void Fried::Renderer::RenderTexture(SDL_Texture* texture, const SDL_Rect& resource, const SDL_Rect& dest, double angle, const SDL_Point& center, bool flip) noexcept
{
	SDL_RenderCopyEx(m_Renderer, texture, &resource, &dest, angle, &center, flip ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE);
}

void Fried::Renderer::RenderRect(const SDL_Rect& rect)const noexcept
{
	const Uint8 r{ 255 }, g{ 105 }, b{ 180 }, a{ 255 };
	SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
	SDL_RenderDrawRect(m_Renderer, &rect);
}

void Fried::Renderer::RenderLine(const Fried::line& line) const noexcept
{
	SDL_RenderDrawLine(m_Renderer, static_cast<int>(line.p1.x), static_cast<int>(line.p1.y),
		static_cast<int>(line.p2.x), static_cast<int>(line.p2.y));
}
