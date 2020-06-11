#include "MiniginPCH.h"
#include "BubbleComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "Structs.h"
#include "StateComponent.h"
#include "StateManager.h"

BubbleComponent::BubbleComponent(bool m_IsGoingRight)
	: m_IsGoingRight{ m_IsGoingRight }
	, m_HasReachedPos{false}
	, m_NextPos{0,0}
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
	if (!m_HasReachedPos)
	{
		StateComponent* pState = pObject->GetComponent<StateComponent>(ComponentName::state); 
		Fried::StateManager * stateMan = Fried::StateManager::GetInstance();
		pState->SetMoveStateX(m_IsGoingRight ? stateMan->GetMoveStateX("MoveRightState") : stateMan->GetMoveStateX("MoveLeftState"));
		const Fried::float2 pos = pObject->GetTransform()->GetPosition();
		if (AreFloatsEqual(pos.x, m_NextPos.x) || m_IsHitByEnemy)
			m_HasReachedPos = true;
	}
	else
	{
		//ColliderComponent* pCollider = pObject->GetComponent<ColliderComponent>(ComponentName::collider);
	}
}