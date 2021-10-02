#include "Pointlist2D.h"

Pointlist2D::Pointlist2D()
{
	_geometry = vector<SDL_FPoint>();
	_points = vector<SDL_FPoint>();
}

Pointlist2D::Pointlist2D(SDL_FPoint* points, Uint16 count)
{
	_geometry = vector<SDL_FPoint>();
	_points = vector<SDL_FPoint>();

	for (int i = 0; i < count; i++)
	{
		SDL_FPoint p = { points[i].x, points[i].y };
		_geometry.push_back(points[i]);
		_points.push_back(p);
	}
	BringHome();
}

Pointlist2D::~Pointlist2D()
{
	_geometry.clear();
	_points.clear();
}

void Pointlist2D::AppendPoints(SDL_FPoint* newPoints, Uint16 count)
{
	for (int i = 0; i < count; i++)
	{
		_geometry.push_back(newPoints[i]);
	}
	BringHome();
}

void Pointlist2D::DeletePointsAt(Uint16 start, Uint16 stop)
{
}

void Pointlist2D::ScalePoints(bool fromSource, SDL_FPoint orgP, float scaleX, float scaleY)
{
	size_t  size = _geometry.size();

	if (fromSource)
	{
		for (auto p = 0; p < size; p++)
		{
			_points[p].x = _geometry[p].x - orgP.x;
			_points[p].y = _geometry[p].y - orgP.y;

			_points[p].x *= scaleX;
			_points[p].y *= scaleY;

			_points[p].x += orgP.x;
			_points[p].y += orgP.y;
		}
	}
	else
	{
		for (auto p = 0; p < size; p++)
		{
			_points[p].x = _points[p].x - orgP.x;
			_points[p].y = _points[p].y - orgP.y;

			_points[p].x *= scaleX;
			_points[p].y *= scaleY;

			_points[p].x += orgP.x;
			_points[p].y += orgP.y;
		}
	}

}

void Pointlist2D::RotatePoints(bool fromSource, SDL_FPoint orgP, int alpha)
{
	SDL_FPoint oldP;
	size_t  size = _geometry.size();
	alpha = alpha % SINTABSIZE;
		
	if (fromSource)
	{
		for (auto p = 0; p < size; p++)
		{
			oldP.x = _geometry[p].x - orgP.x;
			oldP.y = _geometry[p].y - orgP.y;

			_points[p].x = (oldP.x * Costable[alpha]) - (oldP.y * Sintable[alpha]);
			_points[p].y = (oldP.x * Sintable[alpha]) + (oldP.y * Costable[alpha]);

			_points[p].x += orgP.x;
			_points[p].y += orgP.y;

		}
	}
	else
	{
		for (auto p = 0; p < size; p++)
		{
			oldP.x = _points[p].x - orgP.x;
			oldP.y = _points[p].y - orgP.y;

			_points[p].x = (oldP.x * Costable[alpha]) - (oldP.y * Sintable[alpha]);
			_points[p].y = (oldP.x * Sintable[alpha]) + (oldP.y * Costable[alpha]);

			_points[p].x += orgP.x;
			_points[p].y += orgP.y;

		}
	}

	

}

void Pointlist2D::TranslatePoints(bool fromSource, SDL_FPoint offP)
{
	size_t  size = _geometry.size();
	
	if (fromSource)
	{
		for (auto p = 0; p < size; p++)
		{
			_points[p].x = _geometry[p].x + offP.x;
			_points[p].y = _geometry[p].y + offP.y;
		}
	}
	else
	{
		for (auto p = 0; p < size; p++)
		{
			_points[p].x = _points[p].x + offP.x;
			_points[p].y = _points[p].y + offP.y;
		}
	}	
	CentreOfRotation.x = offP.x;
	CentreOfRotation.y = offP.y;
}

void Pointlist2D::DrawPolygon(SDL_Renderer* rend, bool closed)
{
	size_t size = _points.size();
	for (auto l = 0; l < size - 1; l++)
	{
		SDL_RenderDrawLineF(rend, _points[l].x, _points[l].y, _points[l + 1].x, _points[l + 1].y);
	}
	if (closed)
	{
		SDL_RenderDrawLineF(rend, _points[size - 1].x, _points[size - 1].y, _points[0].x, _points[0].y);
	}
}

void Pointlist2D::BringHome()
{
	float minX = _geometry[0].x, maxX = _geometry[0].x, minY = _geometry[0].y, maxY = _geometry[0].y;

	auto size = _geometry.size();
	
	setBoundingBox();
	for (auto l = 0; l < size; l++)
	{
		_geometry[l].x -= CentreOfRotation.x;
		_geometry[l].y -= CentreOfRotation.y;
	}
	setBoundingBox();
}

void Pointlist2D::setBoundingBox()
{
	float minX = _geometry[0].x, maxX = _geometry[0].x, minY = _geometry[0].y, maxY = _geometry[0].y;

	for (int i = 1; i < _geometry.size(); i++)
	{
		minX = std::min(minX, _geometry[i].x);
		maxX = std::max(maxX, _geometry[i].x);
		minY = std::min(minY, _geometry[i].y);
		maxY = std::max(maxY, _geometry[i].y);
	}
	BoundingBox.x = minX;
	BoundingBox.y = minY;
	BoundingBox.w =maxX - minX ;
	BoundingBox.h = maxY - minY;
	CentreOfRotation.x = minX + BoundingBox.w / 2;
	CentreOfRotation.y = minY + BoundingBox.h / 2;
}
