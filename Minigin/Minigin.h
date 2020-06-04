#pragma once
struct SDL_Window;
namespace Fried
{
	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
	protected:
		virtual void LoadGame() = 0;
	private:
		SDL_Window* m_Window{};
		static const int MsPerFrame = 60; //16 for 60 fps, 33 for 30 fps
	};
}