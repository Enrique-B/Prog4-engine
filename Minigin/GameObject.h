#pragma once
#include <unordered_map>
#include "BaseComponent.h"
#include "SceneObject.h"

namespace Fried
{
	class GameObject final : public SceneObject
	{
	public:
		virtual void Update(float elapsedSec);
		virtual void Render() const;

		void SetPosition(float x, float y);
		void AddComponent(ComponentName componentName, BaseComponent* pComponent);
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	protected:
		std::unordered_map<ComponentName, BaseComponent*> m_pComponents;
	private:
		bool m_CanRender;
	};
}