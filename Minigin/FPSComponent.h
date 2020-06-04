#pragma once
#include "BaseComponent.h"

class TextComponent;
class FPSComponent final : public BaseComponent
{
public:
    FPSComponent()noexcept;
    ~FPSComponent();

    virtual void Initialize()noexcept(false) override;
    virtual void Update(float elapsedSec)noexcept;

    size_t GetFPS()const noexcept { return m_FPS; };
    bool DidFPSChange()const noexcept { return m_DidFPSChange; };

private:
    float m_AccumulatedSec;
    size_t m_FrameCounter;
    size_t m_FPS;
    bool m_DidFPSChange;
    TextComponent* m_pText;
};