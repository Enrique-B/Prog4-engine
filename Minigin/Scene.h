#pragma once
#include "SceneManager.h"
#include <string>
class GameObject;	
namespace Fried
{
	class Scene
	{
	public:
		explicit Scene(const std::string& name);
		void Add(GameObject* object);

		void Update(float elapsedSec);
		void CollisionUpdate();
		void Render() const;
		void RenderCollision()const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	protected:
		virtual void Initialize();
		std::vector <GameObject*> m_pObjects{};
	private:

		std::string m_Name;

		static unsigned int m_IdCounter;
	};
}