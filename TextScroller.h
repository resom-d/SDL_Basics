#pragma once
#include "Basics.h"

extern float Sintable[SINTABSIZE];
extern float Costable[SINTABSIZE];

typedef struct CharItem
{
	char Content;
	Uint16 Width;
	Uint16 Height;
	SDL_Point ScreenPos;
	SDL_Texture* Texture;
};

class TextScroller
{
public:
	TextScroller();

	SDL_Rect DisplayRect;
	bool	 GotRenderItems = false;

	void OnInit(SDL_Renderer* rend, string msg, TTF_Font* font, SDL_Color clr, Uint16 speed, SDL_Rect dispRect);
	void OnLoop(void);
	void OnRender(void);
	void OnCleanUp(void);
	void OnReset(void);

private:

protected:
	string _theMessage;
	Sint16 _speed;
	CharacterTextureMap _charMap;
	SDL_Renderer* _rend;
	TTF_Font *_font;
	SDL_Color _fontColor = { 0, 0, 0, 255 };
	int _currentPosition=0;
	list<CharItem> _screenItems;
	Uint16 _lastItemWidth;
	Uint16 _charIndex;
	int _repeatPause = 4 * GlobalFrameRate;
	
		
};

