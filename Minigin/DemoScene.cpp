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
	GameObject* pBackground{ new GameObject{} };
	pBackground->AddComponent(ComponentName::Texture, new TextureComponent{ ResourceManager::GetInstance()->LoadTexture("background.jpg") });
	Add(pBackground);

	GameObject* pLogo{ new GameObject{} };
	pLogo->AddComponent(ComponentName::Texture, new TextureComponent{ ResourceManager::GetInstance()->LoadTexture("logo.png") });
	pLogo->SetPosition(216, 180);
	Add(pLogo);

	

	GameObject* pText = new GameObject{};
	pText->AddComponent(ComponentName::Text ,new TextComponent("Programming 4 Assignment", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36)));
	pText->SetPosition(80, 30);
	Add(pText);

	FPSObject* pFPSObject{ new FPSObject{} };
	Add(pFPSObject);
}
