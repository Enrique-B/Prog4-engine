#pragma once
#include "Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

struct SDL_Texture;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
class Renderer final : public Singleton<Renderer>
{
public:
	void Init(SDL_Window* window);
	void Render() const;
	void Destroy();

	void RenderTexture(SDL_Texture* texture, float x, float y) const;
	void RenderTexture(SDL_Texture* texture, float x, float y, float width, float height) const;

	SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
private:
	SDL_Renderer* m_Renderer{};
};

