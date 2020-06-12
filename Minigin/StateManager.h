#pragma once
#include "Singleton.h"
#include <unordered_map>
#include <string>
class MoveStateX;
class LifeState;
class MoveStateY;
class WeaponState;
namespace Fried
{
	class StateManager : public Singleton<StateManager>
	{
	public:
		StateManager() = default;
		~StateManager();
		LifeState* GetLifeState(const std::string& stateName)const;
		MoveStateX* GetMoveStateX(const std::string& stateName)const;
		MoveStateY* GetMoveStateY(const std::string& stateName)const;
		WeaponState* GetWeaponState(const std::string& stateName)const;

		void AddLifeState(LifeState* pLifeState);
		void AddMoveStateX(MoveStateX* pMoveStateX);
		void AddMoveStateY(MoveStateY* pMoveStateY);
		void AddWeaponState(WeaponState* pWeaponState);

	private: 
		std::unordered_map<std::string, LifeState*> m_pLifeStates;
		std::unordered_map<std::string, MoveStateX*> m_pMoveStateX;
		std::unordered_map<std::string, MoveStateY*> m_pMoveStateY;
		std::unordered_map<std::string, WeaponState*> m_pWeaponStates;
	};
}