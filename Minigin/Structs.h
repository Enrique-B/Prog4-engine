#pragma once
namespace Fried
{
	struct float2
	{
		float2(float X, float Y) : x{ X }, y{ Y }{}
		float2() : x{ 0 }, y{ 0 }{}
		float2(const float2& f2) :x{ f2.x }, y{ f2.y } {};
		float2& operator=(const float2& f2)
		{
			x = f2.x;
			y = f2.y;
		}
		float x;
		float y;
	};

	struct int2
	{
		int2(int X, int Y) : x{ X }, y{ Y }{}
		int2() : x{ 0 }, y{ 0 }{}
		int2(const int2& f2) :x{ f2.x }, y{ f2.y } {};
		int2& operator=(const int2& f2)
		{
			x = f2.x;
			y = f2.y;
		}
		int x;
		int y;
	};
}