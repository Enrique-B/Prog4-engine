#pragma once
#include "Singleton.h"
#include <map>
class TextureComponent;
struct SDL_Texture;

class Font;
namespace Fried
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		SDL_Texture* LoadTexture(const std::string& file);

		Font* LoadFont(const std::string& file, unsigned int size);
		~ResourceManager();
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_DataPath;
		std::map<std::string, SDL_Texture*> m_pTextureMap;
		std::map <std::pair<std::string, unsigned int>, Font* > m_pFontMap;
	};
}