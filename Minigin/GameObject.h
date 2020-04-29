#pragma once
#include <unordered_map>
#include "BaseComponent.h"

class TransformComponent;
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
	void Render() const;
	void RenderCollision()const;
	void SetPosition(float x, float y);
	void AddComponent(BaseComponent* pComponent);
	TransformComponent* GetTransform()const { return m_pTranform; };
	bool HasComponent(ComponentName name)const;
	template <class T>
	T* GetComponent(ComponentName name) // giving the name for checks because i don't want to check typeId's
	{
		for (auto component : m_pComponents)
		{
			if (component->GetComponentName() == name)
				return static_cast<T*>(component);
		}
		return nullptr;
	}
	template <class T>
	std::vector<T*> GetComponents(ComponentName name) // giving the name for checks because i don't want to check typeId's
	{
		std::vector<T*> returnValue;
		for (auto component : m_pComponents)
		{
			if (component->GetComponentName() == name)
				returnValue.push_back(static_cast<T*>(component));
		}
		return returnValue;
	}
protected:
	std::vector<BaseComponent*>m_pComponents;
	TransformComponent* m_pTranform;
private:

};