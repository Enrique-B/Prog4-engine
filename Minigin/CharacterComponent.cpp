#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "StateManager.h"
#include "SpriteComponent.h"
#include "BubbleComponent.h"

CharacterComponent::CharacterComponent(unsigned int characterNumber)
	: m_IsDead{false}
	, m_IsInvincable{false}
	, m_AmountOfSecBeforeReset{2}
	, m_AmountOfSecOfInvincability{3}
	, m_AmountOfLives{3}
	, m_CharacterNumber{ characterNumber }
{
	SetComponentName(ComponentName::Character);
}

void CharacterComponent::Update(float elapsedSec) noexcept
{
	Fried::StateManager* pStateManager = Fried::StateManager::StateManager::GetInstance();
	GameObject* pObject = GetGameObject();
	StateComponent* pState = pObject->GetComponent<StateComponent>(ComponentName::State);
	SpriteComponent* pSprite = pObject->GetComponent<SpriteComponent>(ComponentName::Sprite);

	UNREFERENCED_PARAMETER(elapsedSec);
	if (m_IsDead)
	{
			// set the death state here 
		pState->SetLifeState(pStateManager->GetLifeState("DeathState"));
			// Set the not move state here 
		pState->SetMoveStateX(pStateManager->GetMoveStateX("MoveStateXIdle"));
		pSprite->SetUpdate(true);
		pSprite->SetMaxedFrames(4);
		m_AmountOfSecBeforeReset -= elapsedSec; 
		if (m_AmountOfSecBeforeReset <= 0)
		{
			// insert random number for reset 
			m_AmountOfSecBeforeReset = 2; 
			--m_AmountOfLives;
			if (m_AmountOfLives >= 0)
			{
				Reset();
			}
		}
	}
	else
	{
		if (pState->GetWeaponState() == pStateManager->GetWeaponState("WeaponStateShootBubble") && pSprite->IsAnimationFinished())
		{
			// spauwn bubble
			pSprite->SetFrame(0);
			pSprite->SetDestRectY(0);
			pSprite->Update(true);
			pSprite->SetDestRectY(0);
			// spauwn bubble
			pState->SetWeaponState(pStateManager->GetWeaponState("WeaponStateNone"));
			//MakeBubble();
		}
		ColliderComponent* pCollider = pObject->GetComponent<ColliderComponent>(ComponentName::Collider);
		if (m_IsInvincable)
		{
			m_AmountOfSecOfInvincability -= elapsedSec;
			if (m_AmountOfSecOfInvincability < 0)
			{
				m_AmountOfSecOfInvincability = 3;
				m_IsInvincable = false;
				pState->SetLifeState(pStateManager->GetLifeState("AliveState"));
			}
		}
		// set dying state here 
		else if (pCollider->HasTrigger(ColliderTrigger::Player))
		{
			// set the death state here 
			// Set the not move state here 
			m_IsDead = true;
			pCollider->SetTrigger(ColliderTrigger::None);
			pSprite->SetMaxedFrames(4);
			pSprite->SetDestRectY(16);
			pSprite->SetUpdate(true);
		}
	}
}

void CharacterComponent::Reset()
{
	// give position here 
	const int spriteWidth{ 16 };
	TransformComponent* pTransform = GetGameObject()->GetTransform();
	pTransform->SetPosition(pTransform->GetResetPosition());
	StateComponent* pState = GetGameObject()->GetComponent<StateComponent>(ComponentName::State);
	Fried::StateManager* pStateManager = Fried::StateManager::StateManager::GetInstance();
	pState->SetLifeState(pStateManager->GetLifeState("InvincibleState"));
	pState->SetMoveStateY(pStateManager->GetMoveStateY("MoveStateYIdle"));
	m_IsInvincable = true;
	SpriteComponent* pSprite = GetGameObject()->GetComponent<SpriteComponent>(ComponentName::Sprite);
	pSprite->SetMaxedFrames(4);
	pSprite->SetDestRectY(0);
	pSprite->SetUpdate(true);
	m_IsDead = false;
}
