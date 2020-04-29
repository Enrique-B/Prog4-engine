#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

ColliderComponent::ColliderComponent(const SDL_Rect& collisionRect, bool isStatic)
	:m_ColissionRect{collisionRect}
	, m_IsStatic{isStatic}
{
	SetComponentName(ComponentName::collider);
}

bool ColliderComponent::GetIsStatic() const
{
	return m_IsStatic;
}

void ColliderComponent::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
	if (m_IsStatic)
		return;
	TransformComponent* pTransform = GetGameObject()->GetComponent<TransformComponent>(ComponentName::TransFrom);
	const Fried::float2 pos = pTransform->GetPosition();
	m_ColissionRect.x = static_cast<int>(pos.x);
	m_ColissionRect.y = static_cast<int>(pos.y);
	const size_t size{ m_Lines.size() };
	for (size_t i = 0; i < size; i++)
	{
		m_Lines[i].UpdateLine(Fried::float2{ m_ColissionRect.x + m_ColissionRect.w / 2.f, m_ColissionRect.y + m_ColissionRect.h / 2.f });
	}
}

void ColliderComponent::RenderCollision() const
{
	Fried::Renderer* pRenderer = Fried::Renderer::GetInstance();
	pRenderer->RenderRect(m_ColissionRect);
	const size_t size{ m_Lines.size() };
	for (size_t i = 0; i < size; i++)
	{
		pRenderer->RenderLine(m_Lines[i]);
	}
}

// lines start from the middle of the rect 
void ColliderComponent::AddLines(const Fried::float2& point)
{
	const Fried::line line{m_ColissionRect.x + m_ColissionRect.w/2.f, m_ColissionRect.y + m_ColissionRect.h/2.f, m_ColissionRect.x + m_ColissionRect.w / 2.f + point.x, m_ColissionRect.y + m_ColissionRect.h / 2.f + point.y};
	m_Lines.push_back(line);
}
