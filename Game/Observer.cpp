#include "MiniginPCH.h"
#include "Observer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "CharacterComponent.h"

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
}

PlayerObserver::PlayerObserver(Fried::Scene* pScene) noexcept
	:Observer(pScene), m_LivesPlayer1{4}, m_LivesPlayer2{ 4 }
{

}

void PlayerObserver::Notify(Event event, GameObject* pObject)noexcept
{
	switch (event)
	{
	case Event::EnemyDeath:
		break;
	case Event::PlayerDeath:
		if (pObject->HasComponent(ComponentName::Character))
		{
			CharacterComponent* pChar = pObject->GetComponent<CharacterComponent>(ComponentName::Character);
			int amountOfLives = pChar->GetAmountOfLives();
			if (amountOfLives == 0)
			{
				pObject->SetIsActive(false);
			}
			pChar->GetCharacterNumber() == 0 ? m_LivesPlayer1 = amountOfLives : m_LivesPlayer2 = amountOfLives;
			std::cout << "Player1Lives:  " << m_LivesPlayer1 << "Player2Lives " << m_LivesPlayer2 << " \n";
		}
		break;
	default:
		break;
	}
}
