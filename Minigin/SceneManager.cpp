#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Fried::SceneManager::Update(float elapsedSec)
{
	for(auto& scene : m_pScenes)
	{
		scene->Update(elapsedSec);
	}
}

void Fried::SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Render();
	}
}

Fried::SceneManager::~SceneManager()
{
	const size_t size{ m_pScenes.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pScenes[i]);
	}
}

void Fried::SceneManager::AddScene(Fried::Scene* pScene)
{
	if (pScene)
	{
		m_pScenes.push_back(pScene);
	}
	else
	{
		throw("scene was a nullpoiter");
	}
}
