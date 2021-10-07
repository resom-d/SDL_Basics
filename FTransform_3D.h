#pragma once
#include "list"
#include "Types_3D.h"
using namespace std;

class FTransform3D
{
	virtual void SaleFPoints3D(list<FPoint3D> points, FPoint3D scale) = 0;
	virtual void RotateFPoints3D(list<FPoint3D> points, FPoint3D centreOfRot, FPoint3D rot) = 0;
	virtual void TranslateFPoints3D(list<FPoint3D> points, FPoint3D vec) = 0;
};