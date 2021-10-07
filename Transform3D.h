#pragma once
#include "list"
#include "Types_3D.h"
using namespace std;

class Transform3D
{
public:
	virtual void SalePoints3D(list<Point3D> points, FPoint3D scale) =0;
	virtual void RotatePoints3D(list<Point3D> points, Point3D centreOfRot, Point3D rot) =0;
	virtual void TranslatePoints3D(list<Point3D> points, Point3D vec) =0;
	
	
};