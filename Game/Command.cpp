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
	MoveStateY* pTemp = Fried::StateManager::GetInstance()->GetMoveStateY("JumpState");
	m_pObject->GetComponent<StateComponent>(ComponentName::state)->SetMoveStateY(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	pSprite->SetFrame(1);
	pSprite->SetMaxedFrames(2);
}

MoveLeftCommand::MoveLeftCommand(GameObject* pObject)
	: Command(pObject) {}

void MoveLeftCommand::Execute()
{
	MoveStateX* pTemp = Fried::StateManager::GetInstance()->GetMoveStateX("MoveLeftState");
	m_pObject->GetComponent<StateComponent>(ComponentName::state)->SetMoveStateX(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite); 
	pSprite->SetIsGoingLeft(true);
	pSprite->SetUpdate(true);
	pSprite->SetMaxedFrames(2);
}

MoveRightCommand::MoveRightCommand(GameObject* pObject)
	: Command(pObject){}

void MoveRightCommand::Execute()
{
	MoveStateX* pTemp = Fried::StateManager::GetInstance()->GetMoveStateX("MoveRightState");
	m_pObject->GetComponent<StateComponent>(ComponentName::state)->SetMoveStateX(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	pSprite->SetIsGoingLeft(false);
	pSprite->SetUpdate(true);
	pSprite->SetMaxedFrames(2);
}

ReleaseMovementCommand::ReleaseMovementCommand(GameObject* pObject)
	: Command(pObject){}

void ReleaseMovementCommand::Execute()
{
	MoveStateX* pTemp = Fried::StateManager::GetInstance()->GetMoveStateX("MoveStateXIdle");
	m_pObject->GetComponent<StateComponent>(ComponentName::state)->SetMoveStateX(pTemp);
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	pSprite->SetFrame(1);
	pSprite->SetMaxedFrames(2);
	pSprite->SetUpdate(false);
}

ShootBubbleCommand::ShootBubbleCommand(GameObject* pObject)
	:Command{ pObject } {}

void ShootBubbleCommand::Execute()
{
	SpriteComponent* pSprite = m_pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
	pSprite->SetUpdate(true);
	pSprite->SetDestRectHeight(32);
	pSprite->SetMaxedFrames(2);
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