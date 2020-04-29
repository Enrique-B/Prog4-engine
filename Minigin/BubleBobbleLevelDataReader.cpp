#include "MiniginPCH.h"
#include "BubleBobbleLevelDataReader.h"
#include "BinaryReaderWriter.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components.h"
#include "Structs.h"
#include <sstream>

BubleBobbleLevelDataReader::BubleBobbleLevelDataReader(const std::string& fileName)
	:m_FileName{fileName}
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
	// 1 bit per "cell", one screen consists of 32x25 cells. So 4 bytes for first row of first level -Koen
	BinaryReaderWriter* pBinReader{ new BinaryReaderWriter{} };
	std::ifstream input{};
	input.open(m_FileName.c_str(), std::ios::in | std::ios::binary);	
	const int numberOfLevels{100};
	const int amountOfColumns{25};
	const int rowLength{4};
	const int BlockWidth{ 8 };
	const int destBlockWidth{ 24 };
	const std::string textureName{"blocks.png"};
	SDL_Rect resource{0,0,BlockWidth, BlockWidth};
	SDL_Rect dest{0,0,destBlockWidth,destBlockWidth };
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
		dest.y = 0;
		for (size_t j = 0; j < amountOfColumns; j++)
		{
			SDL_Rect CollisionRect{ 0,dest.y,destBlockWidth,destBlockWidth };
			bool wasLastBlockCollision{ false };
			dest.x = 0;
			for (size_t k = 0; k < rowLength; k++)
			{
				Byte row;
				pBinReader->Read(row, input);
				Check(row.b.bit1, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
				Check(row.b.bit2, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
				Check(row.b.bit3, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
				Check(row.b.bit4, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
				Check(row.b.bit5, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
				Check(row.b.bit6, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
				Check(row.b.bit7, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
				Check(row.b.bit8, pObject, textureName, dest, resource, CollisionRect, destBlockWidth, wasLastBlockCollision);
				dest.x += destBlockWidth;
			}
			pObject->AddComponent(new ColliderComponent{ CollisionRect,true });
			dest.y += destBlockWidth;
		}
		pObject->AddComponent(new TextComponent{ "60 FPS", "Lingua.otf", 36 });
		pObject->AddComponent(new FPSComponent{});
		pObject->GetTransform()->SetPosition(200, 50);
		pScene->Add(pObject);
		pObject = new GameObject{};
		ColliderComponent* pCollider = new ColliderComponent{ SDL_Rect{0,0,destBlockWidth *2,destBlockWidth * 2},false };
		pCollider->AddLines(Fried::float2{ 0,-destBlockWidth  - 1 });
		pCollider->AddLines(Fried::float2{ -destBlockWidth , 0 });
		pCollider->AddLines(Fried::float2{ 0, destBlockWidth  + 1 });
		pCollider->AddLines(Fried::float2{ destBlockWidth,0 });
		pObject->AddComponent(pCollider);
		pObject->SetPosition(100.f, 50.f);
		pScene->Add(pObject);
		m_Scenes.push_back(pScene);
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
