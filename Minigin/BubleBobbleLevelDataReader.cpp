#include "MiniginPCH.h"
#include "BubleBobbleLevelDataReader.h"
#include "BinaryReaderWriter.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
#include "CharacterComponent.h"
#include "Structs.h"
#include <sstream>

BubleBobbleLevelDataReader::BubleBobbleLevelDataReader()
	:m_DestBlockWidth{ 24 }
{
	m_Scenes.reserve(100);
}

union Byte //http://www.cplusplus.com/forum/general/97378/
{
	unsigned char byte; // had to change it to fix the litte/ big endian messup 
	struct B
	{
		bool bit8 : 1;
		bool bit7 : 1;
		bool bit6 : 1;
		bool bit5 : 1;
		bool bit4 : 1;
		bool bit3 : 1;
		bool bit2 : 1;
		bool bit1 : 1;
	};
	B b;
};

void BubleBobbleLevelDataReader::Read()
{
	ReadLevelData();
	ReadEnemyData();
	auto pObject = new GameObject{};

	pObject->AddComponent(new ColliderComponent{ SDL_Rect{0,0,m_DestBlockWidth * 2,m_DestBlockWidth * 2},false });
	pObject->AddComponent(new StateComponent());
	const int spriteWidth{ 16 };
	SpriteComponent* pSprite = new SpriteComponent{ 4, 4, spriteWidth,spriteWidth, "../Data/heroGreen.png",m_DestBlockWidth * 2,m_DestBlockWidth * 2 };
	pObject->AddComponent(pSprite);
	pObject->AddComponent(new CharacterComponent{});
	pObject->SetPosition(spriteWidth * 3, spriteWidth * 34 + 40);
	m_Scenes[0]->AddGameObject(pObject);
}

void BubleBobbleLevelDataReader::ReadLevelData()
{
	// 1 bit per "cell", one screen consists of 32x25 cells. So 4 bytes for first Row of first level -Koen
	BinaryReaderWriter* pBinReader{ new BinaryReaderWriter{} };
	std::ifstream input{};
	input.open("../Data/SeperatedLevelData.dat", std::ios::in | std::ios::binary);
	const int numberOfLevels{ 100 };
	const int amountOfColumns{ 25 };
	const int rowLength{ 4 };
	const int BlockWidth{ 8 };
	const int FpsOffset{ 40 };
	const std::string textureName{ "blocks.png" };
	SDL_Rect resource{ 0,0,BlockWidth, BlockWidth };
	SDL_Rect dest{ 0,0,m_DestBlockWidth,m_DestBlockWidth };
	resource.x -= BlockWidth;
	for (size_t i = 0; i < numberOfLevels; i++)
	{
		Fried::Scene* pScene{ new Fried::Scene{"level " + std::to_string(i + 1)} };
		GameObject* pObject{ new GameObject{} };
		resource.x += BlockWidth;
		if (resource.x == 80)
		{
			resource.x = 0;
			resource.y += BlockWidth;
		}
		dest.y = FpsOffset;
		for (size_t j = 0; j < amountOfColumns; j++)
		{
			SDL_Rect CollisionRect{ m_DestBlockWidth * 2 ,dest.y,m_DestBlockWidth,m_DestBlockWidth };
			bool wasLastBlockCollision{ false };
			Row line{};
			if (j == 0)
				line = Row::first;
			else if (j == amountOfColumns - 1)
			{
				wasLastBlockCollision = true;
				line = Row::last;
			}
			else
				line = Row::mid;
			dest.x = 0;
			bool firstOrLast2Coloms{false};
			for (size_t k = 0; k < rowLength; k++)
			{
				Byte row;
				pBinReader->Read(row, input);
				if (k == 0)
					firstOrLast2Coloms = true;
				Check(row.b.bit1, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
				Check(row.b.bit2, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
				firstOrLast2Coloms = false; 
				Check(row.b.bit3, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
				Check(row.b.bit4, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
				Check(row.b.bit5, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
				Check(row.b.bit6, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
				if (k == rowLength-1 )
					firstOrLast2Coloms = true;
				Check(row.b.bit7, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
				Check(row.b.bit8, pObject, textureName, dest, resource, CollisionRect, wasLastBlockCollision, line, firstOrLast2Coloms);
			}
			if (line != Row::first)
			{
				CollisionRect.w -= m_DestBlockWidth;
			}
			dest.y += m_DestBlockWidth;
		}
		pObject->AddComponent(new ColliderComponent{ SDL_Rect{0,40,m_DestBlockWidth * 2, m_DestBlockWidth *  25}, true });
		pObject->AddComponent(new ColliderComponent{ SDL_Rect{m_DestBlockWidth * 30,40,m_DestBlockWidth * 2, m_DestBlockWidth * 25}, true });
		pObject->AddComponent(new TextComponent{ " FPS", "Lingua.otf", 36 });
		pObject->AddComponent(new FPSComponent{});
		pObject->GetTransform()->SetPosition(0, 0);
		pScene->AddGameObject(pObject);
		m_Scenes.push_back(pScene);
	}
	SafeDelete(pBinReader);
}

void BubleBobbleLevelDataReader::ReadEnemyData()
{
	BinaryReaderWriter* pBinReader{ new BinaryReaderWriter{} };
	std::ifstream input{};
	input.open("../Data/SeperatedEnemyData.dat", std::ios::in | std::ios::binary);
	unsigned char temp;
	pBinReader->Read(temp, input);
	unsigned int levelNumber{0};
	const SDL_Rect collisionRect{ 0,0,m_DestBlockWidth * 2 ,m_DestBlockWidth * 2 };
	// comments how to read the enemydata from Nickey
	// fist byte == 0b00000000 end of level data
	const int spriteWidth{ 16 };
	const std::string spriteName{ "../Data/Enemy.png" };
	while (!input.eof())
	{
		if (temp == 0b00000000)
		{
			levelNumber++;
			pBinReader->Read(temp, input); // read the reading the "fist byte" again 
		}	// if not
		else
		{
			GameObject* pObject{ new GameObject{} };
			// read next 2 bytes
			// in those  3 bytes all the enemy data is in there
			// 0b00000111 & first byte -> enemy type
			unsigned char enemyType = 0b00000111 & temp;
			// (0b11111000 & first byte) >> 3 -> collumn
			int collumn = (0b11111000 & temp) >> 3;
			pBinReader->Read(temp, input); // read the second byte 
			// (0b11111000 & second byte) >> 3 -> Row
			int row = (0b11111000 & temp) >> 3;
			const float x{ float(collumn * m_DestBlockWidth) };
			const float y{ float(row * m_DestBlockWidth + 40 - 3 * m_DestBlockWidth) };
			pObject->SetPosition(x, y);
			// (0b00000111 & second byte)  bool bits // i'm going to ignore this 
			pBinReader->Read(temp, input); // read the 3rd byte 
			// (0b11000000 & third byte) bool bits // i'm also ignoring those 
			// (0b00111111 & third byte) << 1 -> amount of frames that the enemy is idle at the start of the level * 0.017 s
			float amountOfFramesIdle = ((0b00111111 & temp) << 1) /20.f;
			// 7th bit of the 3rd byte is the way they're looking; 
			bool IsLookingLight = temp & (1 << 7);
			EnemyComponent* pComp{ new EnemyComponent{enemyType, amountOfFramesIdle, IsLookingLight} };
			pObject->AddComponent(pComp);
			pObject->AddComponent(new ColliderComponent{ collisionRect , false });
			SpriteComponent* pSprite = new SpriteComponent{ 4, 4, spriteWidth,spriteWidth, spriteName,m_DestBlockWidth * 2,m_DestBlockWidth * 2 };
			pSprite->SetDestRectHeight(float(enemyType * spriteWidth));
			pObject->AddComponent(pSprite);
			pObject->AddComponent(new StateComponent{});
			m_Scenes[levelNumber]->AddGameObject(pObject);
			pBinReader->Read(temp, input); // read the reading the "fist byte" again 
		}
	}
	SafeDelete(pBinReader);
}

void BubleBobbleLevelDataReader::Check(bool bit, GameObject* pObject, const std::string& textureName, SDL_Rect& dest, const SDL_Rect& resource, SDL_Rect& Collision, bool& wasLastBlockCollision,const Row& row, bool firstOrLast2Coloms)
{
	if (bit)
	{
		if (firstOrLast2Coloms)
		{
			if (wasLastBlockCollision)
			{
				if (row == Row::last)
				{
					pObject->AddComponent(new ColliderComponent{ Collision,true });
				}
				else if (row != Row::first)
				{
					Collision.w -= m_DestBlockWidth;
					pObject->AddComponent(new ColliderComponent{ Collision,true });
					Collision.x += Collision.w + m_DestBlockWidth;
					Collision.w = m_DestBlockWidth;
				}
			}
			wasLastBlockCollision = false;

		}
		else if (row == Row::last && !wasLastBlockCollision)
		{
			Collision.x -= m_DestBlockWidth;
			if (Collision.x >= 2 * m_DestBlockWidth)
			{
				pObject->AddComponent(new ColliderComponent{ Collision,true });
			}
			
			Collision.x += Collision.w;
			Collision.w = 2 * m_DestBlockWidth;
			wasLastBlockCollision = true;
		}
		else
		{
			Collision.w += m_DestBlockWidth; 		
			wasLastBlockCollision = true;

		}
		UNREFERENCED_PARAMETER(resource);
		UNREFERENCED_PARAMETER(textureName);
		pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
	}
	else
	{
		if (wasLastBlockCollision)
		{
			if (row != Row::first)
			{
				Collision.w -= m_DestBlockWidth;
				pObject->AddComponent(new ColliderComponent{ Collision,true });
				Collision.x += Collision.w + m_DestBlockWidth;
				Collision.w = m_DestBlockWidth;
			}
		}
		else
		{
			if (row == Row::last)
			{
				Collision.w += m_DestBlockWidth;
			}
			else
			{
				Collision.x += m_DestBlockWidth;
			}
		}
		wasLastBlockCollision = false;
	}
	dest.x += m_DestBlockWidth;
}
