#include "MiniginPCH.h"
#include "Observer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "SceneManager.h"
#include "TextComponent.h"

Observer::Observer(Fried::Scene* pScene)noexcept
	:m_pScene{pScene}
{
}

EnemyObserver::EnemyObserver(Fried::Scene* pScene) noexcept
	:Observer(pScene)
	,m_AmountOfEnemies{ 0 }
	, m_IsNextLevelUnlocked{ false }
{
}

void EnemyObserver::Notify(Event event, GameObject* pObject)noexcept
{
	UNREFERENCED_PARAMETER(pObject);
	switch (event)
	{
	case Event::EnemyDeath:
		--m_AmountOfEnemies;
		if (m_AmountOfEnemies == 0)
		{
			m_IsNextLevelUnlocked = true;
		}
		break;
	case Event::PlayerDeath: 

	default:
		break;
	}
}

void EnemyObserver::SetAmountOfEnemies(int amountOfEnemies) noexcept
{
	m_AmountOfEnemies = amountOfEnemies; 
	m_IsNextLevelUnlocked = false;
}

PlayerObserver::PlayerObserver(Fried::Scene* pScene) noexcept
	:Observer(pScene), m_LivesPlayer1{4}, m_LivesPlayer2{ 4 }
{
}

void PlayerObserver::Notify(Event event, GameObject* pObject)noexcept
{
	switch (event)
	{
	case Event::PlayerDeath:
		if (pObject->HasComponent(ComponentName::Character))
		{
			CharacterComponent* pChar = pObject->GetComponent<CharacterComponent>(ComponentName::Character);
			int amountOfLives = pChar->GetAmountOfLives();
			Fried::SceneManager* pSceneManager = Fried::SceneManager::GetInstance();
			Fried::Scene* pScene = pSceneManager->GetUIScene(Fried::SceneManager::UI::GameMenu);
			std::vector<GameObject*>children = pScene->GetChildren();
			size_t size = children.size();
			std::vector<TextComponent*>texts;
			for (size_t i = 0; i < size; i++)
			{
				if (children[i]->HasComponent(ComponentName::Text) && !children[i]->HasComponent(ComponentName::Score))
				{
					texts.push_back(children[i]->GetComponent<TextComponent>(ComponentName::Text));
				}
			}
			if (pChar->GetCharacterNumber() == 0)
			{
				m_LivesPlayer1 = amountOfLives;
				texts[1]->SetText(std::to_string(amountOfLives));
			}
			else
			{
				m_LivesPlayer2 = amountOfLives;
				texts[2]->SetText(std::to_string(amountOfLives));
			}
			if (amountOfLives == 0)
			{
				pObject->SetIsActive(false);
				if (m_LivesPlayer1 == 0 && m_LivesPlayer2 == 0)
				{
					pSceneManager->SetReset();
					return;
				}
			}
		}
		break;
	default:
		break;
	}
}
