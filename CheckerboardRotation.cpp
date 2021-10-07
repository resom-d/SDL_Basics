#include "CheckerboardRotation.h"

CheckerboardRotation::CheckerboardRotation()
{
}

bool CheckerboardRotation::OnInit(SDL_Renderer* rend, SDL_Window* win)
{
	_renderer = rend;
	_window = win;
	SDL_GetWindowSize(_window, &_windowSize.x, &_windowSize.y);

	_texMask = SDL_LoadTexture(_renderer, "Resources/graphics/checker.png");
	_texBackgnd = SDL_LoadTexture(_renderer, "Resources/graphics/spiral.png");

	return true;
}

int CheckerboardRotation::OnExecute()
{
	return 0;
}

void CheckerboardRotation::OnLoop()
{
	_rotMask += 0.05;
	_rotBackgnd += _rotBackgndSpeed;
	if (abs(_rotBackgnd) > 359.9)
	{
		_rotBackgnd = 0;
		_rotBackgndSpeed *= -1;

	}
}

void CheckerboardRotation::OnRender()
{
	int h, w;
	SDL_QueryTexture(_texMask, nullptr, nullptr, &w, &h);
	SDL_Rect drect = { -((w - _windowSize.x) / 2), -((h - _windowSize.y) / 2), w, h };
	SDL_RenderCopyEx(_renderer, _texBackgnd, nullptr, &drect, _rotBackgnd, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(_renderer, _texMask, nullptr, &drect, _rotMask, nullptr, SDL_FLIP_NONE);
	SDL_RenderCopyEx(_renderer, _texMask, nullptr, &drect, -_rotMask, nullptr, SDL_FLIP_NONE);
}

void CheckerboardRotation::OnCleanup()
{
	SDL_DestroyTexture(_texMask);
	SDL_DestroyTexture(_texBackgnd);
}

void CheckerboardRotation::OnExit()
{}

void CheckerboardRotation::OnEvent(SDL_Event* event)
{}