#include "Basics.h"



class MainApplication : public EngineBase
{

public:
	MainApplication();
	SDL_Joystick* GamePad = NULL;
	bool AppIsRunning = true;
	bool EngineBase::OnInit(SDL_Renderer *rend, SDL_Window *win);
	void EngineBase::OnEvent(SDL_Event* Event);
	int EngineBase::OnExecute();
	void EngineBase::OnLoop();
	void EngineBase::OnRender();
	void EngineBase::OnCleanup();
	void EngineBase::OnExit();

	void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod);
	void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod);

private:
	Uint32 _frameCounter;
	TTF_Font* _font;
	Mix_Music* tune[3];
	Uint16 _actiTune=0;
	Uint16 _initPause = 0 * GlobalFrameRate;
	Uint16 _demoPart = 0;
};