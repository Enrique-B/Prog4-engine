#pragma once
#include "BaseComponent.h"
class CharacterComponent final: public BaseComponent
{
public: 
	CharacterComponent(unsigned int characterNumber);
	CharacterComponent(const CharacterComponent& other) = delete;
	CharacterComponent(CharacterComponent&& other) = delete;
	CharacterComponent& operator=(const CharacterComponent& other) = delete;
	CharacterComponent& operator=(CharacterComponent&& other) = delete;
	~CharacterComponent() = default;
	virtual void Initialize()noexcept override;
	unsigned int GetCharacterNumber()const noexcept { return m_CharacterNumber; }
	virtual void Update(float elapsedSec)noexcept override;
	bool IsDead()const noexcept { return m_IsDead; }
	int GetAmountOfLives()const noexcept { return m_AmountOfLives; }
	void SetAmountOfLives(unsigned int amountOfLives)noexcept { m_AmountOfLives = amountOfLives; }
private: 
	bool m_IsDead;
	bool m_IsInvincable; 
	float m_AmountOfSecBeforeReset; 
	float m_AmountOfSecOfInvincability;
	int m_AmountOfLives;
	unsigned int m_CharacterNumber;
	void Reset();
};