#pragma once
#include "SceneManager.h"

class SceneObject;
class Scene
{
public:
	void Add(SceneObject* object);

	virtual void Update(float elapsedSec) = 0;
	void Render() const;

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;
protected: 
	explicit Scene(const std::string& name);
	virtual void Initialize();
	std::vector < SceneObject*> m_pObjects{};
private:

	std::string m_Name;

	static unsigned int m_IdCounter;
};
