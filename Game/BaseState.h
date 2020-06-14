#pragma once
#include <string>
#include "Structs.h"

class GameObject;
class BaseState
{
public: 
	BaseState() = default; 
	BaseState(const BaseState& other) = delete;
	BaseState(BaseState&& other) = delete;
	BaseState& operator=(const BaseState& other) = delete;
	BaseState& operator=(BaseState&& other) = delete;
	virtual ~BaseState() = default;

	const std::string& GetName()const noexcept { return m_Name; };
protected: 
	void SetName(const std::string& name)noexcept { m_Name = name; };
private: 
	std::string m_Name;
};

class LifeState : public BaseState // life, death, invincable(after death)
{
public:
	LifeState() = default;
	LifeState(const LifeState& other) = delete;
	LifeState(LifeState&& other) = delete;
	LifeState& operator=(const LifeState& other) = delete;
	LifeState& operator=(LifeState&& other) = delete;
	virtual ~LifeState() = default;

	virtual void Update(float elapsedSec, float& velocity) = 0;
};

class DeathState : public LifeState // life, death, invincable(after death)
{
public:
	DeathState();
	DeathState(const DeathState& other) = delete;
	DeathState(DeathState&& other) = delete;
	DeathState& operator=(const DeathState& other) = delete;
	DeathState& operator=(DeathState&& other) = delete;
	virtual ~DeathState() = default;
	virtual void Update(float elapsedSec, float& velocity)override;
};

class AliveState : public LifeState // life, death, invincable(after death)
{
public:
	AliveState();
	AliveState(const AliveState& other) = delete;
	AliveState(AliveState&& other) = delete;
	AliveState& operator=(const AliveState& other) = delete;
	AliveState& operator=(AliveState&& other) = delete;
	virtual ~AliveState() = default;

	virtual void Update(float elapsedSec, float& velocity)override;
};

class InvincibleState : public LifeState // life, death, invincable(after death)
{
public:
	InvincibleState();
	InvincibleState(const InvincibleState& other) = delete;
	InvincibleState(InvincibleState&& other) = delete;
	InvincibleState& operator=(const InvincibleState& other) = delete;
	InvincibleState& operator=(InvincibleState&& other) = delete;
	virtual ~InvincibleState() = default;

	virtual void Update(float elapsedSec, float& velocity)override;
};

class MoveStateX : public BaseState // left, right
{
public:
	MoveStateX();
	MoveStateX(const MoveStateX& other) = delete;
	MoveStateX(MoveStateX&& other) = delete;
	MoveStateX& operator=(const MoveStateX& other) = delete;
	MoveStateX& operator=(MoveStateX&& other) = delete;
	virtual ~MoveStateX() = default;

	virtual void Update(float, float& velocity) = 0;
protected:
	float m_MovementSpeed;
};

class MoveStateRight final: public MoveStateX
{
public:	
	MoveStateRight();
	MoveStateRight(const MoveStateRight& other) = delete;
	MoveStateRight(MoveStateRight&& other) = delete;
	MoveStateRight& operator=(const MoveStateRight& other) = delete;
	MoveStateRight& operator=(MoveStateRight&& other) = delete;
	virtual ~MoveStateRight() = default;
	void Update(float elapsedSec, float& velocity);

};

class MoveStateRightFast final : public MoveStateX
{
public:
	MoveStateRightFast();
	MoveStateRightFast(const MoveStateRightFast& other) = delete;
	MoveStateRightFast(MoveStateRightFast&& other) = delete;
	MoveStateRightFast& operator=(const MoveStateRightFast& other) = delete;
	MoveStateRightFast& operator=(MoveStateRightFast&& other) = delete;
	virtual ~MoveStateRightFast() = default;
	void Update(float elapsedSec, float& velocity);
};

class MoveStateLeft final : public MoveStateX
{
public:
	MoveStateLeft();
	MoveStateLeft(const MoveStateLeft& other) = delete;
	MoveStateLeft(MoveStateLeft&& other) = delete;
	MoveStateLeft& operator=(const MoveStateLeft& other) = delete;
	MoveStateLeft& operator=(MoveStateLeft&& other) = delete;
	virtual ~MoveStateLeft() = default;

	void Update(float elapsedSec, float& velocity);
};

class MoveStateLeftFast final : public MoveStateX
{
public:
	MoveStateLeftFast();
	MoveStateLeftFast(const MoveStateLeftFast& other) = delete;
	MoveStateLeftFast(MoveStateLeftFast&& other) = delete;
	MoveStateLeftFast& operator=(const MoveStateLeftFast& other) = delete;
	MoveStateLeftFast& operator=(MoveStateLeftFast&& other) = delete;
	virtual ~MoveStateLeftFast() = default;

	void Update(float elapsedSec, float& velocity);
};

class MoveStateXIdle final : public MoveStateX
{
public:
	MoveStateXIdle();
	MoveStateXIdle(const MoveStateXIdle& other) = delete;
	MoveStateXIdle(MoveStateXIdle&& other) = delete;
	MoveStateXIdle& operator=(const MoveStateXIdle& other) = delete;
	MoveStateXIdle& operator=(MoveStateXIdle&& other) = delete;
	virtual ~MoveStateXIdle() = default;

	void Update(float elapsedSec, float& velocity);
};

class MoveStateY : public BaseState // jump, falling, idle 
{
public:
	MoveStateY() = default;
	MoveStateY(const MoveStateY& other) = delete;
	MoveStateY(MoveStateY&& other) = delete;
	MoveStateY& operator=(const MoveStateY& other) = delete;
	MoveStateY& operator=(MoveStateY&& other) = delete;
	virtual ~MoveStateY() = default;

	virtual void Update(float elapsedSec, float& velocity) = 0;
};

class JumpState final : public MoveStateY
{
public:
	JumpState();
	JumpState(const JumpState& other) = delete;
	JumpState(JumpState&& other) = delete;
	JumpState& operator=(const JumpState& other) = delete;
	JumpState& operator=(JumpState&& other) = delete;
	virtual ~JumpState() = default;
	void Update(float elapsedSec, float& velocity);
private: 
	float m_JumpSpeed;
};

class MoveStateYIdle final : public MoveStateY
{
public:
	MoveStateYIdle();
	MoveStateYIdle(const MoveStateYIdle& other) = delete;
	MoveStateYIdle(MoveStateYIdle&& other) = delete;
	MoveStateYIdle& operator=(const MoveStateYIdle& other) = delete;
	MoveStateYIdle& operator=(MoveStateYIdle&& other) = delete;
	virtual ~MoveStateYIdle() = default;

	void Update(float elapsedSec, float& velocity);
private: 
	const float m_Gravity;
};

class MoveStateYNone final : public MoveStateY
{
public:
	MoveStateYNone();
	MoveStateYNone(const MoveStateYNone& other) = delete;
	MoveStateYNone(MoveStateYNone&& other) = delete;
	MoveStateYNone& operator=(const MoveStateYNone& other) = delete;
	MoveStateYNone& operator=(MoveStateYNone&& other) = delete;
	virtual ~MoveStateYNone() = default;

	void Update(float, float& velocity);
private:
};

class WeaponState : public BaseState 
{
public:
	WeaponState() = default;
	WeaponState(const WeaponState& other) = delete;
	WeaponState(WeaponState&& other) = delete;
	WeaponState& operator=(const WeaponState& other) = delete;
	WeaponState& operator=(WeaponState&& other) = delete;
	virtual ~WeaponState() = default;
	virtual void Update(float elapsedSec, float& velocity) = 0;
};

class WeaponStateNone : public WeaponState
{
public: 
	WeaponStateNone();
	WeaponStateNone(const WeaponStateNone& other) = delete;
	WeaponStateNone(WeaponStateNone&& other) = delete;
	WeaponStateNone& operator=(const WeaponStateNone& other) = delete;
	WeaponStateNone& operator=(WeaponStateNone&& other) = delete;
	virtual ~WeaponStateNone() = default;
	void Update(float, float&) {};
};

class WeaponStateShootBubble : public WeaponState
{
public:
	WeaponStateShootBubble();
	WeaponStateShootBubble(const WeaponStateShootBubble& other) = delete;
	WeaponStateShootBubble(WeaponStateShootBubble&& other) = delete;
	WeaponStateShootBubble& operator=(const WeaponStateShootBubble& other) = delete;
	WeaponStateShootBubble& operator=(WeaponStateShootBubble&& other) = delete;
	virtual ~WeaponStateShootBubble() = default;
	void Update(float, float&) {};
};