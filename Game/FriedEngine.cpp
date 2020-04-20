#include "FriedEngine.h"
#include "SceneManager.h"
#include "DemoScene.h"
#include "BubleBobbleLevelDataReader.h"
#include "InputManager.h"
#include "Command.h"

void Fried::FriedEngine::LoadGame()
{
	Fried::InputManager::GetInstance()->AddCommand(Input{ new ChangeSceneCommand{}, inputState::release, SDL_SCANCODE_F1, 0, ControllerButton::StartButton });
	BubleBobbleLevelDataReader pData{ "../Data/SeperatedLevelData.dat" };
	pData.Read();
	std::vector<Fried::Scene*> pScenes{ pData.GetScenes()};
	for (size_t i = 0; i < pScenes.size(); i++)
	{
		SceneManager::GetInstance()->AddScene(pScenes[i]);
	}
	//SceneManager::GetInstance()->AddScene(new DemoScene{});
}
