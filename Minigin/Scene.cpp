#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
unsigned int Fried::Scene::m_IdCounter = 0;

Fried::Scene::Scene(const std::string& name) : m_Name(name) {
	Initialize();
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
}

void Fried::Scene::Add(GameObject* object)
{
	m_pObjects.push_back(object);
}


void Fried::Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

