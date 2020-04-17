#pragma once
#include "SceneManager.h"
#include <string>
class GameObject;	
namespace Fried
{
	class Scene
	{
	public:
		void Add(GameObject* object);

		virtual void Update(float elapsedSec) = 0;
		void Render() const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	protected:
		explicit Scene(const std::string& name);
		virtual void Initialize();
		std::vector <GameObject*> m_pObjects{};
	private:

		std::string m_Name;

		static unsigned int m_IdCounter;
	};
}