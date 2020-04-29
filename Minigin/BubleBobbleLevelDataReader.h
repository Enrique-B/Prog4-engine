#pragma once
#include <SDL_rect.h>
namespace Fried
{
	class Scene;
}
class GameObject;
class BubleBobbleLevelDataReader
{
public: 
	BubleBobbleLevelDataReader(const std::string& fileName);
	void Read();
	const std::vector<Fried::Scene*>& GetScenes()const { return m_Scenes; };
private: 
	const std::string m_FileName;
	std::vector<Fried::Scene*> m_Scenes;
	void Check(bool bit, GameObject* pObject, const std::string& TextureName, const SDL_Rect& dest, const SDL_Rect& resource, SDL_Rect& Collision, int destBlockWidth, bool& wasLastBlockCollison);
};

