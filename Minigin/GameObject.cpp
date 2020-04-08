#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"

Fried::GameObject::~GameObject()
{
	for (auto pair : m_pComponents)
	{
		SafeDelete(pair.second);
	}
}

void Fried::GameObject::Update(float elapsedSec)
{
	for (const auto& map : m_pComponents)
	{
		map.second->Update(elapsedSec);
	}
}

void Fried::GameObject::Render() const
{
	if (!m_CanRender)
	{
		return;
	}
	TransformComponent* pTransform = dynamic_cast<TransformComponent*>(m_pComponents.at(ComponentName::TransFrom));
	const float2 pos = pTransform->GetPosition();
	for (const auto& map : m_pComponents)
	{
		map.second->Render(pos);
	}
}

void Fried::GameObject::SetPosition(float x, float y)
{
	TransformComponent* pTransform = static_cast<TransformComponent*>(m_pComponents.at(ComponentName::TransFrom));
	pTransform->SetPosition(x, y);
}

void Fried::GameObject::AddComponent(ComponentName componentName, BaseComponent* pComponent)
{
	if (pComponent != nullptr)
	{
		if (m_pComponents.find(componentName) == m_pComponents.end())
		{
			m_pComponents.emplace(componentName, pComponent);
			if (componentName == ComponentName::Texture || componentName == ComponentName::Text)
			{
				m_CanRender = true;
			}
		}
		else
		{
			std::cout << "component was already in the in the GameObject\n";
		}
	}
}

Fried::GameObject::GameObject()
	:m_CanRender{false}
{
	m_pComponents.emplace(ComponentName::TransFrom, new TransformComponent{});
}
