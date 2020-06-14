#pragma once
#include "Singleton.h"
#include <vector>

namespace Fried
{
class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		enum class UI :unsigned int
		{
			StartMenu = 0,
			GameMenu = 1,
			PauseMenu = 2
		};
		~SceneManager();		
		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		void AddUIScene(Scene* pScene, UI uiType)noexcept(false);
		void AddScene(Scene* pScene)noexcept(false);
		void NextScene()noexcept;
		Scene* GetUIScene(UI ui)const noexcept { return m_pUIScenes[unsigned int(ui)]; }
		void SetUIScene(UI ui)noexcept { m_CurrentUIScene = ui; };
		UI GetUI()const noexcept { return m_CurrentUIScene; }
		Scene* GetNextScene()const noexcept;
		Scene* GetPreviousScene()const noexcept;
		void Update(float elapsedSec);
		void CollisionUpdate(float elapsedSec)noexcept;
		void Render()noexcept;
		void DeactivateNonActiveGameObjects()noexcept(false);
		void SetIsRenderingCollision(bool isRenderingCollision)noexcept {m_IsRenderingCollision = isRenderingCollision;}
		bool GetIsRenderingCollision()const noexcept { return m_IsRenderingCollision; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<Scene*> m_pScenes;
		std::vector<Scene*> m_pUIScenes;
		size_t m_CurrentScene;
		UI m_CurrentUIScene;
		bool m_IsRenderingCollision;
	};
}
