#include "MiniginPCH.h"
#include "DemoScene.h"

#include "GameObject.h"
#include "ResourceManager.h"

#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "FPSComponent.h"

DemoScene::DemoScene()
	:Scene("DemoScene")
{
	Initialize();
}

void DemoScene::Update(float elapsedSec)
{
	// updating the components
	for(auto& object : m_pObjects)
	{
		object->Update(elapsedSec);
	}
	// doing some magic 
	TextComponent* pText = m_pFPSObject->GetComponent<TextComponent>(ComponentName::Text);
	FPSComponent* pFPS = m_pFPSObject->GetComponent<FPSComponent>(ComponentName::FPS);
	if (pFPS->DidFPSChange())
	{
		pText->SetText(std::to_string(pFPS->GetFPS()) + " FPS");
	}
}

void DemoScene::Initialize()
{
	GameObject* pBackground{ new GameObject{} };
	pBackground->AddComponent(new TextureComponent{ "background.jpg"});
	Add(pBackground);

	GameObject* pLogo{ new GameObject{} };
	pLogo->AddComponent(new TextureComponent{ "logo.png"});
	pLogo->SetPosition(216, 180);
	Add(pLogo);

	GameObject* pText = new GameObject{};
	pText->AddComponent(new TextComponent("Programming 4 Assignment", "Lingua.otf", 36));
	pText->SetPosition(80, 30);
	Add(pText);

	m_pFPSObject =  new GameObject{ };
	m_pFPSObject->AddComponent(new TextComponent{ "60 FPS", "Lingua.otf", 36 });
	m_pFPSObject->AddComponent(new FPSComponent{});

	Add(m_pFPSObject);
}
