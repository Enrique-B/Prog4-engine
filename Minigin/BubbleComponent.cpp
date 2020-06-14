#include "MiniginPCH.h"
#include "BubbleComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "Structs.h"
#include "StateComponent.h"
#include "StateManager.h"
#include "SpriteComponent.h"
#include "ItemComponent.h"

#include "../Game/Observer.h"
#include "../Game/Subject.h"

BubbleComponent::BubbleComponent(bool m_IsGoingRight)
	: m_IsGoingRight{ m_IsGoingRight }
	, m_HasReachedPos{false}
	, m_NextPos{0,0}
	, m_EnemyType{unsigned char(-1)}
	, m_IsHitByEnemy{false}
	, m_IsHitByPlayer{false}
	, m_TimeAllive{0}
{
	SetComponentName(ComponentName::Bubble);
}

void BubbleComponent::Initialize()
{
	const Fried::float2 pos = GetGameObject()->GetTransform()->GetPosition();
	m_NextPos.x = pos.x + int(m_IsGoingRight ? 1 : -1) * 50;
	m_NextPos.y = pos.y;
	m_TimeAllive = 0;
	m_EnemyType = unsigned char(-1);
	m_IsHitByEnemy = false;
	m_IsHitByPlayer = false;
	m_HasReachedPos = false; 
}

void BubbleComponent::Update(float elapsedSec)
{
	m_TimeAllive += elapsedSec; 
	GameObject* pObject = GetGameObject();
	Fried::StateManager* stateMan = Fried::StateManager::GetInstance();
	StateComponent* pState = pObject->GetComponent<StateComponent>(ComponentName::State);
	ColliderComponent* pCollider = pObject->GetComponent<ColliderComponent>(ComponentName::Collider);
	SpriteComponent* pSprite = pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);

	// safety check
	const Fried::float2 pos = pObject->GetTransform()->GetPosition();
	if (pos.y < 0)
	{
		pObject->GetTransform()->SetPosition(pos.x,float( 40 + 24 * 2));
	}

	if (m_TimeAllive > 10)
	{
		m_TimeAllive = 0;
		const float frameHeight{ 16.f };
		pSprite->SetDestRectY(2 * frameHeight);
		pSprite->SetFrame(0);
		pSprite->SetIsGoingLeft(false);
		pState->SetMoveStateY(stateMan->GetMoveStateY("MoveStateYNone"));
		pState->SetMoveStateX(stateMan->GetMoveStateX("MoveStateXIdle"));
		if (m_IsHitByEnemy && !m_IsHitByPlayer)
		{
			Fried::Scene* pScene = pObject->GetScene();
			const std::vector<GameObject*> deactivatedObjects =  pScene->GetDeactivatedGameObjects();
			const size_t size{ deactivatedObjects.size() };
			for (size_t i = 0; i < size; i++)
			{
				if (deactivatedObjects[i]->HasComponent(ComponentName::Enemy))
				{
					if (deactivatedObjects[i]->GetComponent<EnemyComponent>(ComponentName::Enemy)
						->GetEnemyType() == m_EnemyType)
					{
						GameObject* pCopy = deactivatedObjects[i]; 
						pScene->RemoveGameObjectFromNonActive(pCopy);
						pScene->AddGameObject(pCopy);
						pCopy->GetTransform()->SetPosition(pObject->GetTransform()->GetPosition());
						m_IsHitByEnemy = false;
						m_EnemyType = unsigned char(-1);
						break;
					}
				}
			}
		}
		m_IsHitByPlayer = true;
		return;
	}
	if (m_IsHitByPlayer)
	{
		pState->SetMoveStateY(stateMan->GetMoveStateY("MoveStateYNone"));
		pState->SetMoveStateX(stateMan->GetMoveStateX("MoveStateXIdle"));
		if (pSprite->IsAnimationFinished())
		{
			if (m_IsHitByEnemy)
			{
				pObject->GetSubject()->Notify(Event::EnemyDeath, pObject);
				std::vector<GameObject*> pNonActiveObjects = pObject->GetScene()->GetDeactivatedGameObjects();
				const size_t size{ pNonActiveObjects.size() };
				for (size_t i = 0; i < size; i++)
				{
					if (pNonActiveObjects[i]->HasComponent(ComponentName::Item))
					{
						if (pNonActiveObjects[i]->GetComponent<ItemComponent>(ComponentName::Item)
							->GetEnemyType() == m_EnemyType)
						{
							pObject->GetScene()->RemoveGameObjectFromNonActive(pNonActiveObjects[i]);
							pObject->GetScene()->AddGameObject(pNonActiveObjects[i]);
							pNonActiveObjects[i]->GetTransform()->SetPosition(pObject->GetTransform()->GetPosition());
							break;
						}
					}
				}
			}
			pObject->SetIsActive(false);
		}
		return;
	}
	if (pCollider->HasTrigger(ColliderTrigger::Player))
	{
		m_IsHitByPlayer = true;
		const float frameHeight{ 16.f };
		pSprite->SetDestRectY(2 * frameHeight);
		pSprite->SetFrame(0);
		pSprite->SetIsGoingLeft(false);
		pState->SetMoveStateY(stateMan->GetMoveStateY("MoveStateYNone"));
		pState->SetMoveStateX(stateMan->GetMoveStateX("MoveStateXIdle"));
	}
	if (!m_HasReachedPos)
	{
		pState->SetMoveStateY(stateMan->GetMoveStateY("MoveStateYNone"));
		pState->SetMoveStateX(m_IsGoingRight ? stateMan->GetMoveStateX("MoveStateRightFast") 
			: stateMan->GetMoveStateX("MoveStateLeftFast"));
		if (pCollider->HasTrigger(ColliderTrigger::Enemy) && !m_IsHitByEnemy)
		{
			m_IsHitByEnemy = true;
			const float frameHeight{ 16.f };
			pSprite->SetDestRectY((m_EnemyType + 3) * frameHeight);
		}

		if (AreFloatsEqual(pos.x, m_NextPos.x) || m_IsHitByEnemy || 
			pCollider->HasTrigger(ColliderTrigger::left) || pCollider->HasTrigger(ColliderTrigger::right))
		{
			m_HasReachedPos = true;
			pState->SetMoveStateY(stateMan->GetMoveStateY("JumpState"));
			pState->SetMoveStateX(stateMan->GetMoveStateX("MoveStateXIdle"));
		}
	}
	else
	{
		if (pCollider->HasTrigger(ColliderTrigger::left) || pCollider->HasTrigger(ColliderTrigger::right))
			m_IsGoingRight = !m_IsGoingRight;
		pState->SetMoveStateX(m_IsGoingRight ? stateMan->GetMoveStateX("MoveStateRightFast")
			: stateMan->GetMoveStateX("MoveStateLeftFast"));
		pCollider->HasTrigger(ColliderTrigger::Top) ? pState->SetMoveStateY(stateMan->GetMoveStateY("MoveStateYNone")) 
			: pState->SetMoveStateY(stateMan->GetMoveStateY("JumpState"));
	}
}