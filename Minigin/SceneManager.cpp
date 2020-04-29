#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Fried::SceneManager::Update(float elapsedSec)
{
	m_pScenes[m_CurrentScene]->Update(elapsedSec);
}

void Fried::SceneManager::CollisionUpdate()
{
	m_pScenes[m_CurrentScene]->CollisionUpdate();
}

void Fried::SceneManager::Render()
{
	m_pScenes[m_CurrentScene]->Render();
	if (m_IsRenderingCollision)
		m_pScenes[m_CurrentScene]->RenderCollision();
}

void Fried::SceneManager::SetIsRenderingCollision(bool isRenderingCollision)
{
	m_IsRenderingCollision = isRenderingCollision;
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
		m_pScenes.push_back(pScene);
	else
		throw("scene was a nullpoiter");
}

void Fried::SceneManager::NextScene()
{
	m_CurrentScene++; 
	if (m_CurrentScene > m_pScenes.size()-1)
		m_CurrentScene = 0;
}
