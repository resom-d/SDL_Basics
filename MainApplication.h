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
	TTF_Font* _font;
	Mix_Music* tune[3];
	Uint16 _actiTune=0;
	float _rotMask = 0.0;
	float _rotMask2 = 0.0;
	float _rotBackgnd = 0.0;
	float _rotBackgnd2 = 0.0;
	Uint16 _level;
	int _timerCatchLevelDone;
	Uint32 _timeCatchChangeScreens;
	Uint16 _initPause = 10 * GlobalFrameRate;
	SDL_Texture* _texMask;
	SDL_Texture* _texBackgnd;
};