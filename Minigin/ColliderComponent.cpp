#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Scene.h"

ColliderComponent::ColliderComponent(const SDL_Rect& collisionRect, bool isStatic)
	:m_ColissionRect{collisionRect}
	, m_IsStatic{isStatic}
{
	SetComponentName(ComponentName::collider);
	if (!m_IsStatic)
		AddLines();
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
	// don't make it update every frame because this is bad atm 

	TransformComponent* pTransform = GetGameObject()->GetComponent<TransformComponent>(ComponentName::TransFrom);
	const Fried::float2 pos = pTransform->GetPosition();
	m_ColissionRect.x = int(pos.x);
	m_ColissionRect.y = int(pos.y);
	const size_t size{ m_Lines.size() };
	Fried::float2 point{ m_ColissionRect.x + m_ColissionRect.w / 2.f, m_ColissionRect.y + m_ColissionRect.h / 2.f };
	for (size_t i = 0; i < size; i++)
	{
		m_Lines[i].line.UpdateLine(point);
	}
}

void ColliderComponent::RenderCollision() const noexcept
{
	Fried::Renderer* pRenderer = Fried::Renderer::GetInstance();
	pRenderer->RenderRect(m_ColissionRect);
	const size_t size{ m_Lines.size() };
	for (size_t i = 0; i < size; i++)
	{
		pRenderer->RenderLine(m_Lines[i].line);
	}
}

void ColliderComponent::SetTrigger(ColliderTrigger trigger) noexcept
{
	ColliderTrigger temp{ m_Trigger.load() };
	if (trigger == ColliderTrigger::None) // resetting the trigger
	{
		ColliderTrigger noneTrigger{ ColliderTrigger::None };
		if (HasTrigger(ColliderTrigger::Teleport))
		{
			noneTrigger = ColliderTrigger(temp | trigger);
		}
		while (!m_Trigger.compare_exchange_weak(temp, noneTrigger)) {}
		return;
	}
	ColliderTrigger expected = ColliderTrigger(temp | trigger);
	while (!m_Trigger.compare_exchange_weak(temp, expected)) {}
}

bool ColliderComponent::HasTrigger(ColliderTrigger trigger) const noexcept
{
	return m_Trigger.load() & trigger;
}

// lines start from the middle of the rect 
void ColliderComponent::AddLines()
{
	const float height2{ m_ColissionRect.h / 2.f };
	const float widht2{ m_ColissionRect.w / 2.f };
	Fried::float2 middlePoint{ m_ColissionRect.x + widht2, m_ColissionRect.y + height2 };
	// first for loop
	Fried::line line{ middlePoint.x, middlePoint.y, middlePoint.x - widht2 - 1, middlePoint.y }; // right
	m_Lines.push_back(CollisionLine(line, ColliderTrigger::left));
	line = Fried::line{ middlePoint.x, middlePoint.y, middlePoint.x + widht2 + 1, middlePoint.y }; // left
	m_Lines.push_back(CollisionLine(line, ColliderTrigger::right));
	line = Fried::line{ middlePoint.x, middlePoint.y,middlePoint.x , middlePoint.y + height2 }; // bottom
	m_Lines.push_back(CollisionLine(line, ColliderTrigger::Bottom));

	line = Fried::line{ middlePoint.x, middlePoint.y,float(m_ColissionRect.x + 2 ) , middlePoint.y + height2 }; // bottom
	m_Lines.push_back(CollisionLine(line, ColliderTrigger(ColliderTrigger::Bottom)));
	line = Fried::line{ middlePoint.x, middlePoint.y,float(m_ColissionRect.x + m_ColissionRect.w - 2) , middlePoint.y + height2}; // bottom
	m_Lines.push_back(CollisionLine(line, ColliderTrigger(ColliderTrigger::Bottom)));
}

void ColliderComponent::Initialize()noexcept
{
	GetGameObject()->GetScene()->AddCollider(this);
}
