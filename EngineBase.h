#pragma once
#include <SDL.h>

using namespace std;

// Base class
class EngineBase{
public:
	// pure virtual function providing interface framework.
	virtual bool OnInit() = 0;
	virtual int OnExecute() = 0;
	virtual void OnLoop() = 0;
	virtual void OnRender() = 0;
	virtual void OnCleanup() = 0;
	virtual void OnExit() = 0;
	virtual void OnEvent(SDL_Event* Event) = 0;	

protected:

};