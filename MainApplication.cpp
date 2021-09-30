#include "Rotator.h"
#include "MainApplication.h"

Rotator theRotator;

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
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}
	
	int r = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
	if (SDL_NumJoysticks() > 0) GamePad = SDL_JoystickOpen(0);

	if ((AppWindow = SDL_CreateWindow(
		"Hank's Playground",
		WindowFrame.x,
		WindowFrame.y,
		WindowFrame.w,
		WindowFrame.h,
		SDL_WINDOW_SHOWN)
		) == nullptr) return false;

	if ((Renderer = SDL_CreateRenderer(AppWindow, -1, SDL_RENDERER_ACCELERATED)) == nullptr) return false;

	#ifdef MUSIC
	tune = Mix_LoadMUS("Resources\music\The impossible Mission.mp3");
	Mix_PlayMusic(tune, -1);
	#endif

	double alpha = 0.0;
	for (int i = 0; i < SINTABSIZE; i++)
	{
		Sintable[i] = sin(alpha * M_PI / 180.0);
		Costable[i] = cos(alpha * M_PI / 180.0);
		alpha += 0.5;
	}

	theRotator = Rotator(Renderer, WindowFrame);
	theRotator.OnInit();

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
	theRotator.OnLoop();
}

void MainApplication::OnRender()
{
	theRotator.OnRender();
}

void MainApplication::OnCleanup()
{
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
