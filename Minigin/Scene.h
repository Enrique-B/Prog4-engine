#pragma once
#include <string>
class GameObject;	
class ColliderComponent;
class Observer;
struct CollisionLine;
namespace Fried
{
	struct line;
	struct HitInfo;
	class Scene final
	{
	public:
		explicit Scene(const std::string& name)noexcept;
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void AddGameObject(GameObject* object)noexcept(false);
		void AddGameObjectToNonActive(GameObject* pObject)noexcept(false);
		void RemoveGameObject(GameObject* object)noexcept(false);
		void RemoveGameObjectFromNonActive(GameObject* pObject)noexcept(false);
		void AddCollider(ColliderComponent* pCollider)noexcept(false);
		void RemoveCollider(ColliderComponent* pCollider)noexcept(false);

		void Update(float elapsedSec)noexcept(false);
		void CollisionUpdate(float elapsedSec)noexcept;
		void DeactivateNonActiveGameObjects()noexcept;
		void Render() const noexcept;
		void RenderCollision()const noexcept;

		const std::vector<GameObject*>& GetChildren()const noexcept { return m_pObjects; }
		const std::vector<GameObject*>& GetDeactivatedGameObjects()const noexcept { return m_pDeactivatedGameObjects; }
		const std::vector<Observer*>& GetObservers()const noexcept { return m_pObservers; }
		bool Raycast(const Fried::line& line, bool raycastStaticColliders, bool raycastDynamicColiders, Fried::HitInfo& hitInfo)const noexcept;
		bool RaycastPLayer(const Fried::line& line, Fried::HitInfo& hitinfo)const noexcept;
		void AddObserver(Observer* pObserver)noexcept(false);
		void Reset(); 
	private:
		std::vector<GameObject*> m_pObjects{};
		std::vector<GameObject*> m_pDeactivatedGameObjects{};
		std::string m_Name;
		std::vector<ColliderComponent*> m_StaticColliders;
		std::vector<ColliderComponent*> m_DynamicColliders;
		float m_TimeUntilNextUpdate;
		float m_TimeUntilNextScene;
		std::vector<Observer*> m_pObservers;

		void NextLevel()noexcept; 
		void CheckStaticCollision(size_t index, const std::vector<CollisionLine>& lines);
		void CheckDynamicCollision(size_t index, const std::vector<CollisionLine>& lines);

	};
}