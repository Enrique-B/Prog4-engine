#include "MiniginPCH.h"
#include "EnemyComponent.h"
#include "GameObject.h"
#include "Structs.h"
#include "ColliderComponent.h"
#include "StateComponent.h"
#include "StateManager.h"
#include "SpriteComponent.h"
#include "Scene.h"

EnemyComponent::EnemyComponent(unsigned char enemyType, const float amountOfSecIdle, bool islookingleft)noexcept
	:BaseComponent()
	, m_EnemyType{ enemyType }
	, m_AmountOfSecIdle{ amountOfSecIdle }
	, m_IsLookingRight{ !islookingleft}
	, m_pColliderComp{nullptr}
	, m_pStateComp{nullptr}
	, m_AmountOfSecAlive{0}
	, m_IsRaycasting{false}
	, m_IsLastStateJump{true}
	, m_AmountOfRaycast{0}
{
	SetComponentName(ComponentName::enemy);
}

void EnemyComponent::Initialize()
{
	GameObject* pObject = GetGameObject(); 
	if (pObject->HasComponent(ComponentName::state))
	{
		m_pStateComp = pObject->GetComponent<StateComponent>(ComponentName::state);
	}
	else
	{
		throw std::runtime_error(std::string("EnemyComponent::Initialize() does not have a statecomponent"));
	}
	if (pObject->HasComponent(ComponentName::state))
	{
		m_pColliderComp = pObject->GetComponent<ColliderComponent>(ComponentName::collider);
	}
	else
	{
		throw std::runtime_error(std::string("EnemyComponent::Initialize() does not have a colliderComp"));
	}
	pObject->GetComponent< SpriteComponent>(ComponentName::Sprite)->SetIsGoingLeft(!m_IsLookingRight);
}

void EnemyComponent::Update(float elapsedSec)
{
	Fried::StateManager* stateMan = Fried::StateManager::GetInstance();
	m_AmountOfSecAlive += elapsedSec; 
	m_TimeForNextCollisionCheck += elapsedSec; 
	if (m_AmountOfSecAlive < m_AmountOfSecIdle)
	{
		m_pStateComp->SetMoveStateY(stateMan->GetMoveStateY("MoveStateYNone"));
		return;
	}
	if (m_TimeForNextCollisionCheck > 0.2f)
	{
		m_TimeForNextCollisionCheck = 0;
		const bool SwitchSides = m_pColliderComp->HasTrigger(ColliderTrigger::left) || m_pColliderComp->HasTrigger(ColliderTrigger::right);
		if (SwitchSides)
		{
			m_IsLookingRight = !m_IsLookingRight;
			GetGameObject()->GetComponent< SpriteComponent>(ComponentName::Sprite)->SetIsGoingLeft(!m_IsLookingRight);
			const Fried::float2 middlePoint{ m_pColliderComp->GetMiddlePoint() };
			const SDL_Rect colliderRect = m_pColliderComp->GetCollisionRect();
			const float x = middlePoint.x + int(!m_IsLookingRight * -1) * (colliderRect.w + 1); 
			// raycast the other direction 
			Fried::HitInfo info; 
			// if the character isn't on the row, jump up 
			if (!GetGameObject()->GetScene()->Raycast(Fried::line({ x, middlePoint.y }, { x + int(!m_IsLookingRight * -1) * 70 ,
				middlePoint.y }), false, true, info))
			{
				m_pStateComp->SetMoveStateY(stateMan->GetMoveStateY("JumpState"));
				m_IsLastStateJump = true;
			}
			else
			{
				// start moving towards the player and still raycast 
			}
			// look the opposite side and raycast after it landed 
			// when it's raycasting set the sprite to 2 

		}
	}
	const bool isOnGround = m_pColliderComp->HasTrigger(ColliderTrigger::Bottom);

	if (!m_IsRaycasting)
	{
		if (isOnGround || !m_IsLastStateJump)
			m_pStateComp->SetMoveStateX(m_IsLookingRight ? stateMan->GetMoveStateX("MoveRightState") : stateMan->GetMoveStateX("MoveLeftState"));
		else
			m_pStateComp->SetMoveStateX(stateMan->GetMoveStateX("MoveStateXIdle"));
	}

}