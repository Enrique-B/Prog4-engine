#pragma once
#include "BaseComponent.h"
#include "Structs.h"
class ColliderComponent : public BaseComponent
{
public:
	ColliderComponent(const SDL_Rect& collisionRect, bool isStatic);
	bool GetIsStatic()const;
	virtual void Update(float elapsedSec)override;
	virtual void RenderCollision()const override;
	void AddLines(const Fried::float2& point);
	const std::vector<Fried::line>& GetLines()const noexcept { return m_Lines; };
	const SDL_Rect& GetCollisionRect()const noexcept { m_ColissionRect; };
private: 
	SDL_Rect m_ColissionRect;
	bool m_IsStatic;
	std::vector<Fried::line> m_Lines;
};

