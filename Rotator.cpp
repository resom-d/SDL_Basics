#include "Rotator.h"

Rotator::Rotator()
{
}

Rotator::Rotator(SDL_Renderer* rend, SDL_FRect winFrame)
{
	_windowFrame.w = winFrame.w;
	_windowFrame.h = winFrame.h;;
	_windowFrame.x = winFrame.x;
	_windowFrame.y = winFrame.y;

	_renderer = rend;
	
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
		_scaleVX += _zoomX;
		_scaleVY += _zoomX;
		if (_scaleVX > _scaleXMax || _scaleVX < _scaleXMin)
		{
			_zoomX *= -1;
			_framePause = 12 * GlobalFrameRate;
			if (_scaleVX < _scaleXMin)
				_noFigures++;
		}
	}

	if (_framePause1 > 0)
	{
		_framePause1--;
	}
	else
	{
		_scaleVX1 += _zoomX1;
		_scaleVY1 += _zoomX1;
		if (_scaleVX1 > 8.0 || _scaleVX1 < 0.6)
		{
			_zoomX1 *= -1;
			_framePause1 = 2 * GlobalFrameRate;
		}
	}
	if (_framePause2 > 0)
	{
		_framePause2--;
	}
	else
	{
		_scaleVX2 += _zoomX2;
		_scaleVY2 += _zoomX2;
		if (_scaleVX2 > 8.0 || _scaleVX2 < 0.6)
		{
			_zoomX2 *= -1;
			_framePause2 = 2 * GlobalFrameRate;
		}
	}
};

void Rotator::OnRender()
{
	SDL_FPoint fp = { _windowFrame.w / 2, _windowFrame.h / 2 };
	SDL_FPoint rp = { _windowFrame.w / 2, _windowFrame.h / 2 };
	
	SDL_Color c;
	c = { 255,255,0,20 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, _rotationV);
	_starfigure.ScalePoints(false, fp, 100 * _scaleVX, 100 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i+1)*63);
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}	
	c = { 255,255,255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationV) % SINTABSIZE);
	_starfigure.ScalePoints(false, fp, 100 * _scaleVX, 100 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	
	c = { 0,0,255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, _rotationV1);
	_starfigure.ScalePoints(false, fp, 90 * _scaleVX, 90 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i+1)*63);
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	c = { 0,255,0,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationV1) % SINTABSIZE);
	_starfigure.ScalePoints(false, fp, 90 * _scaleVX, 90 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}

	c = { 255,0,0,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, _rotationV2);
	_starfigure.ScalePoints(false, fp, 80 * _scaleVX, 80 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i+1)*63);
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	c = { 255,255, 255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationV2) % SINTABSIZE);
	_starfigure.ScalePoints(false, fp, 80 * _scaleVX, 80 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b,(i+1)*63);
		_starfigure.DrawPolygon(_renderer, true);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, 0.8);
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
