#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>

SpriteComponent::SpriteComponent(int maxFrames, int framesPerSecond, float frameWidht, float frameHeight, const std::string& file, int destHeight, int destWidth)
	:m_FrameWidht{frameWidht}
	,m_FrameHeight{frameHeight}
	,m_AnimationTime{ 0 }
	,m_MaxFrames{maxFrames}
	,m_FramesPerSec{framesPerSecond}
	, m_AnimationFrames{ 0 }
	, m_DestWidth{ destWidth }
	, m_DestHeight{ destHeight }
	,m_IsAnimtionFinished{false}
	,m_pTexture{Fried::ResourceManager::GetInstance()->LoadTexture(file)}
	, m_ResourceRect{0,0,int(frameWidht), int(frameHeight)}
	, m_IsGoingLeft{true}
{
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, nullptr, nullptr);
	SetComponentName(ComponentName::Sprite);
}

void SpriteComponent::Update(float elapsedSec)noexcept
{
	if (!m_IsUpUpdating)
	{
		return;
	}
	// updating the animation 
	m_IsAnimtionFinished = false;
	m_AnimationTime += elapsedSec;
	if (m_AnimationTime >= (1 / float(m_FramesPerSec)))
	{
		m_AnimationTime = 0;
		m_AnimationFrames = m_AnimationFrames % m_MaxFrames + 1;
		m_ResourceRect.x = static_cast<int>( m_AnimationFrames * m_FrameWidht);
		if (m_AnimationFrames == m_MaxFrames)
		{
			m_IsAnimtionFinished = true;
			m_AnimationFrames = 0;
			m_ResourceRect.x = static_cast<int>(m_AnimationFrames * m_FrameWidht);
		}
	}
	if (m_AnimationFrames >= m_MaxFrames)
	{
		m_AnimationFrames = 0;
		m_IsAnimtionFinished = true;
		m_ResourceRect.x = static_cast<int>(m_AnimationFrames * m_FrameWidht);
	}

}

void SpriteComponent::Render(const Fried::float2& pos) const noexcept
{
	SDL_Rect DestRect{};
	DestRect.x = static_cast<int>(pos.x);
	DestRect.y = static_cast<int>(pos.y);
	DestRect.w = m_DestWidth;
	DestRect.h = m_DestHeight;
	Fried::Renderer::GetInstance()->RenderTexture(m_pTexture, m_ResourceRect, DestRect, 0, SDL_Point{}, m_IsGoingLeft);
}

void SpriteComponent::SetDestRectHeight(float yCoordinate)noexcept
{
	m_ResourceRect.y = static_cast<int>(yCoordinate);
}

void SpriteComponent::SetFrame(int number)
{
	if (number >= m_MaxFrames + 1)
	{
		return;
	}
	m_AnimationFrames = number; 
	m_ResourceRect.x = static_cast<int>(m_AnimationFrames * m_FrameWidht);
}

void SpriteComponent::SetMaxedFrames(int maxFrames)
{
	m_MaxFrames = maxFrames;
}

