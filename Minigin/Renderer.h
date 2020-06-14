#pragma once
#include "Singleton.h"
#include <SDL_rect.h>
struct SDL_Window;
struct SDL_Renderer;

struct SDL_Texture;
namespace Fried
{
	class Renderer final : public Singleton<Renderer>
	{
	public:
		Renderer(const Renderer& other) = delete;
		Renderer(Renderer&& other) = delete;
		Renderer& operator=(const Renderer& other) = delete;
		Renderer& operator=(Renderer&& other) = delete;
		~Renderer() = default;

		void Init(SDL_Window* window) noexcept(false);
		void Render() const noexcept;
		void Destroy()noexcept;
		void RenderTexture(SDL_Texture* texture, const SDL_Rect& dest) const noexcept;
		void RenderTexture(SDL_Texture* texture, float x, float y, int width, int height) const noexcept;
		void RenderTexture(SDL_Texture* texture, const SDL_Rect& resource, const SDL_Rect& dest)const noexcept;
		void RenderTexture(SDL_Texture* texture, const SDL_Rect& resource, const SDL_Rect& dest, double angle, const SDL_Point& center, bool flip)noexcept;
		void RenderRect(const SDL_Rect& rect)const noexcept;
		void RenderLine(const Fried::line& line)const noexcept;
		SDL_Renderer* GetSDLRenderer() const noexcept { return m_Renderer; }
	private:
		friend class Singleton<Renderer>;
		Renderer() = default;
		SDL_Renderer* m_Renderer{};
	};
}
