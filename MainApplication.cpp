#include "SDL_Extras.h"
#include "Rotator.h"
#include "Starfield.h"
#include "MainApplication.h"
#include "TextScroller.h"
#include "TextRoller.h"
#include "FontMap.h"
#include "CheckerboardRotation.h"
#include "Mesh3D.h"

FontMap FontmapSeqgoe;
Rotator theRotator;
Starfield theStarfield;
TextScroller theScroller;
//TextRoller theRoller;
CheckerboardRotation theChecker;
Mesh3D theBoxMesh;

float Sintable[SINTABSIZE];
float Costable[SINTABSIZE];
//string s = "Hello, SDL!";

int main(int argc, char* argv[]) {

	MainApplication theApp;
	SDL_Window* AppWindow = NULL;;
	SDL_Renderer* Renderer = NULL;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if ((AppWindow = SDL_CreateWindow(
		"Hank's Playground",
		50,
		50,
		1600,
		900,
		SDL_WINDOW_HIDDEN)
		) == nullptr) return false;

	if ((Renderer = SDL_CreateRenderer(AppWindow, -1, SDL_RENDERER_ACCELERATED)) == nullptr) return false;
	// init mixer audio
	int r = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	int flags = MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3;
	// init TTF 
	if (TTF_Init() == -1)
	{
		return false;
	}

	if (theApp.OnInit(Renderer, AppWindow))
	{
		return theApp.OnExecute();
	}
	else return -1;
}

MainApplication::MainApplication()
{

}

bool MainApplication::OnInit(SDL_Renderer* rend, SDL_Window* win)
{
	FGeometry3D geo = theBoxMesh.CreateBoxMesh(1.0);

	_window = win;
	_renderer = rend;

	SDL_GetWindowSize(_window, &_windowFrame.w, &_windowFrame.h);
	_windowFrame.w = 1600;
	_windowFrame.h = 900;
	_windowFrame.x = 50;
	_windowFrame.y = 50;

	// Create a texure map from a string 
	FontmapSeqgoe.OnInit(_renderer, "", "Resources/fonts/segoeui.ttf", { 255,255,255,255 }, 48);

	double alpha = 0.0;
	for (int i = 0; i < SINTABSIZE; i++)
	{
		Sintable[i] = sinf(alpha * M_PI / 180.0);
		Costable[i] = cosf(alpha * M_PI / 180.0);
		alpha += 0.5f;
	}

	theRotator.OnInit(_renderer, _window);
	theStarfield.OnInit(_renderer, _window);

	string s = "Hank Van Bastard presents:                                                                  A Galactic Geometry Show.                                                                                                               \
Ain't math beautiful? A simple polygon, some colors and a little M*A*T*H.                                               \
Right now this piece of code uses (mathematically) 2D scaling, rotation and translation. That's it.                                                                       \
Hank used the following  tools to create this ride:   Visual Studio Community,  GeoGebra,  Git, Gimp, Inkscape.                                                 \
And of course in this case specifically the SDL-Library.                                                     \
All these great tools are free software.    Thanks for the excellent stuff dudes - it's very much appreciated.                                                             \
Idea and coding: Hank.                                                  Music: 'TheSecret' by Hank.                                                               \
In case you'd like to contact the world's greatest bastard, send a message to                                      'hankvanbastard@gmail.com'                                                              \
Remember:    a bastard's work is never done.";


	SDL_Rect dRect = { 200, _windowFrame.h, _windowFrame.w - 400, 200 };
	theScroller.OnInit(_renderer, s, FontmapSeqgoe, { 255, 255, 255, 255 }, 6, dRect);
	theChecker.OnInit(_renderer, _window);

#ifdef MUSIC
	tune[0] = Mix_LoadMUS("Resources/music/TheSecret.ogg");
#endif

	SDL_ShowWindow(_window);
	return true;
}

void MainApplication::OnEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
	case SDL_QUIT:
		AppIsRunning = false;
		break;

	case SDL_KEYDOWN:
		if (((SDL_KeyboardEvent*)Event)->keysym.sym == SDLK_RIGHT)
		{
			if (_demoPart < 2) _demoPart++;
		}
		if (((SDL_KeyboardEvent*)Event)->keysym.sym == SDLK_LEFT)
		{
			if (_demoPart > 0)_demoPart--;
		}
		break;
	}
}

int MainApplication::OnExecute()
{
	SDL_Event AppEvent;
	int timeDiff;
	int timerFPS_n = SDL_GetTicks();
	int timerFPS_1n = SDL_GetTicks();

	while (AppIsRunning)
	{
		timerFPS_1n = SDL_GetTicks();

		//grab events	
		while (SDL_PollEvent(&AppEvent))
		{
			OnEvent(&AppEvent);
		}
		// execute all logic
		OnLoop();
		// do all rendering
		OnRender();
		//

		// make sure we are running at a constant frame rate
		timerFPS_n = SDL_GetTicks();
		timeDiff = timerFPS_n - timerFPS_1n;
		if (timeDiff < 1000 / GlobalFrameRate)
		{
			SDL_Delay((1000 / GlobalFrameRate) - timeDiff);
		}
	}

	// don't leave a messy place
	OnCleanup();

	return 0;

}

void MainApplication::OnLoop()
{
	theStarfield.OnLoop();
	if (_initPause > 0)
	{
		_initPause--;
	}
	else
	{
		if (_demoPart % 3 == 0) {
			theRotator.OnLoopPhase_1();
		}
		else if (_demoPart % 3 == 1) {
			theRotator.OnLoopPhase_2();
		}
		else if (_demoPart % 3 == 2) {
			theChecker.OnLoop();
		}
#ifdef MUSIC
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(tune[_actiTune++ % 1], 1);
		}
#endif
	}
	//theScroller.OnLoop();

	_frameCounter++;

}

void MainApplication::OnRender()
{
	SDL_Color c;
	if (_demoPart % 3 == 0 || _demoPart % 3 == 1) {
		c = { 0, 0, 0, 255 };
	}
	else if (_demoPart % 3 == 2) {
		c = { 0, 180, 255, 255 };
	}
	SDL_Rect srect;
	srect.x = 0;
	srect.y = 0;
	srect.w = _windowFrame.w;
	srect.h = _windowFrame.h;

	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, 255);
	SDL_RenderSetClipRect(_renderer, nullptr);
	// clear Target
	SDL_RenderClear(_renderer);
	// black background
	SDL_RenderFillRect(_renderer, &srect);

	if (_initPause > 0)
	{
		_initPause--;
	}
	else
	{
		if (_demoPart % 3 == 0) {
			theStarfield.OnRender();
			theRotator.OnRenderPhase_1();
		}
		else if (_demoPart % 3 == 1) {
			theStarfield.OnRender();
			theRotator.OnRenderPhase_2();
		}
		else if (_demoPart % 3 == 2) {
			theChecker.OnRender();
		}
	}

	//theScroller.OnRender();

	SDL_RenderPresent(_renderer);

}

void MainApplication::OnCleanup()
{
#ifdef MUSIC
	Mix_Quit();
#endif
	FontmapSeqgoe.OnCleanUp();
	theStarfield.OnCleanup();
	theRotator.OnCleanup();
	theScroller.OnCleanUp();
	theChecker.OnCleanup();
	Mix_FreeMusic(tune[0]);
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void MainApplication::OnExit()
{
}

void MainApplication::OnKeyDown(SDL_Keycode sym, SDL_Keycode mod)
{
}

void MainApplication::OnKeyUp(SDL_Keycode sym, SDL_Keycode mod)
{
}
