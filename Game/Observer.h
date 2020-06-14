#pragma once
namespace Fried
{
	class Scene;
}
enum class Event : int
{
	EnemyDeath = 0,
};

class Observer
{
public: 
	explicit Observer(Fried::Scene* pScene)noexcept;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;
	~Observer() = default; 
	void Notify(Event event)noexcept;
	void SetAmountOfEnemies(int amountOfEnemies)noexcept; 
	bool IsNextLevelUnlocked()const noexcept { return m_IsNextLevelUnlocked; }
private: 
	int m_AmountOfEnemies; 
	Fried::Scene* m_pScene;
	bool m_IsNextLevelUnlocked; 
};
