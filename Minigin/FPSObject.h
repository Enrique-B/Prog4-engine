#pragma once
#include "SceneObject.h"
#include "BaseComponent.h"
#include <unordered_map>

namespace Fried
{
	class FPSObject final : public SceneObject
	{
	public:
		FPSObject();
		virtual ~FPSObject();
		virtual void Update(float elapsedSec);
		virtual void Render()const;
		void AddComponent(ComponentName componentName, BaseComponent* pComponent);
	private:
		std::unordered_map<ComponentName, BaseComponent*> m_pComponents;
	};
}