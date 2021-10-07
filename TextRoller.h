#pragma once
#include "EngineBase.h"
#include "FontMap.h"

class TextRoller :
	public EngineBase
{
public:
	TextRoller();

	SDL_Rect DisplayRect;

	bool EngineBase::OnInit(SDL_Renderer* rend, SDL_Window* win);
	int EngineBase::OnExecute();
	void  EngineBase::OnLoop();
	void  EngineBase::OnRender();
	void  EngineBase::OnCleanup();
	void  EngineBase::OnExit();
	void  EngineBase::OnEvent(SDL_Event* Event);

private:
	FontMap _fontOne;
	Uint16 _fontSize = 36;
	list<CharItem> _screenItems;
	string _theMessage = "Democoding in 2021? Yes, 'cause it's fun and relaxing and enjoyable and beautiful and art as art can be.       Enjoy the show.                                 ";
	Sint16 _speed = 8;
	SDL_Color _fontColor = { 0, 0, 0, 255 };
	int _currentPosition = 0;
	Uint16 _lastItemHeight;
	Uint16 _charIndex;
	int _repeatPause = 0 * GlobalFrameRate;

protected:

};