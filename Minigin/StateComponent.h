#pragma once
#include <vector>
#include "BaseComponent.h"
class MoveStateX;
class LifeState;
class MoveStateY;
class StateComponent final : public BaseComponent
{
public: 
	StateComponent()noexcept;
	~StateComponent()noexcept;
	virtual void Update(float elapsedSec)override;
	void SetMoveStateX(MoveStateX* pState)noexcept(false);
	void SetMoveStateY(MoveStateY* pState)noexcept(false);
	void SetLifeState(LifeState* pState)noexcept(false);
	const Fried::float2& GetVelicity()const { return m_Velocity; };
	void SetVelocity(const Fried::float2& vel);
private:
	Fried::float2 m_Velocity; 
	MoveStateX* m_CurrentMoveStateX;
	MoveStateY* m_pIdleMoveStateY;
	MoveStateY* m_CurrentMoveStateY;
	LifeState* m_CurrentLifeState;
	bool m_DidMoveStateXChange;
	bool m_DidMoveStateYChange;
	bool m_DidLifeStateChange;
	float m_JumpVelocity;
};

