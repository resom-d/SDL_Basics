#pragma once
#include<SDL.h>
#include<iostream>

using namespace::std;

extern float Sintable[SINTABSIZE];
extern float Costable[SINTABSIZE];

struct  _polygon_2D{
	SDL_FPoint* Points;
	SDL_FPoint* PointsBuffer;
	unsigned short CountP;
	SDL_FPoint LocalOriginP;
	SDL_Rect BoundingBox;
};
typedef struct _polygon_2D Polygon2D;


static void RotatePoints2D(SDL_FPoint* oldPoints, SDL_FPoint* newPoints, const  int count, SDL_FPoint orgP, int alpha)
{
	SDL_FPoint oldP;
	alpha = alpha % SINTABSIZE;

	for (int p = 0; p < count; p++)
	{
		newPoints[p].x = oldP.x = oldPoints[p].x - orgP.x;
		newPoints[p].y = oldP.y = oldPoints[p].y - orgP.y;

		newPoints[p].x = (oldP.x * Costable[alpha]) - (oldP.y * Sintable[alpha]);
		newPoints[p].y = (oldP.x * Sintable[alpha]) + (oldP.y * Costable[alpha]);

		newPoints[p].x += orgP.x;
		newPoints[p].y += orgP.y;

	}

}

static void ScalePoints2D(SDL_FPoint* oldPoints, SDL_FPoint* newPoints, const  int count, SDL_FPoint orgP, double scaleX, double scaleY)
{
	SDL_FPoint oldP;


	for (int p = 0; p < count; p++)
	{
		newPoints[p].x = oldP.x = oldPoints[p].x - orgP.x;
		newPoints[p].y = oldP.y = oldPoints[p].y - orgP.y;

		newPoints[p].x *= scaleX;
		newPoints[p].y *= scaleY;

		newPoints[p].x += orgP.x;
		newPoints[p].y += orgP.y;

	}

}

static void TranslatePoints2D(SDL_FPoint* oldPoints, SDL_FPoint* newPoints, const  int count, SDL_FPoint offP)
{
	for (int p = 0; p < count; p++)
	{
		newPoints[p].x = oldPoints[p].x + offP.x;
		newPoints[p].y = oldPoints[p].y + offP.y;
	}
}

static void DrawPolygon2D(SDL_Renderer* rend, SDL_FPoint* points, unsigned short count, bool closed)
{
	for (int l = 0; l < count - 1; l++)
	{
		SDL_RenderDrawLineF(rend, points[l].x, points[l].y, points[l + 1].x, points[l + 1].y);
	}
	if (closed)
	{
		SDL_RenderDrawLineF(rend, points[count - 1].x, points[count - 1].y, points[0].x, points[0].y);
	}
}

static void GetPolygon2DBoundingBox(Polygon2D* poly)
{
	float minX = poly->Points[0].x, maxX = poly->Points[0].x, minY = poly->Points[0].y, maxY = poly->Points[0].y;
	
	for (int i = 1; i < poly->CountP; i++)
	{
		minX = std::min(minX, poly->Points[i].x);
		maxX = std::max(maxX, poly->Points[i].x);
		minY = std::min(minY, poly->Points[i].y);
		maxY = std::max(maxY, poly->Points[i].y);
	}
	poly->BoundingBox.x = minX;
	poly->BoundingBox.y = minY;
	poly->BoundingBox.w = maxX - minX + 1;
	poly->BoundingBox.h = maxY - minY + 1;
	poly->LocalOriginP.x = minX + poly->BoundingBox.w / 2;
	poly->LocalOriginP.y = minY + poly->BoundingBox.h / 2;

}