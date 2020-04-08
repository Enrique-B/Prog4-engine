#include "FriedEngine.h"
#include "SceneManager.h"


#include "DemoScene.h"
void Fried::FriedEngine::LoadGame()
{
	SceneManager::GetInstance()->AddScene(new DemoScene{});
}
