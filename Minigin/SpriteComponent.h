#pragma once
#include "BaseComponent.h"
#include <SDL_rect.h>
struct SDL_Texture;
class SpriteComponent final : public BaseComponent
{
	SpriteComponent(const int maxFrames, const  int framesPerSecond, const float frameWidht, const float frameHeight, const std::string& file);
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) = delete;
	virtual ~SpriteComponent() = default;

	virtual void Update(float elapsedSec) ;
	virtual void Render(const Fried::float2 & pos)const;
	void SetDestRectHeight(float yCoordinate);
	bool IsAnimationFinished()const { return m_IsAnimtionFinished; };

private: 
	const float m_FrameWidht; 
	const float m_FrameHeight;
	float m_AnimationTime;
	int m_MaxFrames;
	int m_FramesPerSec;
	int m_AnimationFrames;
	int m_ImageWidth; 
	int m_ImageHeight;
	bool m_IsAnimtionFinished;
	SDL_Texture* m_pTexture;
	SDL_Rect m_ResourceRect;
};