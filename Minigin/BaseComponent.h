#pragma once
namespace Fried
{
	struct float2;
}

enum class ComponentName
{
	Base = 0,
	TransFrom = 1,
	Texture = 2,
	Text = 3,
	FPS = 4,
	Sprite = 5,
	state = 6,
	collider = 7,
};
class GameObject;
class BaseComponent
{
public:
	BaseComponent();
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;
	virtual ~BaseComponent() = default;
	virtual void Update(float elapsedSec) { UNREFERENCED_PARAMETER(elapsedSec); };
	virtual void Render(const Fried::float2& pos)const { UNREFERENCED_PARAMETER(pos); };
	virtual void RenderCollision()const {};
	ComponentName GetComponentName()const { return m_ComponentName; };
	void SetGameObject(GameObject* pObject) { m_pGameObject = pObject; };
protected: 
	void SetComponentName(ComponentName name) { m_ComponentName = name; };
	GameObject* GetGameObject()const { return m_pGameObject; };
private:
	ComponentName m_ComponentName;
	GameObject* m_pGameObject;
};