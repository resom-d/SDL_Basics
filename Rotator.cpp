#include "Rotator.h"
#include "GeometryF.h"

Rotator::Rotator()
{
}

Rotator::Rotator(SDL_Renderer* rend, SDL_Rect winFrame)
{
	_renderer = rend;
	_windowFrame.w = winFrame.w;
	_windowFrame.h = winFrame.h;;
	_windowFrame.x = winFrame.x;
	_windowFrame.y = winFrame.y;
}

bool Rotator::OnInit()
{
	model::d2::point_xy<double> po;
	_hexagon[0] = {
		_windowFrame.w / 2 - 100,
		_windowFrame.h / 2 - 200 };
	_hexagon[1] = {
		_windowFrame.w / 2 + 100,
		_windowFrame.h / 2 - 200 };
	_hexagon[2] = {
		_windowFrame.w / 2 + 200,
		_windowFrame.h / 2 - 0 };
	_hexagon[3] = {
		_windowFrame.w / 2 + 100,
		_windowFrame.h / 2 + 200 };
	_hexagon[4] = {
	_windowFrame.w / 2 - 100,
	_windowFrame.h / 2 + 200 };
	_hexagon[5] = {
		_windowFrame.w / 2 - 200,
		_windowFrame.h / 2 - 0 };
	
	_rotationV = 0;
	_originP = { _windowFrame.w / 2, _windowFrame.h / 2 };

	return true;
};

int Rotator::OnExecute()
{
	return 1;
};

void Rotator::OnEvent(SDL_Event* event)
{

};

void Rotator::OnLoop()
{
	_rotationV += 1;
	if (_rotationV >= SINTABSIZE)
	{
		_rotationV %= SINTABSIZE;
	}
	_rotationV1 += 2;
	if (_rotationV1 >= SINTABSIZE)
	{
		_rotationV1 %= SINTABSIZE;
	}
	_rotationV2 += 4;
	if (_rotationV2 >= SINTABSIZE)
	{
		_rotationV2 %= SINTABSIZE;
	}
	if (_framePause > 0) {
		_framePause--;
	}
	else
	{
		_scaleVY += _zoomX;
		_scaleVX += _zoomX;

		if (_scaleVX > 2.0 || _scaleVX < 0.4)
		{
			_zoomX *= -1;
			_framePause = 4 * GlobalFrameRate;
		}
	}

};

void Rotator::OnRender()
{
	_frameCounter++;

	SDL_Color c = { 255,220,200,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, 255);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetClipRect(_renderer, nullptr);
	SDL_RenderClear(_renderer);
	SDL_RenderFillRect(_renderer, nullptr);

	c = { 0,0,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b,c.a);
	ScalePoints2D(_hexagon, _hexagonBuf, 6, _originP, _scaleVX, _scaleVY);
	RotatePoints2D(_hexagonBuf, _hexagonBuf, 6, _originP, _rotationV);
	DrawPolygon2D(_renderer, _hexagonBuf, 6, true);

	c = { 255,0,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	ScalePoints2D(_hexagon, _hexagonBuf, 6, _originP, _scaleVX, _scaleVY);
	RotatePoints2D(_hexagonBuf, _hexagonBuf, 6, _originP, _rotationV1);
	DrawPolygon2D(_renderer, _hexagonBuf, 6, true);

	c = { 0,255,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	ScalePoints2D(_hexagon, _hexagonBuf, 6, _originP, _scaleVX, _scaleVY);
	RotatePoints2D(_hexagonBuf, _hexagonBuf, 6, _originP, _rotationV2);
	DrawPolygon2D(_renderer, _hexagonBuf, 6, true);


	// Hey, Renderer! Do it! Do it !
	SDL_RenderPresent(_renderer);

}

void Rotator::OnCleanup()
{

}

void Rotator::OnExit()
{
}

void Rotator::OnKeyDown(SDL_Keycode sym, SDL_Keycode mod)
{
}

void Rotator::OnKeyUp(SDL_Keycode sym, SDL_Keycode mod)
{
}
