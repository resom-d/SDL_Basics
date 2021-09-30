#pragma once
#include"Basics.h"


typedef struct _polygon2D {
	SDL_Point *Points;
	unsigned short CountP;
	SDL_Point LocalOriginP;
	SDL_Rect BoundingBox;

} Polygon2D;

double Sintable[SINTABSIZE];
double Costable[SINTABSIZE];

static void RotatePoints2D(SDL_Point* oldPoints, SDL_Point* newPoints,  const  int count, SDL_Point orgP, int alpha)
{
	SDL_Point oldP;
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

static void ScalePoints2D(SDL_Point* oldPoints, SDL_Point* newPoints, const  int count, SDL_Point orgP, double scaleX, double scaleY)
{
	SDL_Point oldP;
	

	for (int p = 0; p < count; p++)
	{
		newPoints[p].x = oldP.x = oldPoints[p].x - orgP.x;
		newPoints[p].y = oldP.y = oldPoints[p].y - orgP.y;

		newPoints[p].x *=  scaleX;
		newPoints[p].y *= scaleY;

		newPoints[p].x += orgP.x;
		newPoints[p].y += orgP.y;

	}

}

static void TranslatePoints2D(SDL_Point* oldPoints, SDL_Point* newPoints, const  int count, SDL_Point offP)
{	
	for (int p = 0; p < count; p++)
	{
		newPoints[p].x = oldPoints[p].x + offP.x;
		newPoints[p].y = oldPoints[p].y+ offP.y;
	}
}

static void DrawPolygon2D(SDL_Renderer* rend, SDL_Point* points, unsigned short count, bool closed)
{
	for (int l = 0; l < count-1; l++)
	{
		SDL_RenderDrawLine(rend, points[l].x, points[l].y,  points[l + 1].x,points[l + 1].y);
	}
	if (closed)
	{
		SDL_RenderDrawLine(rend, points[count-1].x, points[count-1].y, points[0].x, points[0].y);
	}
}

static void GetPolygon2DBoundingBox(Polygon2D* poly)
{
	int minX=poly->Points[0].x, maxX=poly->Points[0].x, minY = poly->Points[0].y, maxY = poly->Points[0].y;
	for (int i = 0; i < poly->CountP-1; i++)
	{
		minX = std::min(poly->Points[i].x, poly->Points[i+1].x);
		maxX = std::max(poly->Points[i].x, poly->Points[i+1].x);
		minY = std::min(poly->Points[i].y, poly->Points[i+1].y);
		maxY = std::max(poly->Points[i].y, poly->Points[i+1].y);
	}
	poly->BoundingBox.x = minX;
	poly->BoundingBox.y = minY;
	poly->BoundingBox.w = maxX - minX + 1;
	poly->BoundingBox.h = maxY - minY + 1;
	poly->LocalOriginP.x = minX + poly->BoundingBox.w / 2;
	poly->LocalOriginP.y = minY + poly->BoundingBox.h / 2;

}