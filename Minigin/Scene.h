#pragma once
#include "SceneManager.h"
#include <string>
class GameObject;	
class ColliderComponent;
namespace Fried
{
	class Scene
	{
	public:
		explicit Scene(const std::string& name)noexcept;
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void AddGameObject(GameObject* object)noexcept(false);
		void RemoveGameObject(GameObject* object)noexcept(false);
		void AddCollider(ColliderComponent* pCollider)noexcept(false);
		void RemoveCollider(ColliderComponent* pCollider)noexcept(false);

		void Update(float elapsedSec)noexcept(false);
		void CollisionUpdate()noexcept;
		void Render() const noexcept;
		void RenderCollision()const noexcept;
	protected: 
		std::vector<GameObject*> m_pObjects{};
	private:
		std::string m_Name;
		std::vector<ColliderComponent*> m_StaticColliders;
		std::vector<ColliderComponent*> m_DynamicColliders;
	};
}