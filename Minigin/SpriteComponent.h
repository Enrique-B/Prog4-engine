#pragma once
#include "BaseComponent.h"
#include <SDL_rect.h>
struct SDL_Texture;
class SpriteComponent final : public BaseComponent
{
public:
	SpriteComponent(const int maxFrames, const  int framesPerSecond, const float frameWidht, const float frameHeight, const std::string& file, int destHeight, int destWidth)noexcept(false);
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) = delete;
	virtual ~SpriteComponent() = default;

	virtual void Update(float elapsedSec)noexcept;
	virtual void Render(const Fried::float2 & pos)const noexcept;
	void SetDestRectY(float yCoordinate)noexcept;
	bool IsAnimationFinished()const noexcept { return m_IsAnimtionFinished; };
	void SetIsGoingLeft(bool isGoingLeft)noexcept { m_IsGoingLeft = isGoingLeft; };
	bool GetIsGoingLeft()const noexcept { return m_IsGoingLeft; }
	void SetUpdate(bool update) { m_IsUpUpdating = update;};
	void SetFrame(int number);
	void SetMaxedFrames(int maxFrames);
private: 
	const float m_FrameWidht; 
	const float m_FrameHeight;
	float m_AnimationTime;
	const int m_DestWidth; 
	const int m_DestHeight;
	int m_MaxFrames;
	int m_FramesPerSec;
	int m_AnimationFrames;
	bool m_IsAnimtionFinished;
	bool m_IsGoingLeft;
	bool m_IsUpUpdating; 
	SDL_Texture* m_pTexture;
	SDL_Rect m_ResourceRect;
};