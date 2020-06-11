#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "StateManager.h"
#include "SpriteComponent.h"

CharacterComponent::CharacterComponent()
	: m_IsDead{false}
	, m_IsInvincable{false}
	, m_AmountOfSecBeforeReset{2}
	, m_AmountOfSecOfInvincability{3}
	, m_AmountOfLives{3}
{
	SetComponentName(ComponentName::Character);
}

CharacterComponent::~CharacterComponent()
{
}

void CharacterComponent::Update(float elapsedSec) noexcept
{
	UNREFERENCED_PARAMETER(elapsedSec);
	if (m_IsDead)
	{
		StateComponent* pState = GetGameObject()->GetComponent<StateComponent>(ComponentName::state);
		Fried::StateManager* pStateManager = Fried::StateManager::StateManager::GetInstance();
			// set the death state here 
		pState->SetLifeState(pStateManager->GetLifeState("DeathState"));
			// Set the not move state here 
		pState->SetMoveStateX(pStateManager->GetMoveStateX("MoveStateXIdle"));
		SpriteComponent* pSprite = GetGameObject()->GetComponent<SpriteComponent>(ComponentName::Sprite);
		pSprite->SetUpdate(true);
		pSprite->SetMaxedFrames(4);

		m_AmountOfSecBeforeReset -= elapsedSec; 
		if (m_AmountOfSecBeforeReset <= 0)
		{
			// insert random number for reset 
			m_AmountOfSecBeforeReset = 2; 
			m_IsDead = false;
			--m_AmountOfLives;
			if (m_AmountOfLives >= 0)
			{
				Reset();
			}
		}
	}
	else if(m_IsInvincable)
	{
		m_AmountOfSecOfInvincability -= elapsedSec; 
		if (m_AmountOfSecOfInvincability < 0)
		{
			m_AmountOfSecOfInvincability = 3;
			m_IsInvincable = false;
			StateComponent* pState = GetGameObject()->GetComponent<StateComponent>(ComponentName::state);
			Fried::StateManager* pStateManager = Fried::StateManager::StateManager::GetInstance();
			pState->SetLifeState(pStateManager->GetLifeState("AliveState"));
		}
	}
	else
	{
		// set living state here 
		ColliderComponent* pCollider = GetGameObject()->GetComponent<ColliderComponent>(ComponentName::collider);
		if (pCollider->HasTrigger(ColliderTrigger::PlayerHit))
		{
			// set the death state here 
			// Set the not move state here 
			m_IsDead = true;
			pCollider->SetTrigger(ColliderTrigger::None);
			SpriteComponent* pSprite = GetGameObject()->GetComponent<SpriteComponent>(ComponentName::Sprite);
			pSprite->SetMaxedFrames(4);
			pSprite->SetDestRectHeight(16);
			pSprite->SetUpdate(true);
		}
	}
}

void CharacterComponent::Reset()
{
	// give position here 
	const int spriteWidth{ 16 };
	GetGameObject()->GetTransform()->SetPosition(spriteWidth * 3, spriteWidth * 33 + 40);
	StateComponent* pState = GetGameObject()->GetComponent<StateComponent>(ComponentName::state);
	Fried::StateManager* pStateManager = Fried::StateManager::StateManager::GetInstance();
	pState->SetLifeState(pStateManager->GetLifeState("InvincibleState"));
	pState->SetMoveStateY(pStateManager->GetMoveStateY("MoveStateYIdle"));
	m_IsInvincable = true;
	SpriteComponent* pSprite = GetGameObject()->GetComponent<SpriteComponent>(ComponentName::Sprite);
	pSprite->SetMaxedFrames(4);
	pSprite->SetDestRectHeight(0);
	pSprite->SetUpdate(true);
}