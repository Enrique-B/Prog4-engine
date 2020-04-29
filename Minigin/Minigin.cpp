#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"


using namespace std;
using namespace std::chrono;

void Fried::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	const int windowWidth{ 32 * 24 };
	const int windowHeight{ 25 * 24 };

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		throw std::runtime_error(std::string("SDL_INIT_AUDIO Error: ") + SDL_GetError());
	}
	Renderer::GetInstance()->Init(m_Window);
	// tell the resource manager where he can find the game data
	Fried::ResourceManager::GetInstance()->Init("../Data/");

}

void Fried::Minigin::Cleanup()
{
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	Renderer::GetInstance()->Destroy();
	delete InputManager::GetInstance();
	delete Renderer::GetInstance();
	delete ResourceManager::GetInstance(); 
	delete SceneManager::GetInstance(); 
}

void Fried::Minigin::Run()
{
	Initialize();
	LoadGame();

	{
		auto* renderer = Renderer::GetInstance();
		auto* sceneManager = SceneManager::GetInstance();
		auto* input = InputManager::GetInstance();
		float elapsedSec{};

		bool doContinue = true;
		while (doContinue)
		{
			std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

			doContinue = input->ProcessInput();
			input->HandleInput();
			sceneManager->Update(elapsedSec);
			sceneManager->CollisionUpdate();
			renderer->Render();
			
			// Get current time
			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
			// Calculate elapsed time
			elapsedSec = std::chrono::duration<float>(t2 - t1).count();
			// Update current time
			t1 = t2;
		}
	}

	Cleanup();
}
