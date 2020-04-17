#pragma once
#include "BaseComponent.h"
#include "Structs.h"
class TransformComponent final : public BaseComponent
{
public:
	TransformComponent();
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;
	~TransformComponent() = default;
	const Fried::float2& GetPosition() const { return m_Position; }
	void SetPosition(float x, float y);
private:
	Fried::float2 m_Position;
};