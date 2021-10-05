#pragma once
#include "EngineBase.h"
#include "Basics.h"
#include "SDL_Extras.h"
#include "FontMap.h"

class ChaosTris :
    public EngineBase
{
public:	
	ChaosTris();

	bool EngineBase::OnInit(SDL_Renderer* rend, SDL_Window* win);
	bool OnInitA(SDL_Renderer* rend, SDL_Window* win, FontMap chrmap);
	void EngineBase::OnEvent(SDL_Event* Event);
	int EngineBase::OnExecute();
	void EngineBase::OnLoop();
	void EngineBase::OnRender();
	void EngineBase::OnCleanup();
	void EngineBase::OnExit();
	void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod);
	void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod);

private:
	vector<SDL_Point> _points;
	SDL_Point _lastTarget;
	SDL_Point _newTarget;
	FontMap _chrMap;

protected:

};

