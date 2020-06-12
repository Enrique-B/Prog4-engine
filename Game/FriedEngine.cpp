#include "FriedEngine.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BubleBobbleLevelDataReader.h"
#include "InputManager.h"
#include "Command.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "StateManager.h"
#include "BaseState.h"

#define keyBoard1ControllerSetup
#define TwoControllerSetup


void Fried::FriedEngine::LoadGame()
{
	StateManager* pStateManager = StateManager::GetInstance();
	pStateManager->AddMoveStateX(new MoveStateLeft{});
	pStateManager->AddMoveStateX(new MoveStateRight{});
	pStateManager->AddMoveStateX(new MoveStateXIdle{});
	pStateManager->AddMoveStateY(new MoveStateYIdle{});
	pStateManager->AddMoveStateY(new JumpState{});
	pStateManager->AddMoveStateY(new MoveStateYNone{});
	pStateManager->AddLifeState(new DeathState{});
	pStateManager->AddLifeState(new AliveState{});
	pStateManager->AddLifeState(new InvincibleState{});
	pStateManager->AddWeaponState(new WeaponStateNone{});
	pStateManager->AddWeaponState(new WeaponStateShootBubble{});


	BubleBobbleLevelDataReader pData{};
	pData.Read();
	const std::vector<Fried::Scene*> pScenes{ pData.GetScenes()};
	const std::vector<GameObject*> pObjects =  pScenes[0]->GetChildren();

	const size_t objectSize{ pObjects.size() };
	std::vector <GameObject*> pCharacters;
	for (size_t i = 0; i < objectSize; i++)
		if (pObjects[i]->HasComponent(ComponentName::Character))
			pCharacters.push_back(pObjects[i]);

	InputManager* pInput = Fried::InputManager::GetInstance();
	pInput->AddCommand(Input{ new ChangeSceneCommand{}, inputState::pressed, SDL_SCANCODE_F1, 0, ControllerButton::StartButton });
	pInput->AddCommand(Input{ new DebugRenderCommand{}, inputState::pressed, SDL_SCANCODE_F2 });

	pInput->AddCommand(Input{ new MoveLeftCommand{pCharacters[0]}, inputState::down, SDL_SCANCODE_LEFT, 0, ControllerButton::DPadLeft });
	pInput->AddCommand(Input{ new MoveRightCommand{pCharacters[0]}, inputState::down, SDL_SCANCODE_RIGHT, 0, ControllerButton::DPadRight });
	pInput->AddCommand(Input{ new JumpCommand{pCharacters[0]}, inputState::pressed, SDL_SCANCODE_UP, 0, ControllerButton::ButtonA });
	pInput->AddCommand(Input{ new ShootBubbleCommand{pCharacters[0]}, inputState::pressed, SDL_SCANCODE_DOWN, 0, ControllerButton::ButtonB });

	// releasing will make it idle again like how it should be 
	pInput->AddCommand(Input{ new ReleaseMovementCommand{pCharacters[0]}, inputState::release, SDL_SCANCODE_LEFT, 0, ControllerButton::DPadLeft });
	pInput->AddCommand(Input{ new ReleaseMovementCommand{pCharacters[0]}, inputState::release, SDL_SCANCODE_RIGHT, 0, ControllerButton::DPadRight });

	SceneManager* pSceneManager = SceneManager::GetInstance();
	for (size_t i = 0; i < pScenes.size(); i++)
	{
		pSceneManager->AddScene(pScenes[i]);
	}
}