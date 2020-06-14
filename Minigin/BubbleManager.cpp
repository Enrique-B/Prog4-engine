#include "MiniginPCH.h"
#include "BubbleManager.h"
#include "GameObject.h"

#include "StateComponent.h"
#include "SpriteComponent.h"
#include "BubbleComponent.h"
#include "ColliderComponent.h"

Fried::BubbleManager::~BubbleManager()
{
	const size_t size{m_pBubbles.size()};
	for (size_t i = 0; i < size; i++)
	{
		SafeDelete(m_pBubbles[i]);
	}
}

GameObject* Fried::BubbleManager::GetBubble() const noexcept
{
	const size_t size{ m_pBubbles.size() };
	for (size_t i = 0; i < size; i++)
	{
		if (!m_pBubbles[i]->GetIsActive())
		{
			m_pBubbles[i]->SetIsActive(true); 
			return m_pBubbles[i];
		}
	}
	return nullptr;
}

void Fried::BubbleManager::MakeBubbles(size_t amount)
{
	const int spriteWidth{ 16 };
	const int collisionWidth{ 24 * 2 };
	m_pBubbles.reserve(m_pBubbles.size() + amount);
	for (size_t i = 0; i < amount; i++)
	{
		GameObject* pBubble = new GameObject{};
		pBubble->AddComponent(new ColliderComponent{ SDL_Rect{0 ,0, collisionWidth, collisionWidth}, false });
		pBubble->AddComponent(new SpriteComponent(4, 4, spriteWidth, spriteWidth, "bubbles.png", collisionWidth, collisionWidth));
		pBubble->AddComponent(new StateComponent{});
		pBubble->AddComponent(new BubbleComponent{ false });
		m_pBubbles.push_back(pBubble);
		pBubble->SetIsActive(false);
	}
}
