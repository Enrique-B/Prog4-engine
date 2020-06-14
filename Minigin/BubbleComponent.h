#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "EnemyComponent.h"

class BubbleComponent final: public BaseComponent
{
public: 
	BubbleComponent(bool m_IsGoingRight); 
	BubbleComponent(const BubbleComponent& other) = delete;
	BubbleComponent(BubbleComponent&& other) = delete;
	BubbleComponent& operator=(const BubbleComponent& other) = delete;
	BubbleComponent& operator=(BubbleComponent&& other) = delete;
	~BubbleComponent() = default;

	virtual void Update(float elapsedSec) override;
	virtual void Initialize()override; 
	void SetGoingRight(bool isGoingRight) { m_IsGoingRight = isGoingRight; }
	void SetHasHitEnemy(bool ishit) { m_IsHitByEnemy = ishit; }
	void SetEnemyType(unsigned char enemyType) { m_EnemyType = enemyType; };
	bool IsHitByEnemy()const noexcept { return m_IsHitByEnemy; }
	bool HasReachedPos()const noexcept { return m_HasReachedPos; }
private: 
	Fried::float2 m_NextPos; 
	bool m_HasReachedPos; 
	bool m_IsGoingRight;
	bool m_IsHitByEnemy; 
	bool m_IsHitByPlayer;
	unsigned char m_EnemyType; 
	float m_TimeAllive;
};