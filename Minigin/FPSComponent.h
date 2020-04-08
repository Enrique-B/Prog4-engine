#pragma once
#include "BaseComponent.h"
class float2;
class FPSComponent : public BaseComponent
{
public:
    FPSComponent();
    ~FPSComponent();
    virtual void Update(float elapsedSec);
    virtual void Render(const Fried::float2& pos)const;
    size_t GetFPS()const;
    bool DidFPSChange()const;
private:
    float m_AccumulatedSec;
    size_t m_FrameCounter;
    size_t m_FPS;
    bool m_DidFPSChange;
};