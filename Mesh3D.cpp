#include "Mesh3D.h"

Mesh3D::Mesh3D()
{

}

FGeometry3D Mesh3D::CreateBoxMesh(float size)
{
	FGeometry3D geo = FGeometry3D();

	geo.NoFace = 6;
	geo.NoEdge = 12;
	geo.NoVertex = 8;

	list<Uint16> face_1;
	list<Uint16> face_2;
	list<Uint16> face_3;
	list<Uint16> face_4;
	list<Uint16> face_5;
	list<Uint16> face_6;
	// 1st face (xy, front)
	face_1.push_back({ 0 });
	face_1.push_back({ 1 });
	face_1.push_back({ 2 });
	face_1.push_back({ 3 });
	geo.Faces.push_back(face_1);
	// 2nd face (xy, back)
	face_2.push_back({ 4 });
	face_2.push_back({ 5 });
	face_2.push_back({ 6 });
	face_2.push_back({ 7 });
	geo.Faces.push_back(face_2);
	// 3rd face (top)
	face_3.push_back({ 0 });
	face_3.push_back({ 9 });
	face_3.push_back({ 4 });
	face_3.push_back({ 8 });
	geo.Faces.push_back(face_3);
	// 4th face (bottom)
	face_4.push_back({ 3 });
	face_4.push_back({ 12 });
	face_4.push_back({ 7 });
	face_4.push_back({ 11 });
	geo.Faces.push_back(face_4);
	// 5th face (left)
	face_5.push_back({ 3 });
	face_5.push_back({ 10 });
	face_5.push_back({ 7 });
	face_5.push_back({ 8 });
	geo.Faces.push_back(face_5);
	// 6th face (right)
	face_6.push_back({ 1 });
	face_6.push_back({ 9 });
	face_6.push_back({ 5 });
	face_6.push_back({ 10 });
	geo.Faces.push_back(face_6);

	// edges 1st face 
	geo.Edges.push_back({ 0,1 });
	geo.Edges.push_back({ 1,2 });
	geo.Edges.push_back({ 2,3 });
	geo.Edges.push_back({ 3,0 });
	// edges 2nd face 
	geo.Edges.push_back({ 4,5 });
	geo.Edges.push_back({ 5,6 });
	geo.Edges.push_back({ 6,7 });
	geo.Edges.push_back({ 7,4 });
	// edges 3rd face 
	geo.Edges.push_back({ 0,4 });
	geo.Edges.push_back({ 4,4 });
	geo.Edges.push_back({ 5,1 });
	geo.Edges.push_back({ 1, 0 });
	// edges 4th face 
	geo.Edges.push_back({ 3,2 });
	geo.Edges.push_back({ 2,6 });
	geo.Edges.push_back({ 6,7 });
	geo.Edges.push_back({ 7, 3 });
	// edges 5th face 
	geo.Edges.push_back({ 0,4 });
	geo.Edges.push_back({ 4,7 });
	geo.Edges.push_back({ 7,3 });
	geo.Edges.push_back({ 3, 0 });
	// edges 6th face 
	geo.Edges.push_back({ 1,5 });
	geo.Edges.push_back({ 5,6 });
	geo.Edges.push_back({ 6,2 });
	geo.Edges.push_back({ 2, 1 });
	// points
	float halfSize = size * 0.5f;
	geo.Points.push_back({ -halfSize , -halfSize, -halfSize });
	geo.Points.push_back({ halfSize , -halfSize, -halfSize });
	geo.Points.push_back({ -halfSize , halfSize, -halfSize });
	geo.Points.push_back({ halfSize , halfSize, -halfSize });
	geo.Points.push_back({ -halfSize , -halfSize, halfSize });
	geo.Points.push_back({ halfSize , -halfSize, halfSize });
	geo.Points.push_back({ -halfSize , halfSize, halfSize });
	geo.Points.push_back({ halfSize , halfSize, halfSize });;

	geo.BoundingBox.Min.X = -halfSize;
	geo.BoundingBox.Max.X = -halfSize;
	geo.BoundingBox.Min.Y = -halfSize;
	geo.BoundingBox.Max.Y = -halfSize; geo.BoundingBox.Min.X = -halfSize;
	geo.BoundingBox.Min.Z = -halfSize;
	geo.BoundingBox.Max.Z = halfSize;

	geo.CentreOfRotation = { 0.0, 0.0, 0.0 };
	geo.Rotation = { 0.0, 0.0, 0.0 };
	geo.Scale = 1.0;

	return geo;
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
	_boxMesh.BoundingBox.Min.X;
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

FGeometry3D Mesh3D::SaleFPoints3D(list<FPoint3D> points, float scale) {
	FGeometry3D geo = FGeometry3D();
	for (auto iter = geo.Points.begin(); iter != geo.Points.end(); iter++)
	{
		iter->X *= scale;
		iter->X *= scale;
		iter->X *= scale;
	}
	return geo;
}

FGeometry3D Mesh3D::RotateFPoints3D(list<FPoint3D> points, FPoint3D centreOfRot, FPoint3D rot) {
	FGeometry3D geo = FGeometry3D();
	for (auto iter = geo.Points.begin(); iter != geo.Points.end(); iter++)
	{
		// rotate X
		//x' = x
		//y' = y.cos0 - z.sin0
		//z' = y.sinG + z.cosG
		iter->X = iter->X;
		iter->Y = (iter->Y * cos(rot.X)) - (iter->Z * sin(rot.Z));
		iter->Z = (iter->Y * sin(rot.X)) + (iter->Z * cos(rot.X));
		// rotate Y
		//x'    cos0  0 sin0      x
		//y'  = 0     1 0           y
		//z'    -sin0 0 cos0     z
		iter->X = (iter->X * cos(rot.Y)) + (iter->X * sin(rot.Y));
		iter->Y = iter->Y;
		iter->Z = -(iter->Z * sin(rot.Y)) + (iter->Z * cos(rot.Y));
		// rotate Z
		//x'    cosy  -siny 0       x
		//y'  = siny  cosy  0       y
		//z'    0     0     1       z
		iter->X = (iter->X * cos(rot.Z)) - (iter->X * sin(rot.Z));
		iter->Y = (iter->Y * cos(rot.X)) - (iter->Z * sin(rot.Z));
		iter->Z = iter->Z;
	}
	return geo;
}

FGeometry3D Mesh3D::TranslateFPoints3D(list<FPoint3D> points, FPoint3D vec)
{
	FGeometry3D geo = FGeometry3D();

	for (auto iter = geo.Points.begin(); iter != geo.Points.end(); iter++)
	{
		iter->X += vec.X;
		iter->X += vec.Y;
		iter->X += vec.Z;
	}
	return geo;
}