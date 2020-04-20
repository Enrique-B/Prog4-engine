#pragma once
#include <string>
class GameObject;
class BaseState
{
public: 
	virtual void Update(float elapsedSec) = 0;
	const std::string& GetName()const { return m_Name; };
protected: 
	void SetName(const std::string& name) { m_Name = name; };
	GameObject* m_pObject;
private: 
	std::string m_Name;
};