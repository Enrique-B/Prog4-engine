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
	const size_t numberOfLevels{100};
	const size_t amountOfColumns{25};
	const size_t rowLength{4};
	const std::string textureName{"blocks.png"};
	const size_t BlockWidth{ 8 };
	SDL_Rect resource{0,0,BlockWidth, BlockWidth};
	const size_t destBlockWidth{ 24 };
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
			dest.x = 0;
			for (size_t k = 0; k < rowLength; k++)
			{
				Byte row;
				pBinReader->Read(row, input);
				if (row.b.bit1)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource  });
				dest.x += destBlockWidth;
				if (row.b.bit2)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
				dest.x += destBlockWidth;
				if (row.b.bit3)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
				dest.x += destBlockWidth;
				if (row.b.bit4)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
				dest.x += destBlockWidth;
				if (row.b.bit5)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
				dest.x += destBlockWidth;
				if (row.b.bit6)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
				dest.x += destBlockWidth;
				if (row.b.bit7)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
				dest.x += destBlockWidth;
				if (row.b.bit8)
					pObject->AddComponent(new TextureComponent{ textureName, dest, resource });
				dest.x += destBlockWidth;
			}
			dest.y += destBlockWidth;
		}
		pScene->Add(pObject);
		m_Scenes.push_back(pScene);
	}
	SafeDelete(pBinReader);
}
