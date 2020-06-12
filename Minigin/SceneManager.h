#pragma once
#include "Singleton.h"
#include <vector>

namespace Fried
{
class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();
		void AddScene(Scene* pScene)noexcept(false);
		void NextScene()noexcept;
		Scene* GetNextScene()noexcept;
		Scene* GetPreviousScene()noexcept;
		void Update(float elapsedSec);
		void CollisionUpdate(float elapsedSec)noexcept;
		void Render()noexcept;
		void DeactivateNonActiveGameObjects()noexcept(false);
		void SetIsRenderingCollision(bool isRenderingCollision)noexcept {m_IsRenderingCollision = isRenderingCollision;}
		bool GetIsRenderingCollision()const noexcept { return m_IsRenderingCollision; }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() : m_CurrentScene{0} , m_IsRenderingCollision(true){};
		std::vector<Scene*> m_pScenes;
		size_t m_CurrentScene;
		bool m_IsRenderingCollision;
	};
}
