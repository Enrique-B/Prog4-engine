#include "MiniginPCH.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent()
	:BaseComponent()
	,m_Position{0,0}
{
	SetComponentName(ComponentName::TransFrom);
}

void TransformComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void TransformComponent::Render(const Fried::float2& pos) const
{
	UNREFERENCED_PARAMETER(pos);
}

void TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
}
