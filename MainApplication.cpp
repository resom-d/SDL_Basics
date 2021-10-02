#include "Rotator.h"
#include "Starfield.h"
#include "MainApplication.h"
#include "TextScroller.h"
#include "SDL_Extras.h"

Rotator theRotator;
Starfield theStarfield;
TextScroller theScroller;

CharacterTextureMap CharMap;

float Sintable[SINTABSIZE];
float Costable[SINTABSIZE];
//string s = "Hello, SDL!";

int main(int argc, char* argv[]) {

	MainApplication theApp;

	if (theApp.OnInit())
	{
		return theApp.OnExecute();
	}
	else return -1;
}

MainApplication::MainApplication()
{
	WindowFrame.w = 1600;
	WindowFrame.h = 900;
	WindowFrame.x = 50;
	WindowFrame.y = 50;

}

bool MainApplication::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}

	int r = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	int flags = MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3;

	if (SDL_NumJoysticks() > 0) GamePad = SDL_JoystickOpen(0);

	if ((AppWindow = SDL_CreateWindow(
		"Hank's Playground",
		WindowFrame.x,
		WindowFrame.y,
		WindowFrame.w,
		WindowFrame.h,
		SDL_WINDOW_HIDDEN)
		) == nullptr) return false;

	if ((Renderer = SDL_CreateRenderer(AppWindow, -1, SDL_RENDERER_ACCELERATED)) == nullptr) return false;

	// Create a texure map from a string 
	_font = TTF_OpenFont("Resources/fonts/segoeui.ttf", 48);
	CharMap = SDL_GetTexturesFromString(Renderer, " 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖÜßabcdefghijklmnopqrstuvwxyzäöü,.;:*#-_|<>^°?=()!\"§$%&/()@€~", _font, { 0,0,0, 255 });

	double alpha = 0.0;
	for (int i = 0; i < SINTABSIZE; i++)
	{
		Sintable[i] = (float)sin(alpha * M_PI / 180.0);
		Costable[i] = (float)cos(alpha * M_PI / 180.0);
		alpha += 0.5f;
	}

	theRotator = Rotator(Renderer, WindowFrame);
	theRotator.OnInit();
	theStarfield = Starfield(Renderer, WindowFrame);
	theStarfield.OnInit();

	string s = "Hank Van Bastard presents:                                                                  A Galactic Geometry Show.                                                                                                               \
Ain't math beautiful? A simple polygon, some colors and a little M*A*T*H.                                               \
Right now this piece of code uses (mathematically) 2D scaling, rotation and translation. That's it.                                                                       \
Hank used the following  tools to create this ride:   Visual Studio Community,  GeoGebra,  Git, Gimp, Inkscape.                                                 \
And of course in this case specifically the SDL-Library.                                                     \
All these great tools are free software.    Thanks for the excellent stuff dudes - it's very much appreciated.                                                             \
Idea and coding: Hank.                                                  Music: 'TheSecret' by Hank.                                                               \
In case you'd like to contact the world's greatest bastard, send a message to                                      'hankvanbastard@gmail.com'                                                              \
Remember:    a bastard's work is never done.";


	SDL_Rect dRect = { 200, WindowFrame.h - 200, WindowFrame.w - 400, 200 };
	theScroller.OnInit(Renderer, s, _font, { 255, 255, 255, 255 }, 6, dRect);

#ifdef MUSIC
	tune[0] = Mix_LoadMUS("Resources/music/TheSecret.ogg");	
#endif

	SDL_ShowWindow(AppWindow);

	return true;
}

void MainApplication::OnEvent(SDL_Event* Event)
{
	SDL_Event anEvent;
	while (SDL_PollEvent(&anEvent) && AppIsRunning)
	{
		switch (anEvent.type)
		{
		case SDL_QUIT:
			AppIsRunning = false;
			break;
		}
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
		while (SDL_PollEvent(&AppEvent)) OnEvent(&AppEvent);

		// execute all logic
		OnLoop();
		// do all rendering
		OnRender();

		// make sure we are running at a constant frame rate
		timerFPS_n = SDL_GetTicks();
		timeDiff = timerFPS_n - timerFPS_1n;
		if (timeDiff < 1000 / GlobalFrameRate) SDL_Delay((1000 / GlobalFrameRate) - timeDiff);

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
		theRotator.OnLoop();

#ifdef MUSIC
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(tune[_actiTune++ % 1], 1);
		}
#endif
	}
	theScroller.OnLoop();
}

void MainApplication::OnRender()
{
	SDL_Color c = { 0,0,0,255 };
	SDL_Rect srect;
	srect.x = 0;
	srect.y = 0;
	srect.w = WindowFrame.w;
	srect.h = WindowFrame.h;

	SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(Renderer, c.r, c.g, c.b, 255);
	//SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_NONE);
	SDL_RenderSetClipRect(Renderer, nullptr);
	// clear Target
	SDL_RenderClear(Renderer);
	// black background
	SDL_RenderFillRect(Renderer, &srect);

	theStarfield.OnRender();
	if (_initPause > 0)
	{
		_initPause--;
	}
	else
	{
		theRotator.OnRender();
	}
	theScroller.OnRender();

	SDL_RenderPresent(Renderer);
}

void MainApplication::OnCleanup()
{
	Mix_Quit();
	theStarfield.OnCleanup();
	theRotator.OnCleanup();
	theScroller.OnCleanUp();
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
