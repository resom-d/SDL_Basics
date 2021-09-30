#include "Basics.h"



class MainApplication : public EngineBase
{

public:
	MainApplication();
	SDL_FRect WindowFrame;
	SDL_Window* AppWindow = NULL;;
	SDL_Renderer* Renderer= NULL;
	SDL_Joystick* GamePad = NULL;
	bool AppIsRunning = true;
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
	TTF_Font* _font;
	Mix_Music* tune;
	Uint16 _level;
	int _timerCatchLevelDone;
	Uint32 _timeCatchChangeScreens;

};