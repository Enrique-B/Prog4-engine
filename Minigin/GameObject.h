#pragma once
#include <unordered_map>
#include "BaseComponent.h"

class TransformComponent;
class GameObject final
{
public:
	virtual void Update(float elapsedSec);
	virtual void Render() const;
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

	GameObject();
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;
protected:
	std::vector<BaseComponent*>m_pComponents;
	TransformComponent* m_pTranform;
private:
};