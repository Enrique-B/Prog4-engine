#pragma once
#include <unordered_map>
#include "BaseComponent.h"

class TransformComponent;
namespace Fried
{
	class Scene;
}
class GameObject final
{
public:
	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Update(float elapsedSec);
	void Render() const noexcept;
	void RenderCollision()const noexcept;
	void SetPosition(float x, float y) noexcept;
	void AddComponent(BaseComponent* pComponent)noexcept(false);
	TransformComponent* GetTransform()const noexcept { return m_pTranform; };
	bool HasComponent(ComponentName name)const noexcept;
	template <class T>
	T* GetComponent(ComponentName name) noexcept // giving the name for checks because i don't want to check typeId's
	{
		for (auto component : m_pComponents)
		{
			if (component->GetComponentName() == name)
				return static_cast<T*>(component);
		}
		return nullptr;
	}
	template <class T>
	std::vector<T*> GetComponents(ComponentName name)noexcept // giving the name for checks because i don't want to check typeId's
	{
		std::vector<T*> returnValue;
		for (auto component : m_pComponents)
		{
			if (component->GetComponentName() == name)
				returnValue.push_back(static_cast<T*>(component));
		}
		return returnValue;
	}
	bool GetIsActive()const noexcept { return m_IsActive; }
	void SetIsActive(bool isActive); 
	Fried::Scene* GetScene()const { return m_pScene; };
	void SetScene(Fried::Scene* pScene)noexcept { m_pScene = pScene; }
	void Initialize()noexcept(false);
private:
	bool m_IsActive;
	std::vector<BaseComponent*>m_pComponents;
	TransformComponent* m_pTranform;
	Fried::Scene* m_pScene;
};