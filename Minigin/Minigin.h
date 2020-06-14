#pragma once
struct SDL_Window;
namespace Fried
{
	class Minigin
	{
	public:
		Minigin() = default;
		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;
		~Minigin() = default;

		void Initialize();
		void Cleanup();
		void Run();
	protected:
		virtual void LoadGame() = 0;
	private:
		SDL_Window* m_Window{};
	};
}