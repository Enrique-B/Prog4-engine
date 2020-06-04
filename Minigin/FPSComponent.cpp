#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

FPSComponent::FPSComponent()noexcept
	:m_AccumulatedSec{0}
	,m_FrameCounter{0}
	,m_FPS{0}
	,m_DidFPSChange{false}
	,m_pText{nullptr}
{
	SetComponentName(ComponentName::FPS);
}

FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update(float elapsedSec)noexcept
{
	m_DidFPSChange = false;
	m_AccumulatedSec += elapsedSec;
	m_FrameCounter++; 
	if (m_AccumulatedSec > 1)
	{
		if (m_FPS != m_FrameCounter)
		{
			m_FPS = m_FrameCounter;
			m_DidFPSChange = true;
			m_pText->SetText(std::to_string(m_FPS) + " FPS");
		}
		m_FrameCounter = 0; 
		m_AccumulatedSec = 0; 
	}
}

void FPSComponent::Initialize()
{
	// I know this is an ugly dependicy but you have to do what you have to do when you can't parent gameObjects; 
#ifdef _DEBUG
	if (!GetGameObject()->HasComponent(ComponentName::Text))
	{
		throw std::runtime_error(std::string("FPSComponent::Initialize gameObject didn't have a textComponent \n"));
	}
#endif // _DEBUG
	m_pText = GetGameObject()->GetComponent<TextComponent>(ComponentName::Text);
}
