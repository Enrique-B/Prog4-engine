#pragma once
#include "BaseComponent.h"
#include "Structs.h"
// add them on 
enum class ColliderTrigger
{
	None,
	Side,
	Top,
	Bottom,
	Teleport // used for the blocks that are on top and bottom
};


class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(const SDL_Rect& collisionRect, bool isStatic);
	void AddLines(const Fried::float2& point);
	bool GetIsStatic()const;

	virtual void Initialize()noexcept override;
	virtual void Update(float elapsedSec)override;
	virtual void RenderCollision()const noexcept override;

	const std::vector<Fried::line>& GetLines()const noexcept { return m_Lines; };
	const SDL_Rect& GetCollisionRect()const noexcept { return m_ColissionRect; };
private: 
	SDL_Rect m_ColissionRect;
	const bool m_IsStatic;
	std::vector<Fried::line> m_Lines;
};

