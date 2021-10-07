#pragma once
#include "EngineBase.h"
#include "SDL_Extras.h"

class CheckerboardRotation :
    public EngineBase
{
public:
    CheckerboardRotation();

    bool EngineBase::OnInit(SDL_Renderer* rend, SDL_Window* win);
	void EngineBase::OnEvent(SDL_Event* Event);
	int EngineBase::OnExecute();
	void EngineBase::OnLoop();
	void EngineBase::OnRender();
	void EngineBase::OnCleanup();
	void EngineBase::OnExit();

private:
	SDL_Texture* _texMask;
	SDL_Texture* _texBackgnd;
	float _rotMask = 0.0;
	float _rotBackgnd = 0.0;
	float _rotBackgndSpeed = 0.4;
	SDL_Point _windowSize;

protected:

};

