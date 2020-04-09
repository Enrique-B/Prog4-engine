#pragma once
#include "Scene.h"
namespace Fried
{
	class SceneObject;
}
class BubleBobleScene : public Fried::Scene
{
	BubleBobleScene(const std::vector<size_t>& bitMap);
	virtual void Update(float elapsedSec) override;
	~BubleBobleScene() = default;
	BubleBobleScene(const BubleBobleScene& other) = delete;
	BubleBobleScene(BubleBobleScene&& other) = delete;
	BubleBobleScene& operator=(const BubleBobleScene& other) = delete;
	BubleBobleScene& operator=(BubleBobleScene&& other) = delete;
protected:
	virtual void Initialize()override;
	static size_t m_IstanceCounter;
	size_t m_LevelNumber;
};

