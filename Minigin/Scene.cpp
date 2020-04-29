#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"
unsigned int Fried::Scene::m_IdCounter = 0;

Fried::Scene::Scene(const std::string& name) : m_Name(name) 
{
}

void Fried::Scene::Initialize()
{
}

Fried::Scene::~Scene()
{
	const size_t size{ m_pObjects.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pObjects[i]);
	}
	m_pObjects.clear();
}

void Fried::Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
}

void Fried::Scene::Update(float elapsedSec)
{
	for (const auto& object : m_pObjects)
	{
		object->Update(elapsedSec);
	}
}

void Fried::Scene::CollisionUpdate()
{
	std::vector< ColliderComponent*> staticColliders;
	std::vector<ColliderComponent*> dynamicColliders;
	// getting the static and dynamic colliders so i can check the the dynamic colliders on the static ones
	for (const auto& object : m_pObjects)
	{
		std::vector<ColliderComponent*> temp{ object->GetComponents<ColliderComponent>(ComponentName::collider) };
		const size_t size{ temp.size() };
		for (size_t i = 0; i < size; i++)
		{
			if (temp[i]->GetIsStatic())
				staticColliders.push_back(temp[i]);
			else
				dynamicColliders.push_back(temp[i]);
		}
	}
	const size_t dynamicSize{dynamicColliders.size()};
	const size_t staticSize{ staticColliders.size() };
	for (size_t i = 0; i < dynamicSize; i++)
	{
		const std::vector<Fried::line> lines{ dynamicColliders[i]->GetLines() };
		const size_t lineSize{ lines.size() };
		for (size_t j = 0; j < staticSize; j++)
		{
			for (size_t l = 0; l < lineSize; l++)
			{
				// to be continued
			}
		}
	}
}

void Fried::Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

void Fried::Scene::RenderCollision() const
{
	for (const auto& object : m_pObjects)
	{
		object->RenderCollision();
	}
}

