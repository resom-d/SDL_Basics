#include "Starfield.h"

Starfield::Starfield()
{
}

Starfield::Starfield(SDL_Renderer* rend, SDL_FRect winFrame)
{
	
}

bool Starfield::OnInit(SDL_Renderer* rend, SDL_Window* win)
{
	srand(time(0));
	_renderer = rend;
	_window = win;
	SDL_GetWindowSize(_window, &_windowFrame.w, &_windowFrame.h);

	_stars = (SDL_Point**)SDL_malloc(_noStarKinds * sizeof(SDL_Point*));
	for (int i = 0; i < _noStarKinds; i++)
	{
		_stars[i] = (SDL_Point*)SDL_malloc(_noStars * sizeof(SDL_Point));
	}


	for (int i = 0; i < _noStarKinds; i++)
	{
		for (int j = 0; j < _noStars; j++)
		{
			_stars[i][j].x = (rand() % (int)_windowFrame.w) - _windowFrame.w; // start left outside of display
			_stars[i][j].y = rand() % (int)_windowFrame.h;
		}
	}
	return true;
}

int Starfield::OnExecute()
{
	return 1;
}

void Starfield::OnEvent(SDL_Event* event)
{

}

void Starfield::OnLoop()
{
	for (int i = 0; i < _noStarKinds; i++)
	{
		for (int j = 0; j < _noStars; j++)
		{
			_stars[i][j].x += _starSpeed[i];
			if (_stars[i][j].x > _windowFrame.w)
			{
				_stars[i][j].x = 0;
			}
		}
	}
}

void Starfield::OnRender()
{
	SDL_Color c;
	Uint16 coldiff = 255 / _noStarKinds;

	for (int i = 0; i < _noStarKinds; i++)
	{
		c = _starColors[i];
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i+1)*coldiff);
		for (int j = 0; j < _noStars; j++)
		{
			SDL_RenderDrawPoint(_renderer, _stars[i][j].x, _stars[i][j].y);
		}
	}
}

void Starfield::OnCleanup()
{
	/*for (int i = 0; i < _noStarKinds;i++)
	{
		free(_stars[i]);
	}*/
	//free((SDL_Point**)_stars);
}

void Starfield::OnExit()
{
}
void Starfield::OnKeyDown(SDL_Keycode sym, SDL_Keycode mod)
{
}

void Starfield::OnKeyUp(SDL_Keycode sym, SDL_Keycode mod)
{
}
