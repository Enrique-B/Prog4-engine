#include "MiniginPCH.h"
#include "StateComponent.h"
#include "../Game/BaseState.h"
StateComponent::StateComponent()noexcept
	:BaseComponent()
	, m_DidStatechange{false}
	, m_CurrentState{nullptr}
{
	SetComponentName(ComponentName::state);
}

void StateComponent::AddState(BaseState* pState)
{
	const size_t size{m_States.size()};
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(m_States[i]->GetName().c_str(),pState->GetName().c_str()) == 0) //http://www.cplusplus.com/reference/cstring/strcmp/
		{
			throw std::runtime_error(std::string("StateComponent::AddState state was already in the GameObject\n"));
			return;
		}
	}
	m_States.push_back(pState);
}

void StateComponent::Update(float elapsedSec)
{
	m_CurrentState->Update(elapsedSec);
}

void StateComponent::SetCurrentState(BaseState* pState)
{
#if _DEBUG
	if (pState == nullptr)
		throw std::runtime_error(std::string("StateComponent::SetCurrentState pState was a nullptr"));
#endif // _DEBUG
	m_DidStatechange = m_CurrentState != pState;
	if (m_DidStatechange)
		m_CurrentState = pState;
}
