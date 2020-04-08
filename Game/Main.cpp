#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "FriedEngine.h"

int main(int, char* []) 
{
	Fried::FriedEngine engine;
	engine.Run();
	return 0;
}