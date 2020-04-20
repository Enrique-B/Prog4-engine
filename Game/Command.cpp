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

SwapWeapon::SwapWeapon(GameObject* pObject)
	:Command(pObject) 
{
}

void SwapWeapon::Execute()
{

}

Crouch::Crouch(GameObject* pObject)
	:Command(pObject)
{
}

void Crouch::Execute()
{

}

void PauseCommand::Execute()
{

}

void PlaceholderDPadUpCommand::Execute()
{

}

void PlaceholderDPadDownCommand::Execute()
{

}

void PlaceholderDPadRightCommand::Execute()
{

}

void PlaceholderDPadLeftCommand::Execute()
{

}

void PlaceHolderRightTrigger::Execute()
{

}

void PlaceHolderLeftTrigger::Execute()
{

}

void PlaceHolderRightBumper::Execute()
{

}

void PlaceHolderLeftBumper::Execute()
{

}

Command::Command(GameObject* pObject)
	:m_pObject{pObject}
{
}
