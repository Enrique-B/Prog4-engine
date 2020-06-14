#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

ScoreComponent::ScoreComponent(unsigned char enemyType)noexcept
	:m_EnemyType{enemyType}
{
	SetComponentName(ComponentName::Score);
	if (enemyType < 0 || enemyType > 8)
	{
		m_Score = 0;
	}
	else
	{
		//https://strategywiki.org/wiki/Bubble_Bobble/Enemies
		size_t score[8]{500,3000,1000,4000,5000,7000,2000,6000 };
		m_Score = score[size_t(enemyType)];
	}
}

void ScoreComponent::Update(float elapsedSec) noexcept
{
	UNREFERENCED_PARAMETER(elapsedSec);
	GameObject* pObject = GetGameObject();
	if (pObject->HasComponent(ComponentName::Text))
	{
		pObject->GetComponent<TextComponent>(ComponentName::Text)->SetText("Score: " + std::to_string(m_Score));
	}
}
