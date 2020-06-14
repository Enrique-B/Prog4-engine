#pragma once
#include "BaseComponent.h"
class ItemComponent final : public BaseComponent
{
public:
	explicit ItemComponent(unsigned char enemyType)noexcept;
	ItemComponent(const ItemComponent& other) = delete;
	ItemComponent(ItemComponent&& other) = delete;
	ItemComponent& operator=(const ItemComponent& other) = delete;
	ItemComponent& operator=(ItemComponent&& other) = delete;
	~ItemComponent() = default;
	virtual void Update(float )override;
	virtual void Initialize() override;
	unsigned char GetEnemyType() const noexcept{ return m_EnemyType;  };
	void AddCharacterNumber(unsigned int characterNumber) { m_CharacterNumber = characterNumber; };
public: 
	unsigned char m_EnemyType;
	unsigned int m_CharacterNumber;
};

