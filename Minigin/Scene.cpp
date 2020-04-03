#include "MiniginPCH.h"
#include "Scene.h"
#include "SceneObject.h"


unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {
	Initialize();
}

void Scene::Initialize()
{
}


Scene::~Scene()
{
	const size_t size{ m_pObjects.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pObjects[i]);
	}
}

void Scene::Add(SceneObject* object)
{
	m_pObjects.push_back(object);
}


void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

