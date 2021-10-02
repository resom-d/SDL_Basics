#include "Starfield.h"

Starfield::Starfield()
{
}

Starfield::Starfield(SDL_Renderer* rend, SDL_FRect winFrame)
{
	_windowFrame.w = winFrame.w;
	_windowFrame.h = winFrame.h;;
	_windowFrame.x = winFrame.x;
	_windowFrame.y = winFrame.y;

	_renderer = rend;

}

bool Starfield::OnInit()
{
	srand(time(0));

	for (int i = 0; i < _noStarKinds; i++)
	{
		for (int j = 0; j < _noStars; j++)
		{
			_stars[i][j].x = rand() % (int)_windowFrame.w;
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
			if (_stars[i][j].x > (int)_windowFrame.w)
			{
				_stars[i][j].x = 0;
			}
		}
	}
}

void Starfield::OnRender()
{
	for (int i = 0; i < _noStarKinds; i++)
	{
		SDL_Color c = _starColors[i];
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
		for (int j = 0; j < _noStars; j++)
		{
			SDL_RenderDrawPoint(_renderer, _stars[i][j].x, _stars[i][j].y);
		}
	}
}

void Starfield::OnCleanup()
{

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
