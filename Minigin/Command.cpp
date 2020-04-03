#include "Command.h"
#include "ServiceLocator.h"
#include <iostream>
void JumpCommand::Execute()
{
	ServiceLocator::GetInstance()->GetAudio()->PlayMusic(0);
	std::cout << "Jump button has been pressed \n";
}

void FireCommand::Execute()
{
	ServiceLocator::GetInstance()->GetAudio()->PlayMusic(1);
	std::cout << "Fire button has been pressed \n";
}

void SwapWeapon::Execute()
{
	ServiceLocator::GetInstance()->GetAudio()->PlayMusic(2);
	std::cout << "SwapWeapon button has been pressed \n";
}

void Crouch::Execute()
{
	ServiceLocator::GetInstance()->GetAudio()->PlayMusic(3);
	std::cout << "Crouch button has been pressed \n";
}

void PauseCommand::Execute()
{
	std::cout << "Pause button has been pressed \n";
}

void PlaceholderDPadUpCommand::Execute()
{
	std::cout << "PlaceholderDPadUpCommand button has been pressed \n";
}

void PlaceholderDPadDownCommand::Execute()
{
	std::cout << "PlaceholderDPadDownCommand button has been pressed \n";
}

void PlaceholderDPadRightCommand::Execute()
{
	std::cout << "PlaceholderDPadRightCommand button has been pressed \n";
}

void PlaceholderDPadLeftCommand::Execute()
{
	std::cout << "PlaceholderDPadLeftCommand button has been pressed \n";
}

void PlaceHolderRightTrigger::Execute()
{
	std::cout << "PlaceholderRightTriggerCommand button has been pressed \n";
}

void PlaceHolderLeftTrigger::Execute()
{
	std::cout << "PlaceholderLeftTriggerCommand button has been pressed \n";
}

void PlaceHolderRightBumper::Execute()
{
	std::cout << "PlaceholderRightBumperCommand button has been pressed \n";
}

void PlaceHolderLeftBumper::Execute()
{
	std::cout << "PlaceholderLeftBumperCommand button has been pressed \n";
}
