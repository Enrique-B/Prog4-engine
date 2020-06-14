#pragma once
#include "BaseComponent.h"
class ScoreComponent final: public BaseComponent
{
public:
    explicit ScoreComponent(unsigned char enemyType)noexcept;
    ScoreComponent(const ScoreComponent& other) = delete;
    ScoreComponent(ScoreComponent&& other) = delete;
    ScoreComponent& operator=(const ScoreComponent& other) = delete;
    ScoreComponent& operator=(ScoreComponent&& other) = delete;
    ~ScoreComponent() = default;
    void AddScore(size_t score)noexcept { m_Score += score; };
    void ResetScore()noexcept { m_Score = 0; }
    size_t GetScore()const noexcept { return m_Score; };
    unsigned char GetEnemyType()const noexcept { return m_EnemyType; }
    virtual void Update(float elapsedSec)noexcept override;
private: 
    unsigned char m_EnemyType;
    size_t m_Score;
};

