// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"

int main()
{
	Minigin engine;
	engine.Run();
	return 0;
}
