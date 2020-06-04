#include "MiniginPCH.h"
#include "BubleBobbleLevelDataReader.h"
#include "BinaryReaderWriter.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
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
}

void BubleBobbleLevelDataReader::ReadLevelData()
{
	// 1 bit per "cell", one screen consists of 32x25 cells. So 4 bytes for first row of first level -Koen
	BinaryReaderWriter* pBinReader{ new BinaryReaderWriter{} };
	std::ifstream input{};
	input.open("../Data/SeperatedLevelData.dat", std::ios::in | std::ios::binary);
	const int numberOfLevels{ 100 };
	const int amountOfColumns{ 25 };
	const int rowLength{ 4 };
	const int BlockWidth{ 8 };
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
		dest.y = 40;// offset for the fps component
		for (size_t j = 0; j < amountOfColumns; j++)
		{
			SDL_Rect CollisionRect{ 0,dest.y,m_DestBlockWidth,m_DestBlockWidth };
			bool wasLastBlockCollision{ false };
			dest.x = 0;
			for (size_t k = 0; k < rowLength; k++)
			{
				Byte row;
				pBinReader->Read(row, input);
				Check(row.b.bit1, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
				Check(row.b.bit2, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
				Check(row.b.bit3, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
				Check(row.b.bit4, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
				Check(row.b.bit5, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
				Check(row.b.bit6, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
				Check(row.b.bit7, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
				Check(row.b.bit8, pObject, textureName, dest, resource, CollisionRect, m_DestBlockWidth, wasLastBlockCollision);
				dest.x += m_DestBlockWidth;
			}
			pObject->AddComponent(new ColliderComponent{ CollisionRect,true });
			dest.y += m_DestBlockWidth;
		}
		pObject->AddComponent(new TextComponent{ " FPS", "Lingua.otf", 36 });
		pObject->AddComponent(new FPSComponent{});
		pObject->GetTransform()->SetPosition(0, 0);
		pScene->AddGameObject(pObject);
		pObject = new GameObject{};
		ColliderComponent* pCollider = new ColliderComponent{ SDL_Rect{0,0,m_DestBlockWidth * 2,m_DestBlockWidth * 2},false };
		pCollider->AddLines(Fried::float2{ 0,static_cast<float>(-m_DestBlockWidth - 1) });
		pCollider->AddLines(Fried::float2{ static_cast<float>(-m_DestBlockWidth) , 0 });
		pCollider->AddLines(Fried::float2{ 0, static_cast<float>(m_DestBlockWidth + 1) });
		pCollider->AddLines(Fried::float2{ static_cast<float>(m_DestBlockWidth),0 });
		pObject->AddComponent(pCollider);
		pObject->SetPosition(100.f, 50.f);
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
	const std::string spriteName{ "../Data/HeroAndEnemy.png" };
	while (!input.eof())
	{
		if (temp == 0b00000000)
		{
			levelNumber++;
			std::cout << "\nlevel " << levelNumber << std::endl;
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
			unsigned int collumn = (0b11111000 & temp) >> 3;
			pBinReader->Read(temp, input); // read the second byte 
			// (0b11111000 & second byte) >> 3 -> row
			unsigned int row = (0b11111000 & temp) >> 3;
			pObject->SetPosition(static_cast<float>(collumn * m_DestBlockWidth), static_cast<float>(row * m_DestBlockWidth + 40 - 3 * m_DestBlockWidth));
			// (0b00000111 & second byte)  bool bits // i'm going to ignore this 
			pBinReader->Read(temp, input); // read the 3rd byte 
			// (0b11000000 & third byte) bool bits // i'm also ignoring those 
			// (0b00111111 & third byte) << 1 -> amount of frames that the enemy is idle at the start of the level * 0.017 s
			float amountOfFramesIdle = ((0b00111111 & temp) << 1) * 0.017f;
			EnemyComponent* pComp{ new EnemyComponent{enemyType, amountOfFramesIdle} };
			std::cout << " "<< int(enemyType);
			pObject->AddComponent(pComp);
			pObject->AddComponent(new ColliderComponent{ collisionRect , false });
			SpriteComponent* pSprite = new SpriteComponent{ 4, 4, spriteWidth,spriteWidth, spriteName,m_DestBlockWidth * 2,m_DestBlockWidth * 2 };
			pSprite->SetDestRectHeight(float(2 * spriteWidth + enemyType * spriteWidth));
			pObject->AddComponent(pSprite);
			m_Scenes[levelNumber]->AddGameObject(pObject);
			pBinReader->Read(temp, input); // read the reading the "fist byte" again 
		}
	}
	SafeDelete(pBinReader);
}

void BubleBobbleLevelDataReader::Check(bool bit, GameObject* pObject, const std::string& textureName, const SDL_Rect& dest, const SDL_Rect& resource, SDL_Rect& Collision, int destBlockWidth, bool& wasLastBlockCollision)
{
	if (bit)
	{
		pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
		Collision.w += destBlockWidth;
		wasLastBlockCollision = true;
	}
	else
	{
		if (wasLastBlockCollision)
		{
			Collision.w -= destBlockWidth;
			pObject->AddComponent(new ColliderComponent{ Collision,true });
			Collision.x += Collision.w + destBlockWidth;
			Collision.w = destBlockWidth;
		}
		else
		{
			Collision.x += destBlockWidth;
		}
		wasLastBlockCollision = false;
	}
}
