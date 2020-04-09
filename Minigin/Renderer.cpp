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

void Fried::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	Fried::SceneManager::GetInstance()->Render();
	
	SDL_RenderPresent(m_Renderer);
}

void Fried::Renderer::Destroy()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void Fried::Renderer::RenderTexture(SDL_Texture* texture, const float x, const float y, const int width, const int height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = (width);
	dst.h = (height);
	SDL_RenderCopy(m_Renderer, texture, nullptr, &dst);
}

void Fried::Renderer::RenderTexture(SDL_Texture* texture, SDL_Rect resource, SDL_Rect dest) const
{
	SDL_RenderCopy(m_Renderer, texture, &resource, &dest);
}
