#pragma once
#include <SDL_rect.h>
#include <string>
namespace Fried
{
	class Scene;
}

class GameObject;
class BubleBobbleLevelDataReader
{
public: 
	BubleBobbleLevelDataReader();
	BubleBobbleLevelDataReader(const BubleBobbleLevelDataReader& other) = delete;
	BubleBobbleLevelDataReader(BubleBobbleLevelDataReader&& other) = delete;
	BubleBobbleLevelDataReader& operator=(const BubleBobbleLevelDataReader& other) = delete;
	BubleBobbleLevelDataReader& operator=(BubleBobbleLevelDataReader&& other) = delete;
	~BubleBobbleLevelDataReader() = default;

	void Read()noexcept;
	const std::vector<Fried::Scene*>& GetScenes()const noexcept{ return m_Scenes; };
private: 
	enum class Row
	{
		first, mid, last
	};
	const int m_DestBlockWidth;
	std::vector<Fried::Scene*> m_Scenes;
	void ReadLevelData()noexcept;
	void ReadEnemyData()noexcept;
	void MakeCharacters()noexcept;
	void Check(bool bit, GameObject* pObject, const std::string& TextureName, SDL_Rect& dest, const SDL_Rect& resource, 
		SDL_Rect& Collision, bool& wasLastBlockCollison, const Row& row, bool firstOrLast2Coloms)noexcept;
};

