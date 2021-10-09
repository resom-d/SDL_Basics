#pragma once
#include "list"
#include "Types_3D.h"
using namespace std;

class FTransform3D
{
	virtual FGeometry3D SaleFPoints3D(list<FPoint3D> points, float scale) = 0;
	virtual FGeometry3D RotateFPoints3D(list<FPoint3D> points, FPoint3D centreOfRot, FPoint3D rot) = 0;
	virtual FGeometry3D TranslateFPoints3D(list<FPoint3D> points, FPoint3D vec) = 0;
};