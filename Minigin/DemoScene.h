#pragma once
#include "Scene.h"
class TextComponent;
class DemoScene : public Scene
{
public: 
	DemoScene(); 
	virtual void Update(float elapsedSec);

protected: 
	virtual void Initialize();
private: 
};

