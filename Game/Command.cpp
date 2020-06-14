#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "StateComponent.h"
#include "SceneManager.h"
#include "StateManager.h"
#include "../Game/BaseState.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "BubbleComponent.h"
#include "BubbleManager.h"
#include "Scene.h"
#include <iostream>

JumpCommand::JumpCommand(GameObject* pObject)
	:Command(pObject){}

void JumpCommand::Execute()
{
	Fried::StateManager* pStateManager = Fried::StateManager::GetInstance();
	MoveStateY* pJump = pStateManager->GetMoveStateY("JumpState");
	WeaponState* pShootBubble = pStateManager->GetWeaponState("WeaponStateShootBubble");
	StateComponent* pStat = m_pObject->GetComponent<StateComponent>(ComponentName::State);
	ColliderComponent * pCollider = m_pObject->GetComponent<ColliderComponent>(ComponentName::Collider);
	if (pCollider->HasTrigger(ColliderTrigger::Bottom))
	{
		pStat->SetMoveStateY(pJump);
		SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
		if (pShootBubble != pStat->GetWeaponState())
		{
			pSprite->SetFrame(1);
		}
		pSprite->SetMaxedFrames(2);
	}
}

MoveLeftCommand::MoveLeftCommand(GameObject* pObject)
	: Command(pObject) {}

void MoveLeftCommand::Execute()
{
	MoveStateX* pTemp = Fried::StateManager::GetInstance()->GetMoveStateX("MoveLeftState");
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::State);
	pState->SetMoveStateX(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite); 
	if (pState->GetLifeState() != Fried::StateManager::GetInstance()->GetLifeState("DeathState"))
	{
		pSprite->SetIsGoingLeft(true);
		pSprite->SetMaxedFrames(2);
	}
	pSprite->SetUpdate(true);
}

MoveRightCommand::MoveRightCommand(GameObject* pObject)
	: Command(pObject){}

void MoveRightCommand::Execute()
{
	MoveStateX* pTemp = Fried::StateManager::GetInstance()->GetMoveStateX("MoveRightState");
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::State);
	pState->SetMoveStateX(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	if (pState->GetLifeState() != Fried::StateManager::GetInstance()->GetLifeState("DeathState"))
	{
		pSprite->SetIsGoingLeft(false);
		pSprite->SetMaxedFrames(2);
	}
	pSprite->SetUpdate(true);
}

ReleaseMovementCommand::ReleaseMovementCommand(GameObject* pObject)
	: Command(pObject){}

void ReleaseMovementCommand::Execute()
{
	Fried::StateManager* pStateManager{ Fried::StateManager::GetInstance() };
	MoveStateX* pTemp = pStateManager->GetMoveStateX("MoveStateXIdle");
	WeaponState* pShootingState = pStateManager->GetWeaponState("WeaponStateShootBubble");
	m_pObject->GetComponent<StateComponent>(ComponentName::State)->SetMoveStateX(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::State);
	if (pState->GetWeaponState() != pShootingState && pState->GetLifeState() != pStateManager->GetLifeState("DeathState"))
	{
		pSprite->SetFrame(0);
		pSprite->SetMaxedFrames(2);
		pSprite->SetUpdate(false);
	}
}

ShootBubbleCommand::ShootBubbleCommand(GameObject* pObject)
	:Command{ pObject } {}

void ShootBubbleCommand::Execute()
{
	Fried::StateManager* pStateManager = Fried::StateManager::GetInstance();
	WeaponState* pShootingState = pStateManager->GetWeaponState("WeaponStateShootBubble");
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::State);
	if (pState->GetWeaponState() != pShootingState && pState->GetLifeState() != pStateManager->GetLifeState("DeathState"))
	{
		pState->SetWeaponState(pShootingState);
		SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
		pSprite->SetUpdate(true);
		pSprite->SetFrame(0);
		pSprite->SetDestRectY(32);
		pSprite->SetMaxedFrames(2);

		GameObject* pBubble = Fried::BubbleManager::GetInstance()->GetBubble();
		if (pBubble != nullptr)
		{
			ColliderComponent* pThisCollider = m_pObject->GetComponent<ColliderComponent>(ComponentName::Collider);
			bool isGoingRight = !pSprite->GetIsGoingLeft();
			pBubble->GetComponent<BubbleComponent>(ComponentName::Bubble)->SetGoingRight(isGoingRight);
			pBubble->GetComponent<SpriteComponent>(ComponentName::Sprite)->SetDestRectY(0);
			const float offset{ 3 };
			const int collisionWidth{ 24 * 2 };
			Fried::float2 pos{ m_pObject->GetTransform()->GetPosition() };
			pos.x += isGoingRight ? pThisCollider->GetCollisionRect().w + offset : -offset - collisionWidth;
			pBubble->GetTransform()->SetResetPosition(pos);
			m_pObject->GetScene()->AddGameObject(pBubble);
		}
	}
}

ChangeSceneCommand::ChangeSceneCommand()
	:Command(nullptr){}

void ChangeSceneCommand::Execute()
{
	Fried::SceneManager::GetInstance()->NextScene();
}

Command::Command(GameObject* pObject)
	:m_pObject{pObject}{}

void DebugRenderCommand::Execute()
{
	Fried::SceneManager* pManager = Fried::SceneManager::GetInstance();
	pManager->SetIsRenderingCollision(!pManager->GetIsRenderingCollision());
}

void PauseCommand::Execute()
{
	Fried::SceneManager* pManager = Fried::SceneManager::GetInstance();
	Fried::SceneManager::UI UI = pManager->GetUI();
	switch (UI)
	{
	case Fried::SceneManager::UI::GameMenu:
		pManager->SetUIScene(Fried::SceneManager::UI::PauseMenu);
		break;
	case Fried::SceneManager::UI::PauseMenu:
		pManager->SetUIScene(Fried::SceneManager::UI::GameMenu);
		break;
	default:
		break;
	}
}

void SinglePlayerCommand::Execute()
{
	Fried::SceneManager* pManager = Fried::SceneManager::GetInstance();
	Fried::SceneManager::UI UI = pManager->GetUI();
	if (UI == Fried::SceneManager::UI::StartMenu)
	{
		pManager->SetUIScene(Fried::SceneManager::UI::GameMenu);
		Fried::Scene* currentscene = pManager->GetCurrentScene();
		std::vector<GameObject*> pCharacters; 
		std::vector<GameObject*> pGameObjects = currentscene->GetChildren();
		size_t size{ pGameObjects.size() };
		for (size_t i = 1; i < size; i++)
		{
			if (pGameObjects[i]->HasComponent(ComponentName::Character))
			{
				pCharacters.push_back(pGameObjects[i]);
			}
		}
		pCharacters[1]->GetComponent<StateComponent>(ComponentName::State)->
			SetLifeState(Fried::StateManager::GetInstance()->GetLifeState("DeathState"));
		pCharacters[1]->SetIsActive(false);
		Fried::Scene* UIscene = pManager->GetUIScene(Fried::SceneManager::UI::GameMenu);
		const std::vector<GameObject*> UIChildren = UIscene->GetChildren();
		size = UIChildren.size();
		size_t amount = 0;
		size_t amount2 = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (UIChildren[i]->HasComponent(ComponentName::Text) && UIChildren[i]->HasComponent(ComponentName::Texture))
			{
				amount++; 
				if (amount == 2)
				{
					UIscene->RemoveGameObject(UIChildren[i]);
					UIscene->AddGameObjectToNonActive(UIChildren[i]);
				}
			}
			else if (UIChildren[i]->HasComponent(ComponentName::Text))
			{
				amount2++; 
				if (amount2 == 3)
				{
					UIscene->RemoveGameObject(UIChildren[i]);
					UIscene->AddGameObjectToNonActive(UIChildren[i]);
				}
			}
		}
	}
}

void CoopCommand::Execute()
{
	Fried::SceneManager* pManager = Fried::SceneManager::GetInstance();
	Fried::SceneManager::UI UI = pManager->GetUI();
	if (UI == Fried::SceneManager::UI::StartMenu)
	{
		pManager->SetUIScene(Fried::SceneManager::UI::GameMenu);
	}
}
