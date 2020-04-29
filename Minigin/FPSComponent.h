#pragma once
#include "BaseComponent.h"
class float2;
class FPSComponent final : public BaseComponent
{
public:
    FPSComponent();
    ~FPSComponent();
    virtual void Update(float elapsedSec);
    size_t GetFPS()const;
    bool DidFPSChange()const;
private:
    float m_AccumulatedSec;
    size_t m_FrameCounter;
    size_t m_FPS;
    bool m_DidFPSChange;
};