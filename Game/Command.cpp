#include "MiniginPCH.h"
#include "Command.h"
#include <iostream>

void JumpCommand::Execute()
{
	std::cout << "Jump button has been pressed \n";
}

void FireCommand::Execute()
{
	std::cout << "Fire button has been pressed \n";
}

void SwapWeapon::Execute()
{
	std::cout << "SwapWeapon button has been pressed \n";
}

void Crouch::Execute()
{
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
