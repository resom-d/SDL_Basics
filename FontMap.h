#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

using namespace boost::filesystem;
namespace trans = boost::geometry::strategy::transform;
using boost::geometry::dsv;
using namespace boost::geometry;
using namespace std;

typedef unordered_map<char, SDL_Texture*> CharacterTextureMap;

class FontMap
{
public:
	FontMap();


	bool OnInit(SDL_Renderer* rend, string initChars, const char* font, SDL_Color color, Uint16 size);
	SDL_Texture* GetTexture(char chr);
	bool OnCleanUp();
	int GetTexturesFromString(SDL_Renderer* rend, string aString, TTF_Font* font, SDL_Color color);
	void RenderStringAt(SDL_Renderer* rend, string text, SDL_Point p, Uint16 size, SDL_Rect* clipRect);

private:
	CharacterTextureMap _textureMap;
	SDL_Renderer* _renderer;
	TTF_Font* _font;
	SDL_Color _color;
	Uint16 _size;
	
};

