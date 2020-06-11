#include "BaseState.h"
#include "MiniginPCH.h"
#include <iostream>

DeathState::DeathState()
	:LifeState{}
{
	SetName("DeathState");
}

void DeathState::Update(float elapsedSec, float& velocity)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	velocity = 0;
}

AliveState::AliveState()
{
	SetName("AliveState");
}

void AliveState::Update(float, float&)
{}

MoveStateX::MoveStateX()
	:BaseState(), m_MovementSpeed{100} {}

MoveStateRight::MoveStateRight()
	: MoveStateX()
{
	SetName("MoveRightState");
}

void MoveStateRight::Update(float elapsedSec, float& velocity)
{
	velocity = m_MovementSpeed * elapsedSec;
}

MoveStateLeft::MoveStateLeft()
	: MoveStateX()
{
	SetName("MoveLeftState");
}

void MoveStateLeft::Update(float elapsedSec, float& velocity)
{
	velocity = -m_MovementSpeed * elapsedSec;
}

MoveStateXIdle::MoveStateXIdle()
	:MoveStateX()
{
	SetName("MoveStateXIdle");
}

void MoveStateXIdle::Update(float, float& velocity)
{
	velocity = 0;
}

MoveStateYIdle::MoveStateYIdle()
	:MoveStateY(), m_Gravity{ 98.1f * 2.f }
{	
	SetName("MoveStateYIdle");
}

void MoveStateYIdle::Update(float elapsedSec, float& velocity)
{
	// need to find a way to reset the velocity of this one 
	velocity += m_Gravity * elapsedSec;
}

JumpState::JumpState()
	:MoveStateY(), m_JumpSpeed{ 160 * 1.35f}
{ 
	SetName("JumpState");
}

void JumpState::Update(float, float& velocity)
{
	velocity = -m_JumpSpeed;
}

MoveStateYNone::MoveStateYNone()
{
	SetName("MoveStateYNone");
}
void MoveStateYNone::Update(float, float& velocity)
{
	velocity = 0; 
}

InvincibleState::InvincibleState()
{
	SetName("InvincibleState");
}

void InvincibleState::Update(float , float& )
{
}
