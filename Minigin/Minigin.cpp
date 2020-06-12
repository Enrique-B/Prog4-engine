#include "MiniginPCH.h"
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "StateManager.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"

#include <chrono>
#include <thread>
#include <SDL.h>
#include <future>

using namespace std;
using namespace std::chrono;

void Fried::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	const int windowWidth{ 32 * 24 + 100};
	const int windowHeight{ 25 * 24 + 40};

	m_Window = SDL_CreateWindow(
		"Enrique Brosse Bubble Bobble Scuffed Version",
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
	StateManager::GetInstance();
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
	delete StateManager::GetInstance();
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
		std::future<void> collisionThread;
		while (doContinue)
		{
			std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

			doContinue = input->ProcessInput();
			input->HandleInput();
			collisionThread = std::async(std::launch::async, &SceneManager::CollisionUpdate, sceneManager, elapsedSec);
			
			//sceneManager->CollisionUpdate();
			sceneManager->Update(elapsedSec);
			// render
			renderer->Render();
			// Get current time
			std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
			// Calculate elapsed time
			elapsedSec = std::chrono::duration<float>(t2 - t1).count();
			// Update current time
			t1 = t2;
			collisionThread.get(); // should stop the loop here and remove the non active objects 
			sceneManager->DeactivateNonActiveGameObjects();
		}
	}
	Cleanup();
}
