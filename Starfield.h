#pragma once
#include "EngineBase.h"
#include "Basics.h"

class Starfield : public EngineBase
{
public:
	Starfield();
	Starfield(SDL_Renderer* rend, SDL_FRect winFrame);

	bool EngineBase::OnInit();
	void EngineBase::OnEvent(SDL_Event* Event);
	int EngineBase::OnExecute();
	void EngineBase::OnLoop();
	void EngineBase::OnRender();
	void EngineBase::OnCleanup();
	void EngineBase::OnExit();
	void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod);
	void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod);

private:
	SDL_Renderer* _renderer = nullptr;
	SDL_FRect _windowFrame;
	static const  Uint16 _noStars = 196;
	static const  Uint16 _noStarKinds = 5;
	SDL_Color _starColors[_noStarKinds] = {
		{255,0,0,255},
		{0,255,255,255},
		{200,255,55,255},
		{255,160,200,255},
		{255,255,255,255},
	};
	Uint16 _starSpeed[_noStarKinds]=
	{
		1,2,4,6,8
	};

	float _randomSeed;

	SDL_Point **_stars;// [_noStarKinds] [_noStars] ;

};

