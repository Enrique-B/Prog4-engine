#pragma once
#include "BaseComponent.h"
class ColliderComponent;
class StateComponent;

class EnemyComponent final: public BaseComponent
{
public: 
	EnemyComponent(unsigned char enemyType, const float amountOfSecIdle, bool islookingleft)noexcept;
	EnemyComponent(const EnemyComponent& other) = delete;
	EnemyComponent(EnemyComponent&& other) = delete;
	EnemyComponent& operator=(const EnemyComponent& other) = delete;
	EnemyComponent& operator=(EnemyComponent&& other) = delete;
	~EnemyComponent() = default;

	virtual void Update(float elapsedSec) override;
	virtual void Initialize()override;
	unsigned char GetEnemyType()const noexcept { return m_EnemyType; }
private: 
	unsigned char m_EnemyType;
	const float m_AmountOfSecIdle;
	float m_AmountOfSecAlive;
	float m_TimeForNextCollisionCheck; 
	bool m_IsLookingRight;
	bool m_IsRaycasting; 
	bool m_IsLastStateJump; 
	short m_AmountOfRaycast; 

	// storing the variables so i don't have to do GetGameObject()->GetComponent<ColliderComponent>(ComponentName::collider)
	ColliderComponent* m_pColliderComp;
	StateComponent* m_pStateComp;
};

