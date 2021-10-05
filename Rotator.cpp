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

	_rotationV = 0;
	_scalePoint[0] = { _screenCenter.x,_screenCenter.y };
	_scalePoint[1] = { _screenCenter.x,_screenCenter.y };
	_scalePoint[2] = { _screenCenter.x,_screenCenter.y };
	_scalePoint[3] = { _screenCenter.x,_screenCenter.y };
	_vScalePoint[0] = { 0.5, 0.75 };
	_vScalePoint[1] = { -3.5, 3.5 };
	_vScalePoint[2] = { 4.5, -6.5 };
	_vScalePoint[3] = { -3.5, 4.5 };
	//	_hexagon = Pointlist2D(_hexagonP, 6);
	_starfigure = Pointlist2D(_starFigureP, 16);
	vector<Uint16> poly = { 0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,0 };
	_starfigure.Polygons.push_back(poly);
	vector<Uint16> poly2 = { 2,6,6,10,10,14,14,2 };
	_starfigure.Polygons.push_back(poly2);
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
}

void Rotator::OnLoopPhase_2()
{

	if (_frameCounter % (10 * GlobalFrameRate) == 0)
	{
		_noFiguresShown += _showFigureDir;
	}
	if (_noFiguresShown > 3)
	{
		_noFiguresShown = 2;
		_showFigureDir = -1;
	}
	if (_noFiguresShown < 1)
	{
		_noFiguresShown = 2;
		_showFigureDir = 1;
	}
	_frameCounter++;

	_noFiguresShown = 3;
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
	_rotationV2 += 3;
	if (_rotationV2 >= SINTABSIZE)
	{
		_rotationV2 %= SINTABSIZE;
	}

	for (int f = 0; f < 4; f++)
	{
		_scalePoint[f].x += _vScalePoint[f].x;
		_scalePoint[f].y += _vScalePoint[f].y;
		if (_scalePoint[f].x > _screenCenter.x + 20.0 || _scalePoint[f].x < _screenCenter.x - 20.0)
		{
			_vScalePoint[f].x *= -1.0;
		}
		if (_scalePoint[f].y > _screenCenter.y + 20 || _scalePoint[f].y < _screenCenter.y - 20)
		{
			_vScalePoint[f].y *= -1.0;
		}
	}

	if (_scalePause > 0)
	{
		_scalePause--;
	}
	else
	{
		_scale += _scaleInc;
		//_originalScale += _scale*_scale;
	}
	if (_scale >1.3)
	{
		_scale = 1.3;
		_scaleInc *= -1;
		_scalePause = 5 * GlobalFrameRate;
	}
	if(_scale < 1.000)
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
	c = { 255,255,0,20 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, _rotationV);
	_starfigure.ScalePoints(false, _screenCenter, 100 * _scaleVX, 100 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	c = { 255,255,255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationV) % SINTABSIZE);
	_starfigure.ScalePoints(false, _screenCenter, 100 * _scaleVX, 100 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}

	c = { 0,0,255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, _rotationV1);
	_starfigure.ScalePoints(false, _screenCenter, 90 * _scaleVX, 90 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	c = { 0,255,0,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationV1) % SINTABSIZE);
	_starfigure.ScalePoints(false, _screenCenter, 90 * _scaleVX, 90 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}

	c = { 255,0,0,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, _rotationV2);
	_starfigure.ScalePoints(false, _screenCenter, 80 * _scaleVX, 80 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, _repeatScale);
	}
	c = { 255,255, 255,25 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, _screenCenter);
	_starfigure.RotatePoints(false, rp, (SINTABSIZE - _rotationV2) % SINTABSIZE);
	_starfigure.ScalePoints(false, _screenCenter, 80 * _scaleVX, 80 * _scaleVY);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, (i + 1) * 63);
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.ScalePoints(false, _starfigure.CentreOfRotation, _repeatScale, 0.8);
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
	_starfigure.RotatePoints(false, rp, _rotationV);
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
		_starfigure.ScalePoints(false, _scalePoint[0], _scale, _scale);
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
	_starfigure.RotatePoints(false, rp, _rotationV1);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, min((i + 1) * colorScale, 255));
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.DrawPolygon(_renderer, 2);
		_starfigure.ScalePoints(false, _scalePoint[0], _scale, _scale);
	}

	if (_noFiguresShown < 3) return;
	c = { 255,0,0,255 };
	SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
	_starfigure.TranslatePoints(true, fp);
	_starfigure.ScalePoints(false, fp, _originalScale, _originalScale);
	_starfigure.RotatePoints(false, rp, _rotationV2);
	for (int i = 0; i < _noRepeats; i++)
	{
		SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, min((i + 1) * colorScale, 255));
		_starfigure.DrawPolygon(_renderer, 1);
		_starfigure.DrawPolygon(_renderer, 2);
		_starfigure.ScalePoints(false, _scalePoint[0], _scale, _scale);
	}


}
