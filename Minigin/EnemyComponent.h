#pragma once
#include "BaseComponent.h"
class EnemyComponent : public BaseComponent
{
public: 
	EnemyComponent(unsigned char enemyType, const float amountOfSecIdle)noexcept;

private: 
	unsigned char m_EnemyTypel;
	float m_AmountOfSecIdle;
};

