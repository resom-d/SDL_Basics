#include "Rotator.h"
#include "GeometryF.h"

Rotator::Rotator()
{
}

Rotator::Rotator(SDL_Renderer* rend, SDL_FRect winFrame)
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
	_hexagonP[0] = {
		_windowFrame.w / 2 - 100,
		_windowFrame.h / 2 - 200 };
	_hexagonP[1] = {
		_windowFrame.w / 2 + 100,
		_windowFrame.h / 2 - 200 };
	_hexagonP[2] = {
		_windowFrame.w / 2 + 200,
		_windowFrame.h / 2 - 0 };
	_hexagonP[3] = {
		_windowFrame.w / 2 + 100,
		_windowFrame.h / 2 + 200 };
	_hexagonP[4] = {
	_windowFrame.w / 2 - 100,
	_windowFrame.h / 2 + 200 };
	_hexagonP[5] = {
		_windowFrame.w / 2 - 200,
		_windowFrame.h / 2 - 0 };

	_rotationV = 0;

//	_hexagon = Pointlist2D(_hexagonP, 6);
	_starfigure = Pointlist2D(_starFigureP, 16);

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
	_frameCounter += 4;

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
	_rotationV2 = _frameCounter % 720;

	if (_framePause > 0) {
		_framePause--;
	}
	else
	{
		_scaleVY += _zoomX;
		_scaleVX += _zoomX;

		if (_scaleVX > 6.0)
		{
			_zoomX *= -1;
			_framePause = 4 * GlobalFrameRate;
		}
		if (_scaleVX < 0.4)
		{
			_zoomX *= -1;
			_framePause = 2 * GlobalFrameRate;
		}

	}
};

void Rotator::OnRender()
{
	SDL_FPoint fp = { _windowFrame.w / 2, _windowFrame.h / 2 };
	SDL_FPoint rp = { _windowFrame.w / 2, _windowFrame.h / 2 };
	SDL_Color c = { 255,220,200,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, 255);
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderSetClipRect(_renderer, nullptr);
	SDL_RenderClear(_renderer);
	SDL_RenderFillRect(_renderer, nullptr);

	c = { 0,0,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, _rotationV);
	_starfigure.ScalePoints(false, fp, 80*_scaleVX,80*_scaleVY);
	for (int i = 0; i < 10;i++)
	{
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, 0.6, 0.6);
	}	
	c = { 0,0,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE- _rotationV)%SINTABSIZE);
	_starfigure.ScalePoints(false, fp, 80 * _scaleVX, 80 * _scaleVY);
	for (int i = 0; i < 10; i++)
	{
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, 0.7, 0.7);
	}
	

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
