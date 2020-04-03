#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"
class TransformComponent final : public BaseComponent 
{
public:
	TransformComponent();
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) = delete;
	~TransformComponent() = default;
	virtual void Update(float elapsedSec);
	virtual void Render(const float2& pos)const;
	const float2& GetPosition() const { return m_Position; }
	void SetPosition(float x, float y);
private:
	float2 m_Position;
};
