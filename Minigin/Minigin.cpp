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

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance()->Init(m_Window);
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

	// tell the resource manager where he can find the game data
	Fried::ResourceManager::GetInstance()->Init("../Data/");

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
			sceneManager->Update(elapsedSec);
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
