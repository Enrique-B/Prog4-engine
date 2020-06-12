#include "MiniginPCH.h"
#include "BubbleComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "Structs.h"
#include "StateComponent.h"
#include "StateManager.h"
#include "SpriteComponent.h"

BubbleComponent::BubbleComponent(bool m_IsGoingRight)
	: m_IsGoingRight{ m_IsGoingRight }
	, m_HasReachedPos{false}
	, m_NextPos{0,0}
	, m_EnemyType{unsigned char(-1)}
	, m_IsHitByEnemy{false}
{
	SetComponentName(ComponentName::bubble);
}

BubbleComponent::~BubbleComponent()
{
}

void BubbleComponent::Initialize()
{
	const Fried::float2 pos = GetGameObject()->GetTransform()->GetPosition();
	m_NextPos.x = pos.x + int(m_IsGoingRight ? 1 : -1) * 50;
	m_NextPos.y = pos.y;
}

void BubbleComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	GameObject* pObject = GetGameObject();
	StateComponent* pState = pObject->GetComponent<StateComponent>(ComponentName::state);
	Fried::StateManager* stateMan = Fried::StateManager::GetInstance();
	if (!m_HasReachedPos)
	{
		ColliderComponent* pCollider = pObject->GetComponent<ColliderComponent>(ComponentName::collider);
		pState->SetMoveStateX(m_IsGoingRight ? stateMan->GetMoveStateX("MoveRightState") : stateMan->GetMoveStateX("MoveLeftState"));
		SpriteComponent* pSprite = pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
		if (pCollider->HasTrigger(ColliderTrigger::EnemyHit) && !m_IsHitByEnemy)
		{
			m_IsHitByEnemy = true;
			const float frameHeight{ 16.f };
			pSprite->SetDestRectY((m_EnemyType + 2) * frameHeight);
		}

		const Fried::float2 pos = pObject->GetTransform()->GetPosition();
		if (AreFloatsEqual(pos.x, m_NextPos.x) || m_IsHitByEnemy)
			m_HasReachedPos = true;
		else if (pCollider->HasTrigger(ColliderTrigger::left) || pCollider->HasTrigger(ColliderTrigger::right))
		{
			m_HasReachedPos = true;
		}
	}
	else
	{
		ColliderComponent* pCollider = pObject->GetComponent<ColliderComponent>(ComponentName::collider);
		SpriteComponent* pSprite = pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);
		if (pCollider->HasTrigger(ColliderTrigger::EnemyHit) && !m_IsHitByEnemy)
		{
			m_IsHitByEnemy = true;
			const float frameHeight{16.f};
			pSprite->SetDestRectY((m_EnemyType + 2) * frameHeight);
		}
		if (pCollider->HasTrigger(ColliderTrigger::PlayerHit))
		{
			GetGameObject()->SetIsActive(false);
		}
		if (m_IsHitByEnemy)
		{
			pState->SetMoveStateY(stateMan->GetMoveStateY("JumpState"));
		}
	}
}