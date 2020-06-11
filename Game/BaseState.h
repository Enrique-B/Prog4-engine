#pragma once
#include <string>
#include "Structs.h"

class GameObject;
class BaseState
{
public: 
	const std::string& GetName()const noexcept { return m_Name; };
	virtual ~BaseState() = default;
protected: 
	void SetName(const std::string& name)noexcept { m_Name = name; };
private: 
	std::string m_Name;
};

class LifeState : public BaseState // life, death, invincable(after death)
{
public:
	virtual ~LifeState() = default;
	virtual void Update(float elapsedSec, float& velocity) = 0;
};

class DeathState : public LifeState // life, death, invincable(after death)
{
public:
	DeathState();

	virtual ~DeathState() = default;
	virtual void Update(float elapsedSec, float& velocity)override;
};

class AliveState : public LifeState // life, death, invincable(after death)
{
public:
	AliveState();

	virtual ~AliveState() = default;
	virtual void Update(float elapsedSec, float& velocity)override;
};


class InvincibleState : public LifeState // life, death, invincable(after death)
{
public:
	InvincibleState();
	virtual ~InvincibleState() = default;
	virtual void Update(float elapsedSec, float& velocity)override;
};


class MoveStateX : public BaseState // left, right
{
public:
	MoveStateX();
	virtual ~MoveStateX() = default;
	virtual void Update(float, float& velocity) = 0;
protected:
	float m_MovementSpeed;
};

class MoveStateRight final: public MoveStateX
{
public:	
	MoveStateRight();
	virtual ~MoveStateRight() = default;

	void Update(float elapsedSec, float& velocity);
};

class MoveStateLeft final : public MoveStateX
{
public:
	MoveStateLeft();
	virtual ~MoveStateLeft() = default;

	void Update(float elapsedSec, float& velocity);
};

class MoveStateXIdle final : public MoveStateX
{
public:
	MoveStateXIdle();
	virtual ~MoveStateXIdle() = default;

	void Update(float elapsedSec, float& velocity);
};

class MoveStateY : public BaseState // jump, falling, idle 
{
public:
	virtual ~MoveStateY() = default;

	virtual void Update(float elapsedSec, float& velocity) = 0;
};

class JumpState final : public MoveStateY
{
public:
	JumpState();
	virtual ~JumpState() = default;

	void Update(float elapsedSec, float& velocity);
private: 
	float m_JumpSpeed;
};

class MoveStateYIdle final : public MoveStateY
{
public:
	MoveStateYIdle();
	virtual ~MoveStateYIdle() = default;
	void Update(float elapsedSec, float& velocity);
private: 
	const float m_Gravity;
};

class MoveStateYNone final : public MoveStateY
{
public:
	MoveStateYNone();
	virtual ~MoveStateYNone() = default;
	void Update(float, float& velocity);
private:
};

