#pragma once
#include <vector>
enum class Event;
class Observer;
class GameObject;
class Subject
{
public: 
	Subject() = default;
	Subject(const Subject& other) = delete;
	Subject(Subject&& other) = delete;
	Subject& operator=(const Subject& other) = delete;
	Subject& operator=(Subject&& other) = delete;
	~Subject() = default;

	void AddObserver(Observer* pObserver)noexcept;
	void RemoveObserver(Observer* pObserver)noexcept;
	void Notify(Event event, GameObject* pObject)noexcept;
private: 
	std::vector<Observer*> m_pObservers;
};

