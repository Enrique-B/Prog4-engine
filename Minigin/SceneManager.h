#pragma once
#include "Singleton.h"
#include <vector>

namespace Fried
{
class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void AddScene(Scene* pScene);
		void NextScene();
		void Update(float elapsedSec);
		void Render();
		~SceneManager();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() : m_CurrentScene{0} {};
		std::vector<Scene*> m_pScenes;
		size_t m_CurrentScene;
	};
}
