#pragma once
namespace Fried
{
	struct float2;
}

enum class ComponentName
{
	Base,
	TransFrom,
	Texture,
	Text,
	FPS,
	Sprite,
	State,
	Collider,
	Enemy,
	Bubble,
	Character,
	Score,
	Item
};
class GameObject;
class BaseComponent
{
public:
	BaseComponent()noexcept;
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;
	virtual ~BaseComponent() = default;
	virtual void Update(float elapsedSec) { UNREFERENCED_PARAMETER(elapsedSec); };
	virtual void Render(const Fried::float2& pos)const noexcept { UNREFERENCED_PARAMETER(pos); };
	virtual void RenderCollision()const noexcept {};
	ComponentName GetComponentName()const noexcept { return m_ComponentName; };
	void SetGameObject(GameObject* pObject)noexcept { m_pGameObject = pObject; };
	inline GameObject* GetGameObject()const noexcept { return m_pGameObject; };
	virtual void Initialize() {};
protected: 
	void SetComponentName(ComponentName name)noexcept { m_ComponentName = name; };
private:
	ComponentName m_ComponentName;
	GameObject* m_pGameObject;
};