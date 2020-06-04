#include "FriedEngine.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "BubleBobbleLevelDataReader.h"
#include "InputManager.h"
#include "Command.h"
#include "GameObject.h"
#include "ColliderComponent.h"

void Fried::FriedEngine::LoadGame()
{
	Fried::InputManager::GetInstance()->AddCommand(Input{ new ChangeSceneCommand{}, inputState::release, SDL_SCANCODE_F1, 0, ControllerButton::StartButton });
	Fried::InputManager::GetInstance()->AddCommand(Input{ new DebugRenderCommand{}, inputState::release, SDL_SCANCODE_F2 });

	BubleBobbleLevelDataReader pData{};
	pData.Read();
	std::vector<Fried::Scene*> pScenes{ pData.GetScenes()};
	for (size_t i = 0; i < pScenes.size(); i++)
	{
		SceneManager::GetInstance()->AddScene(pScenes[i]);
	}
	//SceneManager::GetInstance()->AddScene(new DemoScene{});
}
