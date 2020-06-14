#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"

TransformComponent::TransformComponent()noexcept
	:BaseComponent()
	,m_Position{0,0}
	, m_ResetPosition{0,0}
{
	SetComponentName(ComponentName::TransFrom);
}

void TransformComponent::Initialize() noexcept
{
	m_Position = m_ResetPosition;
}

void TransformComponent::SetResetPosition(const Fried::float2& pos) noexcept
{
	m_ResetPosition = pos;
}

void TransformComponent::SetPosition(const float x, const float y)noexcept
{
	m_Position.x = x;
	m_Position.y = y;
}

void TransformComponent::SetPosition(const Fried::float2& pos)noexcept
{
	m_Position = pos;
}

void TransformComponent::Move(float x, float y)noexcept
{
	m_Position.x += x;
	m_Position.y += y;
}

void TransformComponent::Move(const Fried::float2& velocity)noexcept
{
	m_Position += velocity;
}

