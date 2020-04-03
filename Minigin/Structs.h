#pragma once

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
