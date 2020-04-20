#pragma once
#include <vector>
#include "BaseComponent.h"
class BaseState;
class StateComponent : public BaseComponent
{
public: 
	StateComponent();
	void AddState(BaseState* pState);
	virtual void Update(float elapsedSec)override;
	void SetCurrentState(BaseState* pState);
	BaseState* GetCurrentState()const { return m_CurrentState; };
	const std::vector<BaseState*>& GetStates()const { return m_States; };
private: 
	std::vector<BaseState*> m_States;
	BaseState* m_CurrentState;
};

