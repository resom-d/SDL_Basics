#include "Pointlist2D.h"

Pointlist2D::Pointlist2D()
{
	Geometry = vector<SDL_FPoint>();
	Points = vector<SDL_FPoint>();
}

Pointlist2D::Pointlist2D(SDL_FPoint* points, Uint16 count)
{
	Geometry = vector<SDL_FPoint>();
	Points = vector<SDL_FPoint>();

	for (int i = 0; i < count; i++)
	{
		SDL_FPoint p = { points[i].x, points[i].y };
		Geometry.push_back(points[i]);
		Points.push_back(p);
	}
	BringHome();
}

Pointlist2D::~Pointlist2D()
{
	Geometry.clear();
	Points.clear();
}

void Pointlist2D::AppendPoints(SDL_FPoint* newPoints, Uint16 count)
{
	for (int i = 0; i < count; i++)
	{
		Geometry.push_back(newPoints[i]);
	}
	BringHome();
}

void Pointlist2D::DeletePointsAt(Uint16 start, Uint16 stop)
{
}

void Pointlist2D::ScalePoints(bool fromSource, SDL_FPoint orgP, float scaleX, float scaleY)
{
	size_t  size = Geometry.size();

	if (fromSource)
	{
		for (auto p = 0; p < size; p++)
		{
			Points[p].x = Geometry[p].x - orgP.x;
			Points[p].y = Geometry[p].y - orgP.y;

			Points[p].x *= scaleX;
			Points[p].y *= scaleY;

			Points[p].x += orgP.x;
			Points[p].y += orgP.y;
		}
	}
	else
	{
		for (auto p = 0; p < size; p++)
		{
			Points[p].x -= orgP.x;
			Points[p].y -= orgP.y;

			Points[p].x *= scaleX;
			Points[p].y *= scaleY;

			Points[p].x += orgP.x;
			Points[p].y += orgP.y;
		}
	}
}

void Pointlist2D::RotatePoints(bool fromSource, SDL_FPoint orgP, int alpha)
{
	SDL_FPoint oldP;
	size_t  size = Geometry.size();
	alpha = alpha % SINTABSIZE;

	if (fromSource)
	{
		for (auto p = 0; p < size; p++)
		{
			oldP.x = Geometry[p].x - orgP.x;
			oldP.y = Geometry[p].y - orgP.y;

			Points[p].x = (oldP.x * Costable[alpha]) - (oldP.y * Sintable[alpha]);
			Points[p].y = (oldP.x * Sintable[alpha]) + (oldP.y * Costable[alpha]);

			Points[p].x += orgP.x;
			Points[p].y += orgP.y;

		}
	}
	else
	{
		for (auto p = 0; p < size; p++)
		{
			oldP.x = Points[p].x - orgP.x;
			oldP.y = Points[p].y - orgP.y;

			Points[p].x = (oldP.x * Costable[alpha]) - (oldP.y * Sintable[alpha]);
			Points[p].y = (oldP.x * Sintable[alpha]) + (oldP.y * Costable[alpha]);

			Points[p].x += orgP.x;
			Points[p].y += orgP.y;

		}
	}



}

void Pointlist2D::TranslatePoints(bool fromSource, SDL_FPoint offP)
{
	size_t  size = Geometry.size();

	if (fromSource)
	{
		for (auto p = 0; p < size; p++)
		{
			Points[p].x = Geometry[p].x + offP.x;
			Points[p].y = Geometry[p].y + offP.y;
		}
	}
	else
	{
		for (auto p = 0; p < size; p++)
		{
			Points[p].x = Points[p].x + offP.x;
			Points[p].y = Points[p].y + offP.y;
		}
	}
	CentreOfRotation.x = offP.x;
	CentreOfRotation.y = offP.y;
}

void Pointlist2D::ShearPoints(bool fromSource, float shearX, float shearY)
{
}

int Pointlist2D::DrawPolygon(SDL_Renderer* rend, Uint16 polyNo)
{
	Uint16 source = polyNo - 1;
	vector<Uint16> poly = Polygons[source];
	Uint16 polySize = poly.size();
	if (polySize % 2) return -1; // polygon corrupt (no. not even)
	Uint16 point = 0;
	SDL_FPoint p1, p2;

	while (point < polySize)
	{
		p1 = Points[poly[point++]];
		p2 = Points[poly[point++]];
		SDL_RenderDrawFLine(rend, p1, p2);
	}
	return 0;
}

void Pointlist2D::BringHome()
{
	float minX = Geometry[0].x, maxX = Geometry[0].x, minY = Geometry[0].y, maxY = Geometry[0].y;

	auto size = Geometry.size();

	setBoundingBox();
	for (auto l = 0; l < size; l++)
	{
		Geometry[l].x -= CentreOfRotation.x;
		Geometry[l].y -= CentreOfRotation.y;
	}
	setBoundingBox();
}

void Pointlist2D::setBoundingBox()
{
	float minX = Geometry[0].x, maxX = Geometry[0].x, minY = Geometry[0].y, maxY = Geometry[0].y;

	for (int i = 1; i < Geometry.size(); i++)
	{
		minX = std::min(minX, Geometry[i].x);
		maxX = std::max(maxX, Geometry[i].x);
		minY = std::min(minY, Geometry[i].y);
		maxY = std::max(maxY, Geometry[i].y);
	}
	BoundingBox.x = minX;
	BoundingBox.y = minY;
	BoundingBox.w = maxX - minX;
	BoundingBox.h = maxY - minY;
	CentreOfRotation.x = minX + BoundingBox.w / 2;
	CentreOfRotation.y = minY + BoundingBox.h / 2;
}
