#pragma once
#include "BaseComponent.h"
class CharacterComponent : public BaseComponent
{
public: 
	CharacterComponent(); 
	~CharacterComponent();
	virtual void Update(float elapsedSec)noexcept override;
	bool IsDead()const noexcept { return m_IsDead; }
private: 
	bool m_IsDead;
	bool m_IsInvincable; 
	float m_AmountOfSecBeforeReset; 
	float m_AmountOfSecOfInvincability;
	int m_AmountOfLives;
	void Reset();
};