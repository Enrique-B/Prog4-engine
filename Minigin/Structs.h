#pragma once
#include <SDL_rect.h>
#include <vector>

inline bool AreFloatsEqual(float f1, float f2, float epilison = 0.00001)
{
	return (abs(f1 - f2) <epilison );
}

namespace Fried
{
	struct float2
	{
		float2(float X, float Y)noexcept : x{ X }, y{ Y }{}
		float2()noexcept : x{ 0 }, y{ 0 }{}
		float2(const float2& f2)noexcept :x{ f2.x }, y{ f2.y } {};
		float2(float2&& f2)noexcept :x{ f2.x }, y{ f2.y } {};
		float2& operator=(const float2& f2)noexcept
		{
			x = f2.x;
			y = f2.y;
			return *this;
		}
		float2& operator+=(const float2& f2)noexcept
		{
			x += f2.x;
			y += f2.y;
			return *this;
		}
		float2& operator=(float2&& f2)noexcept
		{
			x = f2.x;
			y = f2.y;
			return *this;
		}
		float cross(const float2& f2)const
		{
			return x * f2.y - y* f2.x;
		}
		float x;
		float y;
	};

	struct HitInfo
	{
		HitInfo() = default; 
		HitInfo(const HitInfo&) = delete;
		HitInfo(HitInfo&&) = delete;
		HitInfo& operator= (const HitInfo&) = delete;
		HitInfo& operator= (HitInfo&&) = delete;
		~HitInfo() = default;
		std::vector<float2> intersectPoint{};
		bool hit{ false };
		HitInfo& operator+=(const HitInfo& info);
	};

	inline HitInfo& HitInfo::operator+=(const HitInfo& info)
	{
		if (info.hit)
		{
			hit = info.hit;
			size_t size{ info.intersectPoint.size() };
			for (size_t i = 0; i < size; i++)
			{
				intersectPoint.push_back(info.intersectPoint[i]);
			}
		}
		return *this;
	}
	struct int2
	{
		int2(int X, int Y) : x{ X }, y{ Y }{}
		~int2() = default;
		int2() : x{ 0 }, y{ 0 }{}
		int2(const int2& f2) :x{ f2.x }, y{ f2.y } {};
		int2(int2&& f2)noexcept :x{ f2.x }, y{ f2.y } {};
		int2& operator=(const int2& f2)
		{
			x = f2.x;
			y = f2.y;
		}
		int2& operator=(int2&& f2)noexcept
		{
			x = f2.x;
			y = f2.y;
		}
		int x;
		int y;
	};

	struct line
	{
		line(const float2& point1, const float2& point2);
		line(float px1, float py1, float px2, float py2);
		line(const line&) = default;
		line(line&&) = default;
		line& operator= (const line&) = default;
		line& operator= (line&&) = default;
		~line() = default;

		float2 p1, p2;
		void intersect(const line& collisionLine, HitInfo& hitinfo)const;
		void intersect(const SDL_Rect& collisionLine,HitInfo& hitinfo)const;
		void UpdateLine(const float2& point);
		float2 differenceVec;
	};
}

inline Fried::line::line(const float2& point1, const float2& point2)
	:p1{point1},p2{point2}, differenceVec{ point2.x - point1.x ,point2.y - point1.y }
{
}

inline Fried::line::line(float px1, float py1, float px2, float py2)
	:p1{px1,py1},p2{px2,py2},differenceVec{ px2 -px1 ,py2 - py1 }
{
}

inline void Fried::line::intersect(const line& collisionLine, HitInfo& hitinfo)const
{
	//https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
	// in this example the p + r is going to be this line
	// the q + s is going to be the collisionLine
	const float2 p{ p1 };
	const float2 r{ differenceVec }; 
	const float2 q{ collisionLine.p1 };
	const float2 s{ collisionLine.differenceVec };
	const float2 differenceQP{q.x - p.x, q.y - p.y};
	const float rXs{ r.cross(s) };
	const float t = differenceQP.cross(s) / rXs;
	const float u = differenceQP.cross(r) / rXs;
	// checking if it's coliniar == on 1 line 
	

	if (rXs != 0 && (0 <= t && t <= 1) && (0 <= u && u <= 1))
	{
		hitinfo.hit = true;
		hitinfo.intersectPoint.push_back(float2(p.x + t * r.x, p.y + t * r.y));
	}
}

inline void Fried::line::intersect(const SDL_Rect& collisionRect, HitInfo& hitinfo) const
{
	const float x{static_cast<float>(collisionRect.x)};
	const float y{ static_cast<float>(collisionRect.y) };
	const float xw{ static_cast<float>(collisionRect.x + collisionRect.w)};
	const float yh{ static_cast<float>(collisionRect.y + collisionRect.h) };
	const line top{ x, y, xw, y };
	const line bottom{ x, yh, xw, yh };
	const line right{ xw, y, xw , yh };
	const line left{ x, y, x, yh };

	intersect(bottom, hitinfo);
	intersect(top, hitinfo);
	intersect(right, hitinfo);
	intersect(left, hitinfo);
}

inline void Fried::line::UpdateLine(const float2& point)
{
	p1 = point;
	p2 = float2(p1.x + differenceVec.x, p1.y + differenceVec.y);
}

inline int randUINT(int min, int max)
{
	return rand() % (max - min + 1) + min;
}
