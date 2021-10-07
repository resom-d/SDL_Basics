#pragma once


struct _point3d {
	int X;
	int Y;
	int Z;
};
typedef struct _point3d Point3D;

struct _fpoint3d {
	float X;
	float Y;
	float Z;
};
typedef struct _fpoint3d FPoint3D;

struct _boundingBox3d {
	Point3D Min;
	Point3D Max;
	Point3D Centre;
};
typedef _boundingBox3d BoundingBox3D;

struct _fboundingBox3d {
	FPoint3D Min;
	FPoint3D Max;
	FPoint3D Centre;
};
typedef _fboundingBox3d FBoundingBox3D;

struct _geometry3d {
	Uint16 NoFace = 0;
	Uint16 NoEdge = 0;
	Uint16 NoVertex = 0;
	FPoint3D Rotation;
	Point3D OriginPoint;
	Point3D CentreOfRotation;
};
typedef struct _geometry3d Geometry3D;

struct _fgeometry3d {
	Uint16 NoFace = 0;
	Uint16 NoEdge = 0;
	Uint16 NoVertex = 0;
	FPoint3D Rotation;
	FPoint3D OriginPoint;
	FPoint3D CentreOfRotation;
	FBoundingBox3D BoundingBox;
};
typedef struct _fgeometry3d FGeometry3D;