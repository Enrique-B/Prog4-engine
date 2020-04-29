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
		void CollisionUpdate();
		void Render();
		void SetIsRenderingCollision(bool isRenderingCollision);
		bool GetIsRenderingCollision()const { return m_IsRenderingCollision; };
		~SceneManager();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() : m_CurrentScene{0} , m_IsRenderingCollision(false){};
		std::vector<Scene*> m_pScenes;
		size_t m_CurrentScene;
		bool m_IsRenderingCollision;
	};
}
