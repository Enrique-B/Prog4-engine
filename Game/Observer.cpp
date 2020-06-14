#include "MiniginPCH.h"
#include "Observer.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

Observer::Observer(Fried::Scene* pScene)noexcept
	:m_pScene{pScene}
	,m_AmountOfEnemies{0}
	,m_IsNextLevelUnlocked{false}
{
}

void Observer::Notify(Event event)noexcept
{
	switch (event)
	{
	case Event::EnemyDeath:
		--m_AmountOfEnemies;
		if (m_AmountOfEnemies == 0)
		{
			m_IsNextLevelUnlocked = true;
		}
		break;
	default:
		break;
	}
}

void Observer::SetAmountOfEnemies(int amountOfEnemies) noexcept
{
	m_AmountOfEnemies = amountOfEnemies; 
}
