#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Update(float elapsedSec)
{
	for(auto& scene : m_pScenes)
	{
		scene->Update(elapsedSec);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_pScenes)
	{
		scene->Render();
	}
}

SceneManager::~SceneManager()
{
	const size_t size{ m_pScenes.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pScenes[i]);
	}
}

void SceneManager::AddScene(Scene* pScene)
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
