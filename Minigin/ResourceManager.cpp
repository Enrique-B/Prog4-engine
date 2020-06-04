#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Renderer.h"
#include "TextureComponent.h"
#include "Font.h"

Fried::ResourceManager::~ResourceManager()
{
	for (auto& temp :m_pFontMap)
	{
		SafeDelete(temp.second);
	}
	for (auto& temp : m_pTextureMap)
	{
		SDL_DestroyTexture(temp.second);
	}
}

void Fried::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) 
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG) 
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0) 
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}	
	
	// initialize sdl_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		throw std::runtime_error(std::string("Failed MIX_DEFAULT_FORMAT: ") + Mix_GetError());
	}
}

SDL_Texture* Fried::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_DataPath + file;
	if (m_pTextureMap.find(fullPath) == m_pTextureMap.end())
	{
		SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance()->GetSDLRenderer(), fullPath.c_str());
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
		}
		m_pTextureMap[fullPath] = texture;
	}
	return m_pTextureMap[fullPath];
}

Font* Fried::ResourceManager::LoadFont(const std::string& file, unsigned int size)noexcept
{
	std::string fullPath = m_DataPath + file;
	std::pair<std::string, unsigned int>pair{ fullPath, size };
	if (m_pFontMap.find(pair) == m_pFontMap.end()) // if it's not in the map make a new Font pointer
	{
		Font* pTemp = new Font{ fullPath , size };
		m_pFontMap[pair] = pTemp;
	}
	return m_pFontMap[pair];
}


