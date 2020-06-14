#pragma once
namespace Fried
{
	class Scene;
}
enum class Event : int
{
	EnemyDeath = 0,
	PlayerDeath = 1,
};
class GameObject;
class Observer
{
public: 
	explicit Observer(Fried::Scene* pScene)noexcept;
	Observer(const Observer& other) = delete;
	Observer(Observer&& other) = delete;
	Observer& operator=(const Observer& other) = delete;
	Observer& operator=(Observer&& other) = delete;
	virtual ~Observer() = default; 
	virtual void Notify(Event event, GameObject* pObject)noexcept = 0;
protected: 
	Fried::Scene* m_pScene;
};


class PlayerObserver final : public Observer
{
public:
	explicit PlayerObserver(Fried::Scene* pScene)noexcept;
	PlayerObserver(const PlayerObserver& other) = delete;
	PlayerObserver(PlayerObserver&& other) = delete;
	PlayerObserver& operator=(const PlayerObserver& other) = delete;
	PlayerObserver& operator=(PlayerObserver&& other) = delete;
	virtual~PlayerObserver() = default;
	virtual void Notify(Event event, GameObject* pObject)noexcept override;
private:
	unsigned int m_LivesPlayer1;
	unsigned int m_LivesPlayer2;
};

class EnemyObserver final : public Observer
{
public:
	explicit EnemyObserver(Fried::Scene* pScene)noexcept;
	EnemyObserver(const EnemyObserver& other) = delete;
	EnemyObserver(EnemyObserver&& other) = delete;
	EnemyObserver& operator=(const EnemyObserver& other) = delete;
	EnemyObserver& operator=(EnemyObserver&& other) = delete;
	~EnemyObserver() = default;
	virtual void Notify(Event event, GameObject* pObject)noexcept override;
	bool IsNextLevelUnlocked()const noexcept { return m_IsNextLevelUnlocked; }
	void SetAmountOfEnemies(int amountOfEnemies) noexcept;
private:
	int m_AmountOfEnemies;
	bool m_IsNextLevelUnlocked;
};