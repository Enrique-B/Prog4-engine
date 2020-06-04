#pragma once
#include "BaseComponent.h"
#include "Structs.h"
class TransformComponent final : public BaseComponent
{
public:
	TransformComponent()noexcept;
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;
	~TransformComponent() = default;

	const Fried::float2& GetPosition() const noexcept { return m_Position; }
	void SetPosition(float x, float y)noexcept;
	void SetPosition(const Fried::float2& pos)noexcept;
	void Move(float x, float y)noexcept;
	void Move(const Fried::float2& velocity)noexcept;
private:
	Fried::float2 m_Position;
};