#pragma once
#include "EngineBase.h"
#include "Basics.h"
#include "FontMap.h"

extern float Sintable[SINTABSIZE];
extern float Costable[SINTABSIZE];

class TextScroller
{
public:
	TextScroller();

	SDL_Rect DisplayRect;
	bool	 GotRenderItems = false;

	void OnInit(SDL_Renderer* rend, string msg, FontMap fontMap, SDL_Color clr, Uint16 speed, SDL_Rect dispRect);
	void OnLoop(void);
	void OnRender(void);
	void OnCleanUp(void);
	void OnReset(void);
	void SetSinusSize(float size);

private:

protected:
	string _theMessage;
	Sint16 _speed;
	float _sinSize=24.0;
	CharacterTextureMap _charMap;
	SDL_Renderer* _rend;
	FontMap _fontMap;
	SDL_Color _fontColor = { 0, 0, 0, 255 };
	int _currentPosition=0;
	list<CharItem> _screenItems;
	Uint16 _lastItemWidth;
	Uint16 _charIndex;
	int _repeatPause = 4 * GlobalFrameRate;
	
		
};

