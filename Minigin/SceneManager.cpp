#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "../Game/Observer.h"

Fried::SceneManager::~SceneManager()
{
	size_t size{ m_pScenes.size() };
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pScenes[i]);
	}
	for (size_t i = 0; i < m_pUIScenes.size(); i++)
	{
		SafeDelete(m_pUIScenes[i]);
	}
}

void Fried::SceneManager::AddUIScene(Scene* pScene, UI uiType) noexcept(false)
{
	if (m_pUIScenes[unsigned int(uiType)] == nullptr)
	{
		m_pUIScenes[unsigned int(uiType)] = pScene;
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
	if (m_CurrentScene > m_pScenes.size() - 1)
		m_CurrentScene = 0;
#ifdef _DEBUG
	std::cout << m_CurrentScene << std::endl;
#endif // _DEBUG
}


Fried::Scene* Fried::SceneManager::GetNextScene()const noexcept
{
	if (m_CurrentScene + 1 > m_pScenes.size() - 1)
		return nullptr;
	return m_pScenes[m_CurrentScene + 1];
}

Fried::Scene* Fried::SceneManager::GetPreviousScene()const noexcept
{
	if (m_CurrentScene - 1 < 0)
		return nullptr;
	return m_pScenes[m_CurrentScene - 1];
}

void Fried::SceneManager::Update(float elapsedSec)
{
	if (m_CurrentUIScene == UI::GameMenu)
		m_pScenes[m_CurrentScene]->Update(elapsedSec);
	m_pUIScenes[unsigned int(m_CurrentUIScene)]->Update(elapsedSec);
}

void Fried::SceneManager::CollisionUpdate(float elapsedSec)noexcept
{
	if (m_CurrentUIScene == UI::GameMenu)
		m_pScenes[m_CurrentScene]->CollisionUpdate(elapsedSec);
}

void Fried::SceneManager::Render()noexcept
{
	if (m_CurrentUIScene != UI::StartMenu)
	{
		m_pScenes[m_CurrentScene]->Render();
		if (m_IsRenderingCollision)
			m_pScenes[m_CurrentScene]->RenderCollision();
	}
	m_pUIScenes[unsigned int(m_CurrentUIScene)]->Render();
}

void Fried::SceneManager::DeactivateNonActiveGameObjects() noexcept(false)
{
	m_pScenes[m_CurrentScene]->DeactivateNonActiveGameObjects();
	if (m_Reset)
	{
		Reset();
		m_Reset = false;
	}
}

void Fried::SceneManager::Reset() // only get's called when both players are dead
{
	const std::vector<GameObject*> pCurrentSceneObjects = m_pScenes[m_CurrentScene]->GetDeactivatedGameObjects();
	size_t size = pCurrentSceneObjects.size();
	std::vector<GameObject*> pCharacters;
	size_t amountOfCharactersFound{};
	for (size_t i = 0; i < size; i++)
	{
		if (pCurrentSceneObjects[i]->HasComponent(ComponentName::Character))
		{
			m_pScenes[m_CurrentScene]->RemoveGameObjectFromNonActive(pCurrentSceneObjects[i]);
			pCharacters.push_back(pCurrentSceneObjects[i]);
			amountOfCharactersFound++;
			if (amountOfCharactersFound == 2)
				break;
		}
	}
	// finding the lost characters
	if (amountOfCharactersFound != 2)
	{
		for (size_t i = 0; i < m_CurrentScene; i++)
		{
			const std::vector<GameObject*> pUnusedSceneObjects = m_pScenes[m_CurrentScene]->GetDeactivatedGameObjects();
			size = pUnusedSceneObjects.size();
			for (size_t j = 0; j < size; j++)
			{
				if (pCurrentSceneObjects[j]->HasComponent(ComponentName::Character))
				{
					m_pScenes[i]->RemoveGameObject(pCurrentSceneObjects[j]);
					pCharacters.push_back(pCurrentSceneObjects[j]);
					amountOfCharactersFound++;
					if (amountOfCharactersFound == 2)
						break;
				}
			}
		}
	}
	//adding the characters back into the first scene 
	for (size_t i = 0; i < amountOfCharactersFound; i++)
	{
		m_pScenes[0]->AddGameObject(pCharacters[i]);
	}
	// resetting every scene 
	for (size_t i = 0; i <= m_CurrentScene; i++)
	{
		m_pScenes[i]->Reset();
	}
	Fried::Scene* pUIScene = m_pUIScenes[int(UI::GameMenu)];
	std::vector<GameObject*> copy = pUIScene->GetChildren();
	size = copy.size();
	size_t score{0};
	size_t lives{0};
	// finding the score of both players, finding the lives texture/text 
	for (size_t i = 0; i < size; i++)
	{
		bool hasText = copy[i]->HasComponent(ComponentName::Text);
		if (hasText && copy[i]->HasComponent(ComponentName::Texture))
		{
			lives++;
			copy[i]->GetComponent<TextComponent>(ComponentName::Text)->SetText("4");
		}
		else if (hasText)
		{
			score++; 
			if (score >= 2)
			{
				copy[i]->GetComponent<TextComponent>(ComponentName::Text)->SetText("score: 0");
			}
		}
	}
	copy.clear();
	if (lives != 2 || score != 3)
	{
		copy = pUIScene->GetDeactivatedGameObjects();
		size = copy.size();
		for (size_t i = 0; i < size; i++)
		{
			bool hasText = copy[i]->HasComponent(ComponentName::Text);
			if (hasText && copy[i]->HasComponent(ComponentName::Texture))
			{
				lives++;
				copy[i]->GetComponent<TextComponent>(ComponentName::Text)->SetText("4");
				if (lives == 2 && score == 3)
				{
					break;
				}
			}
			else if (hasText)
			{
				score++;
				if (score >= 2)
				{
					copy[i]->GetComponent<TextComponent>(ComponentName::Text)->SetText("score: 0");
					if (lives == 2 && score == 3)
					{
						break;
					}
				}
			}
		}
	}
	PlayerObserver* playerObserver = static_cast<PlayerObserver*>(pUIScene->GetObservers()[1]);
	playerObserver->SetPlayer1Lives(4);
	playerObserver->SetPlayer2Lives(4);
	SetUIScene(Fried::SceneManager::UI::StartMenu);
	m_CurrentScene = 0;
}

Fried::SceneManager::SceneManager()
	: m_CurrentScene{ 0 }, m_IsRenderingCollision(false), m_CurrentUIScene{ UI::StartMenu }, m_Reset{false}
{
	m_pUIScenes.push_back(nullptr);
	m_pUIScenes.push_back(nullptr);
	m_pUIScenes.push_back(nullptr);
}
