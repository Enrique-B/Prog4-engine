#include "MiniginPCH.h"
#include "Command.h"
#include "GameObject.h"
#include "StateComponent.h"
#include <iostream>
#include "SceneManager.h"

JumpCommand::JumpCommand(GameObject* pObject)
	:Command(pObject)
{
}

void JumpCommand::Execute()
{
	StateComponent* pState  = m_pObject->GetComponent<StateComponent>(ComponentName::state);
	pState->GetCurrentState();
}

ChangeSceneCommand::ChangeSceneCommand()
	:Command(nullptr)
{
}

void ChangeSceneCommand::Execute()
{
	Fried::SceneManager::GetInstance()->NextScene();
}

Command::Command(GameObject* pObject)
	:m_pObject{pObject}
{
}

void DebugRenderCommand::Execute()
{
	Fried::SceneManager::GetInstance()->SetIsRenderingCollision(!Fried::SceneManager::GetInstance()->GetIsRenderingCollision());
}
