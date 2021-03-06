#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "Structs.h"

template<typename T> 
inline void SafeDelete(T* toDelete)
{
	if (toDelete)
	{
		delete toDelete; 
		toDelete = nullptr; 
	}
}