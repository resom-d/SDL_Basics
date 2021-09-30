#pragma once
#include<SDL.h>
#include<vector>
#include "Basics.h"
using namespace std;

extern float Sintable[SINTABSIZE];
extern float Costable[SINTABSIZE];

class Pointlist2D
{
public:
	Pointlist2D();
	Pointlist2D(SDL_FPoint* points, Uint16 count);
	~Pointlist2D();

	SDL_FPoint CentreOfRotation;
	SDL_FRect BoundingBox;

	void AppendPoints(SDL_FPoint* newPoints, Uint16 count);
	void DeletePointsAt(Uint16 start, Uint16 stop);
	void ScalePoints(bool fromSource, SDL_FPoint orgP, float scaleX, float scaleY);
	void RotatePoints(bool fromSource, SDL_FPoint orgP, int alpha);
	void TranslatePoints(bool fromSource, SDL_FPoint offP);
	void DrawPolygon(SDL_Renderer* rend, bool closed);
	void BringHome();

private:
	vector<SDL_FPoint> _geometry;
	vector<SDL_FPoint> _points;

	void setBoundingBox();

protected:

};

