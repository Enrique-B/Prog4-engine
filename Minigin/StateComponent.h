#pragma once
#include <vector>
#include "BaseComponent.h"
class MoveStateX;
class LifeState;
class MoveStateY;
class WeaponState;
class StateComponent final : public BaseComponent
{
public: 
	StateComponent()noexcept;
	StateComponent(const StateComponent& other) = delete;
	StateComponent(StateComponent&& other) = delete;
	StateComponent& operator=(const StateComponent& other) = delete;
	StateComponent& operator=(StateComponent&& other) = delete;
	~StateComponent()noexcept;
	virtual void Initialize()noexcept(false) override;
	virtual void Update(float elapsedSec)noexcept(false)override;
	
	const Fried::float2& GetVelicity()const noexcept { return m_Velocity; };
	void SetVelocity(const Fried::float2& vel);
	void SetMoveStateX(MoveStateX* pState)noexcept(false);
	void SetMoveStateY(MoveStateY* pState)noexcept(false);
	void SetLifeState(LifeState* pState)noexcept(false);
	void SetWeaponState(WeaponState* pState)noexcept(false);

	MoveStateX* GetMoveStateX()const noexcept { return m_CurrentMoveStateX; }
	MoveStateY* GetMoveStateY()const noexcept { return m_CurrentMoveStateY; }
	LifeState* GetLifeState()const noexcept { return m_CurrentLifeState; }
	WeaponState* GetWeaponState()const noexcept { return m_CurrentWeaponState; }
private:
	Fried::float2 m_Velocity; 
	MoveStateX* m_CurrentMoveStateX;
	MoveStateY* m_pIdleMoveStateY;
	MoveStateY* m_CurrentMoveStateY;
	LifeState* m_CurrentLifeState;
	WeaponState* m_CurrentWeaponState;
	bool m_DidMoveStateXChange;
	bool m_DidMoveStateYChange;
	bool m_DidLifeStateChange;
	float m_JumpVelocity;
};

