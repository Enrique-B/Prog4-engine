#include "MiniginPCH.h"
#include "GameObject.h"
#include "Scene.h"
#include "Renderer.h"
#include "Components.h"
#include "../Game/Subject.h"

GameObject::GameObject()
	:m_IsActive{true}
	,m_pScene{nullptr}
	, m_pSubject{ new Subject{} }
{
	m_pTranform = new TransformComponent{};
	m_pComponents.push_back(m_pTranform);
	m_pTranform->SetGameObject(this);
}

GameObject::~GameObject()
{
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pComponents[i]);
	}
	SafeDelete(m_pSubject);
}

void GameObject::Initialize()noexcept(false)
{
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pComponents[i]->Initialize();
	}
	std::vector<Observer*> pObservers = m_pScene->GetObservers();
	const size_t ObserverSize = pObservers.size();
	for (size_t i = 0; i < ObserverSize; i++)
	{
		m_pSubject->AddObserver(pObservers[i]);
	}
}

void GameObject::Update(float elapsedSec)
{
	if (!m_IsActive)
		return;
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pComponents[i]->Update(elapsedSec);
	}
}

void GameObject::Render() const noexcept
{
	if (!m_IsActive)
		return;
	const Fried::float2 pos = m_pTranform->GetPosition();
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pComponents[i]->Render(pos);
	}
}

void GameObject::RenderCollision() const noexcept
{
	if (!m_IsActive.load())
		return;
	const size_t size{ m_pComponents.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_pComponents[i]->RenderCollision();
	}
}

void GameObject::SetPosition(float x, float y)noexcept
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
			pComponent->SetGameObject(this);
		}
		else
		{
			throw std::runtime_error(std::string("there can only be one TransformComponent per GameObject\n"));
		}
	}
}

bool GameObject::HasComponent(ComponentName name) const noexcept
{
	for (const auto& component : m_pComponents)
	{
		if (component->GetComponentName() == name)
		{
			return true;
		}
	}
	return false;
}

void GameObject::SetIsActive(bool isActive)
{
	bool temp{ m_IsActive.load() };
	bool expected{ isActive };
	while (!m_IsActive.compare_exchange_weak(temp, expected)) {}
}

