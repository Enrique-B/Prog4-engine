#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "StateComponent.h"
#include <iostream>
#include "SceneManager.h"
#include "StateManager.h"
#include "../Game/BaseState.h"
#include "SpriteComponent.h"

JumpCommand::JumpCommand(GameObject* pObject)
	:Command(pObject){}

void JumpCommand::Execute()
{
	Fried::StateManager* pStateManager = Fried::StateManager::GetInstance();
	MoveStateY* pJump = pStateManager->GetMoveStateY("JumpState");
	WeaponState* pShootBubble = pStateManager->GetWeaponState("WeaponStateShootBubble");
	StateComponent* pStat = m_pObject->GetComponent<StateComponent>(ComponentName::state);
	pStat->SetMoveStateY(pJump);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	if (pShootBubble != pStat->GetWeaponState())
	{
		pSprite->SetFrame(1);
	}
	pSprite->SetMaxedFrames(2);
}

MoveLeftCommand::MoveLeftCommand(GameObject* pObject)
	: Command(pObject) {}

void MoveLeftCommand::Execute()
{
	MoveStateX* pTemp = Fried::StateManager::GetInstance()->GetMoveStateX("MoveLeftState");
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::state);
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
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::state);
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
	m_pObject->GetComponent<StateComponent>(ComponentName::state)->SetMoveStateX(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::state);
	if (pState->GetWeaponState() != pShootingState && pState->GetLifeState() != pStateManager->GetLifeState("DeathState"))
	{
		pSprite->SetFrame(1);
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
	StateComponent* pState = m_pObject->GetComponent<StateComponent>(ComponentName::state);
	if (pState->GetWeaponState() != pShootingState && pState->GetLifeState() != pStateManager->GetLifeState("DeathState"))
	{
		pState->SetWeaponState(pShootingState);
		SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
		pSprite->SetUpdate(true);
		pSprite->SetFrame(0);
		pSprite->SetDestRectY(32);
		pSprite->SetMaxedFrames(2);
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