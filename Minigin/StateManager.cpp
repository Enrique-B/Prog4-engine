#include "MiniginPCH.h"
#include "StateManager.h"
#include "../Game/BaseState.h"
Fried::StateManager::~StateManager()
{
	for (auto pair : m_pLifeStates)
	{
		SafeDelete(pair.second);
	}
	for (auto pair : m_pMoveStateX)
	{
		SafeDelete(pair.second);
	}

	for (auto pair : m_pMoveStateY)
	{
		SafeDelete(pair.second);
	}

}

LifeState* Fried::StateManager::GetLifeState(const std::string& stateName)const
{
#ifdef _DEBUG
	const auto it = m_pLifeStates.find(stateName);
	if (it == m_pLifeStates.cend())
		throw std::runtime_error(std::string("StateManager::GetLifeState " + stateName + "is not in the unsorted map\n"));
#endif // _DEBUG
	return m_pLifeStates.at(stateName);
}

MoveStateX* Fried::StateManager::GetMoveStateX(const std::string& stateName) const
{
#ifdef _DEBUG
	const auto it = m_pMoveStateX.find(stateName);
	if (it == m_pMoveStateX.cend())
		throw std::runtime_error(std::string("StateManager::GetMoveStateX " + stateName + "is not in the unsorted map\n"));
#endif // _DEBUG
	return m_pMoveStateX.at(stateName);
}

MoveStateY* Fried::StateManager::GetMoveStateY(const std::string& stateName) const
{
#ifdef _DEBUG
	const auto it = m_pMoveStateY.find(stateName);
	if (it == m_pMoveStateY.cend())
		throw std::runtime_error(std::string("StateManager::GetMoveStateY " + stateName + "is not in the unsorted map\n"));
#endif // _DEBUG
	return m_pMoveStateY.at(stateName);
}

void Fried::StateManager::AddLifeState(LifeState* pLifeState)
{
#ifdef _DEBUG
	const auto it = m_pLifeStates.find(pLifeState->GetName());
	if (it != m_pLifeStates.cend())
		throw std::runtime_error(std::string("StateManager::AddLifeState " + pLifeState->GetName() + " is already in the map\n"));
#endif
	m_pLifeStates.emplace(std::make_pair(pLifeState->GetName(),pLifeState));
}

void Fried::StateManager::AddMoveStateX(MoveStateX* pMoveStateX)
{
#ifdef _DEBUG
	const auto it = m_pMoveStateX.find(pMoveStateX->GetName());
	if (it != m_pMoveStateX.cend())
		throw std::runtime_error(std::string("StateManager::AddMoveStateX " + pMoveStateX->GetName() + " is already in the map\n"));
#endif
	m_pMoveStateX.emplace(std::make_pair(pMoveStateX->GetName(), pMoveStateX));

}

void Fried::StateManager::AddMoveStateY(MoveStateY* pMoveStateY)
{
#ifdef _DEBUG
	const auto it = m_pMoveStateY.find(pMoveStateY->GetName());
	if (it != m_pMoveStateY.cend())
		throw std::runtime_error(std::string("StateManager::AddMoveStateY " + pMoveStateY->GetName() + " is already in the map\n"));
#endif
	m_pMoveStateY.emplace(std::make_pair(pMoveStateY->GetName(), pMoveStateY));
}