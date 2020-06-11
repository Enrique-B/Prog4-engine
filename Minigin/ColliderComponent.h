#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <atomic>
// add them on 
enum ColliderTrigger : UINT32
{
	None = 0,
	left = (1 << 0),
	right = (1 << 1),
	Top = (1 << 2),
	Bottom = (1 << 3),
	Teleport = (1 << 4),
	EnemyHit = (1 << 5),
	PlayerHit = (1 << 6)
};

struct CollisionLine
{
	CollisionLine(const Fried::line& l, ColliderTrigger col) :line{ l }, collision{ col }{}
	Fried::line line;
	ColliderTrigger collision;
};

class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(const SDL_Rect& collisionRect, bool isStatic);
	void AddLines();
	bool GetIsStatic()const;

	virtual void Initialize()noexcept override;
	virtual void Update(float elapsedSec)override;
	virtual void RenderCollision()const noexcept override;
	const std::vector<CollisionLine>& GetLines()const noexcept { return m_Lines; };
	const SDL_Rect& GetCollisionRect()const noexcept { return m_ColissionRect; };
	void SetTrigger(ColliderTrigger trigger) noexcept;
	bool HasTrigger(ColliderTrigger trigger)const noexcept;
	Fried::float2 GetMiddlePoint()const { return m_IsStatic ? Fried::float2() : m_Lines[0].line.p1; };
private: 
	SDL_Rect m_ColissionRect;
	const bool m_IsStatic;
	std::vector<CollisionLine> m_Lines;
	std::atomic<ColliderTrigger> m_Trigger;
};

