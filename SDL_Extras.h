#pragma once
#include "Basics.h"
#include "FontMap.h"

	void SDL_RenderSetPixel(SDL_Renderer* renderer, int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

	void SDL_RenderDrawCircle(SDL_Renderer* renderer, int n_cx, int n_cy, int radius, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

	void SDL_RenderFillCircle(SDL_Renderer* renderer, int cx, int cy, int radius, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);

	void SDL_RenderDrawBorder(SDL_Renderer* rend, SDL_Rect rect, Uint16 borderWidth, SDL_Color color);
	
	int SDL_RenderDrawFLine(SDL_Renderer* rend, SDL_FPoint p1, SDL_FPoint p2);
	
	int SDL_RenderSetDrawColor(SDL_Renderer* rend, SDL_Color col);
		
	void CreateWidgetTexture(SDL_Renderer* rend, string filePath, SDL_Texture* destTex, SDL_Rect srcRect, SDL_Rect destRect, double rot, SDL_RendererFlip flip);

	SDL_Texture* SDL_LoadTexture(SDL_Renderer* rend, path filename);

	list<string> SplitString(string sourceString, const char splitter);

	list<path> GetFilesInDirectory(path dir);