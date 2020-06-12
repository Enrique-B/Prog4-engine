#include "MiniginPCH.h"
#include "StateComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "../Game/BaseState.h"
#include "StateManager.h"
#include "ColliderComponent.h"

StateComponent::StateComponent()noexcept
	:BaseComponent()
	, m_Velocity{0,0}
	, m_CurrentMoveStateX{ Fried::StateManager::GetInstance()->GetMoveStateX("MoveStateXIdle") }
	, m_pIdleMoveStateY{ new MoveStateYIdle{} }
	, m_CurrentMoveStateY{ m_pIdleMoveStateY }
	, m_CurrentLifeState{ nullptr }
	, m_DidMoveStateXChange{ false }
	, m_DidMoveStateYChange{ false }
	, m_DidLifeStateChange{ false }
	, m_JumpVelocity{0}
{ 
	SetComponentName(ComponentName::state);
}

StateComponent::~StateComponent()
{
	// need the idle Y state because otherwise it would do it for every one of my enemies
	SafeDelete(m_pIdleMoveStateY);
}

void StateComponent::Update(float elapsedSec)
{
	// check something with the weapon state and if it's shooting if it is make a new game object with a bubble
	m_CurrentMoveStateX->Update(elapsedSec, m_Velocity.x);
	const bool IsOnGround{ GetGameObject()->GetComponent<ColliderComponent>(ComponentName::collider)->HasTrigger(ColliderTrigger::Bottom)};
	const bool isIdle{ m_CurrentMoveStateY == m_pIdleMoveStateY };

	if (m_CurrentLifeState == Fried::StateManager::GetInstance()->GetLifeState("DeathState"))
	{
		return;
	}
	if (IsOnGround) // it's jumping here
	{
		if (!isIdle)
		{
			m_CurrentMoveStateY->Update(elapsedSec, m_JumpVelocity);
		}
	}   
	else if (!IsOnGround && isIdle)
	{
		m_CurrentMoveStateY->Update(elapsedSec, m_JumpVelocity);
		const float terminalVelocity{ 90 * 2.f};
		if (m_JumpVelocity > terminalVelocity)
		{
			m_JumpVelocity = terminalVelocity;
		}
	}
	m_Velocity.y = m_JumpVelocity * elapsedSec;
	SetMoveStateY(m_pIdleMoveStateY);
	GetGameObject()->GetTransform()->Move(m_Velocity);
}

void StateComponent::SetMoveStateX(MoveStateX* pState) noexcept(false)
{
#ifdef _DEBUG
	if (pState == nullptr)
		throw std::runtime_error(std::string("StateComponent::SetCurrentState pState was a nullptr"));
#endif // _DEBUG
	m_DidMoveStateXChange = m_CurrentMoveStateX != pState;
	if (m_DidMoveStateXChange)
	{
		m_CurrentMoveStateX = pState;
	}
}

void StateComponent::SetMoveStateY(MoveStateY* pState) noexcept(false)
{
#ifdef _DEBUG
	if (pState == nullptr)
		throw std::runtime_error(std::string("StateComponent::SetCurrentState pState was a nullptr"));
#endif // _DEBUG
	m_DidMoveStateYChange = m_CurrentMoveStateY != pState;
	if (m_DidMoveStateYChange)
	{
		m_CurrentMoveStateY = pState;
	}
}

void StateComponent::SetLifeState(LifeState* pState) noexcept(false)
{
#ifdef _DEBUG
	if (pState == nullptr)
		throw std::runtime_error(std::string("StateComponent::SetCurrentState pState was a nullptr"));
#endif // _DEBUG
	m_DidLifeStateChange = m_CurrentLifeState != pState;
	if (m_DidLifeStateChange)
	{
		m_CurrentLifeState = pState;
	}
}

void StateComponent::SetWeaponState(WeaponState* pState) noexcept(false)
{
#ifdef _DEBUG
	if (pState == nullptr)
		throw std::runtime_error(std::string("StateComponent::SetCurrentState pState was a nullptr"));
#endif // _DEBUG
	if (m_CurrentWeaponState != pState)
	{
		m_CurrentWeaponState = pState;
	}
}

void StateComponent::SetVelocity(const Fried::float2& vel)
{
	m_Velocity = vel;
}