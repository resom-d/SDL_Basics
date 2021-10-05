#include "FontMap.h"

FontMap::FontMap()
{
}

bool FontMap::OnInit(SDL_Renderer* rend, string initChars, const char* font, SDL_Color color, Uint16 size)
{
	_renderer = rend;
	_font = TTF_OpenFont(font, size);
	_color = color;
	GetTexturesFromString(_renderer, initChars, _font, color);
	return true;
}

SDL_Texture* FontMap::GetTexture(const char chr)
{
	if (_textureMap[chr] != nullptr)
	{
		return _textureMap[chr];
	}
	else
	{
		char txt[2] = { chr, '\0' };
		SDL_Surface* surf = TTF_RenderText_Solid(_font, txt, _color);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(_renderer, surf);
		_textureMap.insert({ chr, tex });
		return tex;
	}
}

bool FontMap::OnCleanUp()
{
	for (auto item = _textureMap.begin(); item != _textureMap.end(); item++)
	{
		SDL_DestroyTexture(item->second);

	}
	return false;
}

int FontMap::GetTexturesFromString(SDL_Renderer* rend, string aString, TTF_Font* font, SDL_Color color)
{
	for (auto iter = aString.begin(); iter != aString.end(); iter++)
	{
		char c = *iter;
		if (_textureMap[c] == nullptr)
		{
			char txt[2] = { c, '\0' };
			SDL_Surface* surf = TTF_RenderText_Solid(font, txt, color);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surf);
			_textureMap.insert({ c, tex });
		}
	}

	return 1;
}

void FontMap::RenderStringAt(SDL_Renderer* rend, string text, SDL_Point p, Uint16 size, SDL_Rect* clipRect)
{
	SDL_Rect destRect{ p.x, p.y, 0,0 };
	SDL_Rect srcRect = { 0,0,0,0 };
	SDL_Texture* tex;
	char c;
	int w, h;
	SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
	SDL_RenderSetClipRect(rend, clipRect);
	for (auto iter = text.begin(); iter != text.end(); iter++)
	{
		c = *iter;
		tex = GetTexture(c);
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);

		destRect.w = w;
		destRect.h = h;
		srcRect = { 0,0,w,h };
		SDL_RenderCopy(rend, tex, &srcRect, &destRect);
		destRect.x += w;
	}
	SDL_RenderSetClipRect(rend, nullptr);
}
