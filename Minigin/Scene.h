#pragma once
#include "SceneManager.h"
#include <string>
class GameObject;	
class ColliderComponent;
struct CollisionLine;
namespace Fried
{
	struct line;
	struct HitInfo;
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
		void CollisionUpdate(float elapsedSec)noexcept;
		void Render() const noexcept;
		void RenderCollision()const noexcept;
		const std::vector<GameObject*>& GetChildren()const noexcept { return m_pObjects; }
		bool Raycast(const Fried::line& line, bool raycastStaticColliders, bool raycastDynamicColiders, Fried::HitInfo& hitInfo);
		bool RaycastPLayer(const Fried::line& line, Fried::HitInfo& hitinfo);

	protected: 
		std::vector<GameObject*> m_pObjects{};
	private:
		std::string m_Name;
		std::vector<ColliderComponent*> m_StaticColliders;
		std::vector<ColliderComponent*> m_DynamicColliders;
		void CheckStaticCollision(size_t index, const std::vector<CollisionLine>& lines);
		void CheckDynamicCollision(size_t index, const std::vector<CollisionLine>& lines);
		float timeUntilNextUpdate;
	};
}