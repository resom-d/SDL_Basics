#pragma once
#include<SDL.h>
#include<vector>
#include "Basics.h"
#include "SDL_Extras.h"

using namespace std;

extern float Sintable[SINTABSIZE];
extern float Costable[SINTABSIZE];

class Pointlist2D
{
public:
	Pointlist2D();
	Pointlist2D(SDL_FPoint* points, Uint16 count);
	~Pointlist2D();

	vector<SDL_FPoint> Geometry;
	vector<SDL_FPoint> Points;
	vector<vector<Uint16>> Polygons;
	SDL_FPoint CentreOfRotation;
	SDL_FRect BoundingBox;

	void AppendPoints(SDL_FPoint* newPoints, Uint16 count);
	void DeletePointsAt(Uint16 start, Uint16 stop);
	void ScalePoints(bool fromSource, SDL_FPoint orgP, float scaleX, float scaleY);
	void RotatePoints(bool fromSource, SDL_FPoint orgP, int alpha);
	void TranslatePoints(bool fromSource, SDL_FPoint offP);
	void ShearPoints(bool fromSource, float shearX, float shearY);
	int DrawPolygon(SDL_Renderer* rend, Uint16 polyNo);
	void BringHome();

private:
	void setBoundingBox();

protected:

};

