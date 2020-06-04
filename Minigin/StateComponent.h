#pragma once
#include <vector>
#include "BaseComponent.h"
class BaseState;
class StateComponent final : public BaseComponent
{
public: 
	StateComponent()noexcept;
	void AddState(BaseState* pState)noexcept(false);
	virtual void Update(float elapsedSec)override;
	void SetCurrentState(BaseState* pState)noexcept(false);
	BaseState* GetCurrentState()const noexcept { return m_CurrentState; };
	const std::vector<BaseState*>& GetStates()const noexcept { return m_States; };
private:
	std::vector<BaseState*> m_States;
	BaseState* m_CurrentState;
	bool m_DidStatechange;
};

