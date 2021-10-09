#include "Rotator.h"

Rotator::Rotator()
{
}


bool Rotator::OnInit(SDL_Renderer* rend, SDL_Window* win)
{
	_renderer = rend;
	_window = win;

	SDL_GetWindowSize(_window, &_windowFrame.w, &_windowFrame.h);
	_screenCenter = { (float)_windowFrame.w / 2, (float)_windowFrame.h / 2 };
	_hexagonP[0] = {
		(float)_windowFrame.w / 2 - 100,
		(float)_windowFrame.h / 2 - 200 };
	_hexagonP[1] = {
		(float)_windowFrame.w / 2 + 100,
		(float)_windowFrame.h / 2 - 200 };
	_hexagonP[2] = {
		(float)_windowFrame.w / 2 + 200,
		(float)_windowFrame.h / 2 - 0 };
	_hexagonP[3] = {
		(float)_windowFrame.w / 2 + 100,
		(float)_windowFrame.h / 2 + 200 };
	_hexagonP[4] = {
	(float)_windowFrame.w / 2 - 100,
	(float)_windowFrame.h / 2 + 200 };
	_hexagonP[5] = {
		(float)_windowFrame.w / 2 - 200,
		(float)_windowFrame.h / 2 - 0 };

	_starfigure = Pointlist2D(_starFigureP, 16);
	vector<Uint16> poly = { 0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,0 };
	_starfigure.Polygons.push_back(poly);
	vector<Uint16> poly2 = { 2,6,6,10,10,14,14,2 };
	_starfigure.Polygons.push_back(poly2);

	_scalePoint = { _screenCenter.x,_screenCenter.y };
	

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
	switch (_phase)
	{
	case 0:
		OnLoopPhase_1();
		break;

	case 1:
		OnLoopPhase_2();
		break;
	}
};

void Rotator::OnRender()
{
	switch (_phase)
	{
	case 0:
		OnRenderPhase_1();
		break;

	case 1:
		OnRenderPhase_2();
		break;
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

void Rotator::OnLoopPhase_1()
{
	_frameCounter++;

	_rotationP1[0] += 1;
	if (_rotationP1[0] >= SINTABSIZE)
	{
		_rotationP1[0] %= SINTABSIZE;
	}
	_rotationP1[1] += 2;
	if (_rotationP1[1] >= SINTABSIZE)
	{
		_rotationP1[1] %= SINTABSIZE;
	}
	_rotationP1[2] += 4;
	if (_rotationP1[2] >= SINTABSIZE)
	{
		_rotationP1[2] %= SINTABSIZE;
	}

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

}

void Rotator::OnLoopPhase_2()
{
	_noFiguresShown = 3;
	_rotationP2[0] += 1;
	if (_rotationP2[0] >= SINTABSIZE)
	{
		_rotationP2[0] %= SINTABSIZE;
	}
	_rotationP2[1] += 2;
	if (_rotationP2[0] >= SINTABSIZE)
	{
		_rotationP2[1] %= SINTABSIZE;
	}
	_rotationP2[2] += 3;
	if (_rotationP2[2] >= SINTABSIZE)
	{
		_rotationP2[2] %= SINTABSIZE;
	}

	_scalePoint.x += _vScalePoint.x;
	_scalePoint.y += _vScalePoint.y;
	if (_scalePoint.x > _screenCenter.x + 22.0 || _scalePoint.x < _screenCenter.x - 22.0)
	{
		_vScalePoint.x *= -1.0;
	}
	if (_scalePoint.y > _screenCenter.y + 9 || _scalePoint.y < _screenCenter.y - 9)
	{
		_vScalePoint.y *= -1.0;
	}

	if (_scalePause > 0)
	{
		_scalePause--;
	}
	else
	{
		_scale += _scaleInc;
	}
	if (_scale > 1.3)
	{
		_scale = 1.3;
		_scaleInc *= -1;
		_scalePause = 5 * GlobalFrameRate;
	}
	if (_scale < 1.000)
	{
		_scale = 1.0;
		_scaleInc *= -1;
		_scalePause = 10 * GlobalFrameRate;
	}
}

void Rotator::OnRenderPhase_1()
{
	SDL_FPoint rp = { _windowFrame.w / 2, _windowFrame.h / 2 };
	SDL_Color c;
	Uint16 colorScale = 255 / _noRepeats;

	c = { 255,255,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, _rotationP1[0]);
	_starfigure.ScalePoints(false, _screenCenter, 100 * _scaleVX, 100 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * colorScale);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}

	c = { 255,255,255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationP1[0]) % SINTABSIZE);
	_starfigure.ScalePoints(false, _screenCenter, 100 * _scaleVX, 100 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * colorScale);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}

	c = { 0,0,255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, _rotationP1[1]);
	_starfigure.ScalePoints(false, _screenCenter, 90 * _scaleVX, 90 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * colorScale);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	c = { 0,255,0,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationP1[1]) % SINTABSIZE);
	_starfigure.ScalePoints(false, _screenCenter, 90 * _scaleVX, 90 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * colorScale);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}

	c = { 255,0,0,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, _rotationP1[2]);
	_starfigure.ScalePoints(false, _screenCenter, 80 * _scaleVX, 80 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * colorScale);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	c = { 66, 224, 245,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationP1[2]) % SINTABSIZE);
	_starfigure.ScalePoints(false, _screenCenter, 80 * _scaleVX, 80 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * colorScale);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
}

void Rotator::OnRenderPhase_2()
{
	SDL_FPoint fp = { _windowFrame.w / 2, _windowFrame.h / 2 };
	SDL_FPoint rp = { _windowFrame.w / 2, _windowFrame.h / 2 };
	Uint16 colorScale = 255 / _noRepeats;
	SDL_Color c = { 255,255,255,255 };
	SDL_FPoint pointsM[16];

	c = { 255,255,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.ScalePoints(false, fp, _originalScale, _originalScale);
	_starfigure.RotatePoints(false, rp, _rotationP2[0]);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, min((i + 1) * colorScale, 255));
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.DrawPolygon(_renderer, 2);
		for (int p = 0; p < 16; p++)
		{
			pointsM[p].x = _starfigure.Points[p].x;
			pointsM[p].y = _starfigure.Points[p].y;
		}
		_starfigure.ScalePoints(false, _scalePoint, _scale, _scale);
		if (i < _noRepeats - 1) {
			for (int l = 0; l < 16; l++)
			{
				SDL_RenderDrawLineF(_renderer, pointsM[l].x, pointsM[l].y, _starfigure.Points[l].x, _starfigure.Points[l].y);
			}
		}
	}

	if (_noFiguresShown < 2) return;
	c = { 0,255,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.ScalePoints(false, fp, _originalScale, _originalScale);
	_starfigure.RotatePoints(false, rp, _rotationP2[1]);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, min((i + 1) * colorScale, 255));
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.DrawPolygon(_renderer, 2);
		_starfigure.ScalePoints(false, _scalePoint, _scale, _scale);
	}

	if (_noFiguresShown < 3) return;
	c = { 255,0,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.ScalePoints(false, fp, _originalScale, _originalScale);
	_starfigure.RotatePoints(false, rp, _rotationP2[2]);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, min((i + 1) * colorScale, 255));
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.DrawPolygon(_renderer, 2);
		_starfigure.ScalePoints(false, _scalePoint, _scale, _scale);
	}
}
