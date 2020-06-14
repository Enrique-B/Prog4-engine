#include "FriedEngine.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BubleBobbleLevelDataReader.h"
#include "InputManager.h"
#include "Command.h"
#include "GameObject.h"
#include "StateManager.h"
#include "BaseState.h"
#include "Observer.h"
#include "Subject.h"
#include "Components.h"

#define keyBoard1ControllerSetup
#define TwoControllerSetup


void Fried::FriedEngine::LoadGame()
{
	Addstates();
	MakeUIScenes();
	BubleBobbleLevelDataReader pData{};
	pData.Read();
	const std::vector<Fried::Scene*> pScenes{ pData.GetScenes() };
	const std::vector<GameObject*> pObjects = pScenes[0]->GetChildren();
	const size_t objectSize{ pObjects.size() };
	std::vector <GameObject*> pCharacters;
	for (size_t i = 0; i < objectSize; i++)
		if (pObjects[i]->HasComponent(ComponentName::Character))
			pCharacters.push_back(pObjects[i]);
	AddInput(pCharacters);
	SceneManager* pSceneManager = SceneManager::GetInstance();
	for (size_t i = 0; i < pScenes.size(); i++)
	{
		pSceneManager->AddScene(pScenes[i]);
	}
}

void Fried::FriedEngine::Addstates()
{
	StateManager* pStateManager = StateManager::GetInstance();
	pStateManager->AddMoveStateX(new MoveStateLeft{});
	pStateManager->AddMoveStateX(new MoveStateRight{});
	pStateManager->AddMoveStateX(new MoveStateXIdle{});
	pStateManager->AddMoveStateX(new MoveStateLeftFast{});
	pStateManager->AddMoveStateX(new MoveStateRightFast{});

	pStateManager->AddMoveStateY(new MoveStateYIdle{});
	pStateManager->AddMoveStateY(new JumpState{});
	pStateManager->AddMoveStateY(new MoveStateYNone{});
	pStateManager->AddLifeState(new DeathState{});
	pStateManager->AddLifeState(new AliveState{});
	pStateManager->AddLifeState(new InvincibleState{});
	pStateManager->AddWeaponState(new WeaponStateNone{});
	pStateManager->AddWeaponState(new WeaponStateShootBubble{});
}

void Fried::FriedEngine::AddInput(const std::vector <GameObject*>& pCharacters)
{
	InputManager* pInput = Fried::InputManager::GetInstance();
#ifdef _DEBUG
	pInput->AddCommand(Input{ new ChangeSceneCommand{}, inputState::pressed, SDL_SCANCODE_F1 });
	pInput->AddCommand(Input{ new DebugRenderCommand{}, inputState::pressed, SDL_SCANCODE_F2 });
#endif // _DEBUG
	pInput->AddCommand(Input{ new MoveLeftCommand{pCharacters[0]}, inputState::down, SDL_SCANCODE_A, 0, ControllerButton::DPadLeft });
	pInput->AddCommand(Input{ new MoveRightCommand{pCharacters[0]}, inputState::down, SDL_SCANCODE_D, 0, ControllerButton::DPadRight });
	pInput->AddCommand(Input{ new JumpCommand{pCharacters[0]}, inputState::pressed, SDL_SCANCODE_W, 0, ControllerButton::ButtonA });
	pInput->AddCommand(Input{ new ShootBubbleCommand{pCharacters[0]}, inputState::pressed, SDL_SCANCODE_S, 0, ControllerButton::ButtonB });
	// releasing will make it idle again like how it should be 
	pInput->AddCommand(Input{ new ReleaseMovementCommand{pCharacters[0]}, inputState::release, SDL_SCANCODE_A, 0, ControllerButton::DPadLeft });
	pInput->AddCommand(Input{ new ReleaseMovementCommand{pCharacters[0]}, inputState::release, SDL_SCANCODE_D, 0, ControllerButton::DPadRight });

	pInput->AddCommand(Input{ new MoveLeftCommand{pCharacters[1]}, inputState::down, SDL_SCANCODE_LEFT, 1, ControllerButton::DPadLeft });
	pInput->AddCommand(Input{ new MoveRightCommand{pCharacters[1]}, inputState::down, SDL_SCANCODE_RIGHT, 1, ControllerButton::DPadRight });
	pInput->AddCommand(Input{ new JumpCommand{pCharacters[1]}, inputState::pressed, SDL_SCANCODE_UP, 1, ControllerButton::ButtonA });
	pInput->AddCommand(Input{ new ShootBubbleCommand{pCharacters[1]}, inputState::pressed, SDL_SCANCODE_DOWN, 1, ControllerButton::ButtonB });
	// releasing will make it idle again like how it should be 
	pInput->AddCommand(Input{ new ReleaseMovementCommand{pCharacters[1]}, inputState::release, SDL_SCANCODE_LEFT, 1, ControllerButton::DPadLeft });
	pInput->AddCommand(Input{ new ReleaseMovementCommand{pCharacters[1]}, inputState::release, SDL_SCANCODE_RIGHT, 1, ControllerButton::DPadRight });
	pInput->AddCommand(Input{ new PauseCommand{}, inputState::pressed, SDL_SCANCODE_RETURN, 0, ControllerButton::StartButton });
	
	pInput->AddCommand(Input{ new SinglePlayerCommand{}, inputState::pressed, SDL_SCANCODE_1 });
	pInput->AddCommand(Input{ new CoopCommand{}, inputState::pressed, SDL_SCANCODE_2 });

	Observer* pObserver = Fried::SceneManager::GetInstance()->GetUIScene(Fried::SceneManager::UI::GameMenu)->GetObservers()[1];
	pCharacters[0]->GetSubject()->AddObserver(pObserver);
	pCharacters[1]->GetSubject()->AddObserver(pObserver);
}

void Fried::FriedEngine::MakeUIScenes()
{
	SceneManager* pSceneManager = SceneManager::GetInstance();

	Fried::Scene* pGameUI{ new Fried::Scene{"UISceneGame"} };
	GameObject* pObject{ new GameObject{} };
	pObject->AddComponent(new TextComponent{ "FPS ", "Lingua.otf", 36 });
	pObject->AddComponent(new FPSComponent{});
	pGameUI->AddGameObject(pObject);
	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "Score: 0", "Lingua.otf", 30 });
	pObject->AddComponent(new ScoreComponent{ unsigned char(-1) });
	pObject->GetTransform()->SetResetPosition(Fried::float2(300, 0));
	pGameUI->AddGameObject(pObject);
	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "Score: 0", "Lingua.otf", 30 });
	pObject->AddComponent(new ScoreComponent{ unsigned char(-1) });
	pObject->GetTransform()->SetResetPosition(Fried::float2(600, 0));
	pGameUI->AddGameObject(pObject);
	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "4", "Lingua.otf", 30 });
	TextureComponent* pTexture = new TextureComponent("heroGreen.png", SDL_Rect{ 780, 0,24*2,24 * 2 }, SDL_Rect{ 0,0,16,16 });
	pObject->AddComponent(pTexture);
	pObject->GetTransform()->SetResetPosition(Fried::float2{ 780, 50 });
	pGameUI->AddGameObject(pObject);
	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "4", "Lingua.otf", 30 });
	pObject->GetTransform()->SetResetPosition(Fried::float2{ 780, 150 });
	pGameUI->AddGameObject(pObject);
	pTexture = new TextureComponent("heroBlue.png", SDL_Rect{ 780, 100,24 * 2,24 * 2 }, SDL_Rect{ 0,0,16,16 });
	pObject->AddComponent(pTexture);
	pGameUI->AddObserver(new PlayerObserver{ pGameUI });
	pSceneManager->AddUIScene(pGameUI, SceneManager::UI::GameMenu);

	pGameUI = new Fried::Scene{"UIScenePause"};
	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "PAUSE ||", "Lingua.otf", 50 });
	pObject->GetTransform()->SetResetPosition(Fried::float2(300, 0));
	pGameUI->AddGameObject(pObject);
	pSceneManager->AddUIScene(pGameUI, SceneManager::UI::PauseMenu);

	pGameUI = new Fried::Scene{ "UISceneStart" };
	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "Single player (1)", "Lingua.otf", 50 });
	pObject->GetTransform()->SetResetPosition(Fried::float2(250, 100));
	pGameUI->AddGameObject(pObject);
	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "co-op (2)", "Lingua.otf", 50 });
	pObject->GetTransform()->SetResetPosition(Fried::float2(250, 200));
	pGameUI->AddGameObject(pObject);

	pObject = new GameObject{};
	pObject->AddComponent(new TextComponent{ "VS (Not implemented) (3)", "Lingua.otf", 50 });
	pObject->GetTransform()->SetResetPosition(Fried::float2(250, 300));
	pGameUI->AddGameObject(pObject);

	pSceneManager->AddUIScene(pGameUI, SceneManager::UI::StartMenu);
}