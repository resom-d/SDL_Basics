#include "Mesh3D.h"

Mesh3D::Mesh3D()
{

}

bool Mesh3D::OnInit(SDL_Renderer* rend, SDL_Window* win)
{
	_renderer = rend;
	_window = win;
	return true;
}

int Mesh3D::OnExecute()
{

	return 0;
}

void Mesh3D::OnLoop()
{
	_mesh.BoundingBox.Min.X;
}

void Mesh3D::OnRender()
{
}

void Mesh3D::OnCleanup()
{
}

void Mesh3D::OnExit()
{
}

void Mesh3D::OnEvent(SDL_Event* event)
{
}

void Mesh3D::SaleFPoints3D(list<FPoint3D> points, FPoint3D scale){}
void Mesh3D::RotateFPoints3D(list<FPoint3D> points, FPoint3D centreOfRot, FPoint3D rot){}
void Mesh3D::TranslateFPoints3D(list<FPoint3D> points, FPoint3D vec){}