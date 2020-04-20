#pragma once
namespace Fried
{
	class Scene;
}

class BubleBobbleLevelDataReader
{
public: 
	BubleBobbleLevelDataReader(const std::string& fileName);
	void Read();
	const std::vector<Fried::Scene*>& GetScenes()const { return m_Scenes; };
private: 
	const std::string m_FileName;
	std::vector<Fried::Scene*> m_Scenes;
};

