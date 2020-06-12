#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "EnemyComponent.h"

class BubbleComponent : public BaseComponent
{
public: 
	BubbleComponent(bool m_IsGoingRight); 
	~BubbleComponent();
	virtual void Update(float elapsedSec) override;
	virtual void Initialize()override; 
	void SetGoingRight(bool isGoingRight) { m_IsGoingRight = isGoingRight; }
	void SetHasHitEnemy(bool ishit) { m_IsHitByEnemy = ishit; }
	void SetEnemyType(unsigned char enemyType) { m_EnemyType = enemyType; };
	bool IsHitByEnemy()const noexcept { return m_IsHitByEnemy; }
private: 
	Fried::float2 m_NextPos; 
	bool m_HasReachedPos; 
	bool m_IsGoingRight;
	bool m_IsHitByEnemy; 
	unsigned char m_EnemyType; 
};

