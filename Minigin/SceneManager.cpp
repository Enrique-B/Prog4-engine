#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Fried::SceneManager::Update(float elapsedSec)
{
	m_pScenes[m_CurrentScene]->Update(elapsedSec);
}

void Fried::SceneManager::CollisionUpdate(float elapsedSec)noexcept
{
	m_pScenes[m_CurrentScene]->CollisionUpdate(elapsedSec);
}

void Fried::SceneManager::Render()noexcept
{
	m_pScenes[m_CurrentScene]->Render();
	if (m_IsRenderingCollision)
		m_pScenes[m_CurrentScene]->RenderCollision();
}

void Fried::SceneManager::DeactivateNonActiveGameObjects() noexcept(false)
{
	m_pScenes[m_CurrentScene]->DeactivateNonActiveGameObjects();
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
#ifdef _DEBUG
		if (std::find(m_pScenes.cbegin(), m_pScenes.cend(), pScene) != m_pScenes.cend())
		{
			throw std::runtime_error(std::string("SceneManager::AddScene scene was already in vector\n"));
		}
#endif 
		m_pScenes.push_back(pScene);
	}
	else
		throw std::runtime_error(std::string("scene was a nullpoiter"));
}

void Fried::SceneManager::NextScene()noexcept
{
	m_CurrentScene++; 
	if (m_CurrentScene > m_pScenes.size()-1)
		m_CurrentScene = 0;
#ifdef _DEBUG
	std::cout << m_CurrentScene << std::endl;
#endif // _DEBUG
}

Fried::Scene* Fried::SceneManager::GetNextScene()noexcept
{
	if (m_CurrentScene +1 > m_pScenes.size() - 1)
		return nullptr;
	return m_pScenes[m_CurrentScene + 1];
}

Fried::Scene* Fried::SceneManager::GetPreviousScene()noexcept
{
	if (m_CurrentScene - 1 < 0)
		return nullptr;
	return m_pScenes[m_CurrentScene - 1];
}
