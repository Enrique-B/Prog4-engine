#pragma once
#include "BaseComponent.h"
#include "Structs.h"

class BubbleComponent : public BaseComponent
{
public: 
	BubbleComponent(bool m_IsGoingRight); 
	~BubbleComponent();
	virtual void Update(float elapsedSec) override;
	virtual void Initialize()override; 
	bool SetGoingRight(bool isGoingRight) { m_IsGoingRight = isGoingRight; }
	bool SetHasHitEnemy(bool ishit) { m_IsHitByEnemy = ishit; }
private: 
	Fried::float2 m_NextPos; 
	bool m_HasReachedPos; 
	bool m_IsGoingRight;
	bool m_IsHitByEnemy; 
};

