#include "MiniginPCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent()
	:m_AccumulatedSec{0}
	,m_FrameCounter{0}
	,m_FPS{0}
	,m_DidFPSChange{false}
{
}

FPSComponent::~FPSComponent()
{
}

void FPSComponent::Update(float elapsedSec)
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
		}
		m_FrameCounter = 0; 
		m_AccumulatedSec = 0; 
	}
}

void FPSComponent::Render(const Fried::float2& pos) const
{
	UNREFERENCED_PARAMETER(pos);
}

size_t FPSComponent::GetFPS() const
{
	return m_FPS;
}

bool FPSComponent::DidFPSChange() const
{
	return m_DidFPSChange;
}
