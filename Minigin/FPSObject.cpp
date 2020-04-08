#include "MiniginPCH.h"
#include "FPSObject.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

Fried::FPSObject::FPSObject()
	:SceneObject()
{
	AddComponent(ComponentName::TransFrom, new TransformComponent{});
	AddComponent(ComponentName::Text, new TextComponent{"60 FPS", ResourceManager::GetInstance()->LoadFont("Lingua.otf", 36) });
	AddComponent(ComponentName::FPS, new FPSComponent{});
}

Fried::FPSObject::~FPSObject()
{
	for (const auto& pair : m_pComponents)
	{
		SafeDelete(pair.second);
	}
}

void Fried::FPSObject::Update(float elapsedSec)
{
	TextComponent* pText = dynamic_cast<TextComponent*>(m_pComponents.at(ComponentName::Text));
	FPSComponent* pFPS = dynamic_cast<FPSComponent*>(m_pComponents.at(ComponentName::FPS));
	if (pFPS->DidFPSChange())
	{
		pText->SetText(std::to_string(pFPS->GetFPS()) + " FPS");
	}
	for (const auto& map : m_pComponents)
	{
		map.second->Update(elapsedSec);
	}
}

void Fried::FPSObject::Render() const
{
	TransformComponent* pTransform = dynamic_cast<TransformComponent*>(m_pComponents.at(ComponentName::TransFrom));
	const Fried::float2 pos = pTransform->GetPosition();
	for (const auto& map : m_pComponents)
	{
		map.second->Render(pos);
	}
}

void Fried::FPSObject::AddComponent(ComponentName componentName, BaseComponent* pComponent)
{
	if (pComponent != nullptr)
	{
		if (m_pComponents.find(componentName) == m_pComponents.end())
		{
			m_pComponents.emplace(componentName, pComponent);
		}
		else
		{
			std::cout << "component was already in the in the GameObject\n";
		}
	}
}
