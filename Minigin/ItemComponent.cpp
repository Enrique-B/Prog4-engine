#include "MiniginPCH.h"
#include "ItemComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "SpriteComponent.h"
#include "StateComponent.h"
#include "StateManager.h"
#include "ColliderComponent.h"
#include "ScoreComponent.h"
#include "SceneManager.h"

ItemComponent::ItemComponent(unsigned char enemyType) noexcept
	:m_EnemyType{enemyType}
	, m_CharacterNumber{0}
{
	SetComponentName(ComponentName::Item);
}


void ItemComponent::Initialize()
{
	GameObject* pObject = GetGameObject();
	const float temp{ float(m_EnemyType) * 16 };
	pObject->GetComponent<SpriteComponent>(ComponentName::Sprite)->SetDestRectY(temp);
	pObject->GetComponent<StateComponent>(ComponentName::State)
		->SetMoveStateX(Fried::StateManager::GetInstance()->GetMoveStateX("MoveStateXIdle"));
	pObject->GetComponent<SpriteComponent>(ComponentName::Sprite)->SetMaxedFrames(4);
	m_CharacterNumber = 0;
}

void ItemComponent::Update(float )
{
	GameObject* pObject = GetGameObject();
	ColliderComponent* pCollider = pObject->GetComponent<ColliderComponent>(ComponentName::Collider); 
	StateComponent* pState = pObject->GetComponent<StateComponent>(ComponentName::State);
	if (pCollider->HasTrigger(ColliderTrigger::Bottom))
	{
		SpriteComponent* pSprite = pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
		pSprite->SetTexture("drops.png");
		pSprite->SetMaxedFrames(1);
		pSprite->SetFrame(0);
		pState->SetMoveStateY(Fried::StateManager::GetInstance()->GetMoveStateY("MoveStateYNone"));
		if (pCollider->HasTrigger(ColliderTrigger::Player))
		{
			const size_t thisScore = pObject->GetComponent<ScoreComponent>(ComponentName::Score)->GetScore(); 
			// add score to scene 
			std::vector<GameObject*> pChildren = Fried::SceneManager::GetInstance()->GetUIScene(Fried::SceneManager::UI::GameMenu)->GetChildren();
			const size_t size{ pChildren.size() };
			std::vector<ScoreComponent*> pScores;
			for (size_t i = 0; i < size; i++)
			{
				if (pChildren[i]->HasComponent(ComponentName::Text) && pChildren[i]->HasComponent(ComponentName::Score))
				{
					pScores.push_back(pChildren[i]->GetComponent<ScoreComponent>(ComponentName::Score));
				}
			}
			pScores[m_CharacterNumber]->AddScore(thisScore);
			// set to non active
			pObject->SetIsActive(false);
		}
	}
}
