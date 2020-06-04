#include "MiniginPCH.h"
#include "EnemyComponent.h"

EnemyComponent::EnemyComponent(unsigned char enemyType, const float amountOfSecIdle)noexcept
	:BaseComponent(),m_EnemyTypel{enemyType}, m_AmountOfSecIdle{amountOfSecIdle}
{
	SetComponentName(ComponentName::enemy);
}
