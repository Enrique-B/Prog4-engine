#pragma once
#include "Singleton.h"
#include <vector>
class GameObject; 
namespace Fried
{
	class BubbleManager final : public Singleton<BubbleManager>
	{
	public: 
		BubbleManager(const BubbleManager& other) = delete;
		BubbleManager(BubbleManager&& other) = delete;
		BubbleManager& operator=(const BubbleManager& other) = delete;
		BubbleManager& operator=(BubbleManager&& other) = delete;
		~BubbleManager(); 
		GameObject* GetBubble()const noexcept;
		void MakeBubbles(size_t amount);
	private: 
		friend class Singleton<BubbleManager>;
		BubbleManager() = default;
		std::vector<GameObject*> m_pBubbles;
	};
}