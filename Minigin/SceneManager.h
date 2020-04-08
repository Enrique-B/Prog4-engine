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

		void Update(float elapsedSec);
		void Render();
		~SceneManager();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_pScenes;
	};
}
