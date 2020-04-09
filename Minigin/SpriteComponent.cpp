#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>

SpriteComponent::SpriteComponent(int maxFrames, int framesPerSecond, float frameWidht, float frameHeight, const std::string& file)
	:m_FrameWidht{frameWidht}
	,m_FrameHeight{frameHeight}
	,m_AnimationTime{ 0 }
	,m_MaxFrames{maxFrames}
	,m_FramesPerSec{framesPerSecond}
	, m_AnimationFrames{ 0 }
	,m_IsAnimtionFinished{false}
	,m_pTexture{Fried::ResourceManager::GetInstance()->LoadTexture(file)}
	, m_ResourceRect{0,0,int(frameWidht), int(frameHeight)}
{
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_ImageWidth, &m_ImageHeight);
	SetComponentName(ComponentName::Sprite);
}

void SpriteComponent::Update(float elapsedSec)
{
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

void SpriteComponent::Render(const Fried::float2& pos) const
{
	SDL_Rect DestRect{};
	DestRect.x = static_cast<int>(pos.x);
	DestRect.y = static_cast<int>(pos.y);
	DestRect.w = m_ImageWidth;
	DestRect.h = m_ImageHeight;
	Fried::Renderer::GetInstance()->RenderTexture(m_pTexture, m_ResourceRect, DestRect);
}

void SpriteComponent::SetDestRectHeight(float yCoordinate)
{
	m_ResourceRect.y = static_cast<int>(yCoordinate);
}