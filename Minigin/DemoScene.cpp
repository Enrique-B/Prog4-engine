#include "MiniginPCH.h"
#include "DemoScene.h"

#include "GameObject.h"
#include "FPSObject.h"
#include "ResourceManager.h"

#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"


DemoScene::DemoScene()
	:Scene("DemoScene")
{
	Initialize();
}

void DemoScene::Update(float elapsedSec)
{
	for(auto& object : m_pObjects)
	{
		object->Update(elapsedSec);
	}
}

void DemoScene::Initialize()
{
	Fried::GameObject* pBackground{ new Fried::GameObject{} };
	pBackground->AddComponent(ComponentName::Texture, new TextureComponent{ Fried::ResourceManager::GetInstance()->LoadTexture("background.jpg") });
	Add(pBackground);

	Fried::GameObject* pLogo{ new Fried::GameObject{} };
	pLogo->AddComponent(ComponentName::Texture, new TextureComponent{ Fried::ResourceManager::GetInstance()->LoadTexture("logo.png") });
	pLogo->SetPosition(216, 180);
	Add(pLogo);

	Fried::GameObject* pText = new Fried::GameObject{};
	pText->AddComponent(ComponentName::Text ,new TextComponent("Programming 4 Assignment", Fried::ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36)));
	pText->SetPosition(80, 30);
	Add(pText);

	Fried::FPSObject* pFPSObject{ new Fried::FPSObject{} };
	Add(pFPSObject);
}
