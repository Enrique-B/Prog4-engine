#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"

GameObject::GameObject()
{
	m_pTranform = new TransformComponent{};
	m_pComponents.push_back(m_pTranform);
}

GameObject::~GameObject()
{
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pComponents[i]);
	}
}

void GameObject::Update(float elapsedSec)
{
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pComponents[i]->Update(elapsedSec);
	}
}

void GameObject::Render() const
{
	const Fried::float2 pos = m_pTranform->GetPosition();
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pComponents[i]->Render(pos);
	}
}

void GameObject::SetPosition(float x, float y)
{
	m_pTranform->SetPosition(x, y);
}

void GameObject::AddComponent(BaseComponent* pComponent)
{
	if (pComponent != nullptr)
	{
		if (pComponent->GetComponentName() != ComponentName::TransFrom)
		{
			m_pComponents.push_back(pComponent);
		}
		else
		{
			std::cout << "there can only be one TransformComponent per GameObject" << std::endl;
		}
	}
}

bool GameObject::HasComponent(ComponentName name) const
{
	for (auto component : m_pComponents)
	{
		if (component->GetComponentName() == name)
		{
			return true;
		}
	}
	return false;
}
