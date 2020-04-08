#pragma once
namespace Fried
{
	struct float2;
}

enum class ComponentName
{
	TransFrom = 0,
	Texture = 1,
	Text = 2,
	FPS = 3,
};

class BaseComponent
{
public:
	BaseComponent() = default;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;
	virtual ~BaseComponent() = default;
	virtual void Update(float elapsedSec) = 0;
	virtual void Render(const Fried::float2& pos)const = 0;
private:

};