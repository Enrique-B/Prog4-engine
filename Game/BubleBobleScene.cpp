#include "MiniginPCH.h"
#include "BubleBobleScene.h"

size_t BubleBobleScene::m_IstanceCounter = 0; // used for the map blocks and the enemies;

BubleBobleScene::BubleBobleScene(const std::vector<size_t>& bitMap)
	:Fried::Scene("BubleBobleScene" + std::to_string(m_IstanceCounter))
{
	++m_IstanceCounter;
	m_LevelNumber = m_IstanceCounter;
	UNREFERENCED_PARAMETER(bitMap);
}

void BubleBobleScene::Update(float elapsedSec)
{
	UNREFERENCED_PARAMETER(elapsedSec);
}

void BubleBobleScene::Initialize()
{

}