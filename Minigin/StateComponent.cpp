#include "MiniginPCH.h"
#include "StateComponent.h"
#include "../Game/BaseState.h"
StateComponent::StateComponent()
	:BaseComponent()
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
			std::cout << "state was already in statecomponent";
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
	if (pState != nullptr && m_CurrentState != pState)
		m_CurrentState = pState;
}
