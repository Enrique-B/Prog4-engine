#pragma once
#include "Singleton.h"
#include <SDL_rect.h>
struct SDL_Window;
struct SDL_Renderer;

struct SDL_Texture;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
namespace Fried
{
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(SDL_Texture* texture, float x, float y, int width, int height) const;
		void RenderTexture(SDL_Texture* texture, SDL_Rect resource, SDL_Rect dest)const;
		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}
