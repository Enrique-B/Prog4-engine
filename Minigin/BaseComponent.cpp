#include "MiniginPCH.h"
#include "BaseComponent.h"

BaseComponent::BaseComponent()noexcept
	:m_ComponentName{ComponentName::Base}
	,m_pGameObject{nullptr}
{
}
