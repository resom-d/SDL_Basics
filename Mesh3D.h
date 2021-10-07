#pragma once
#include "EngineBase.h"
#include "FTransform_3D.h"

class Mesh3D : public EngineBase , public FTransform3D
{
public:
	Mesh3D();

	virtual bool EngineBase::OnInit(SDL_Renderer* rend, SDL_Window* win);
	virtual int EngineBase::OnExecute();
	virtual void EngineBase::OnLoop();
	virtual void EngineBase::OnRender();
	virtual void EngineBase::OnCleanup();
	virtual void EngineBase::OnExit();
	virtual void EngineBase::OnEvent(SDL_Event* event);

	virtual void FTransform3D::SaleFPoints3D(list<FPoint3D> points, FPoint3D scale);
	virtual void FTransform3D::RotateFPoints3D(list<FPoint3D> points, FPoint3D centreOfRot, FPoint3D rot);
	virtual void FTransform3D::TranslateFPoints3D(list<FPoint3D> points, FPoint3D vec);
	
private:
	FGeometry3D _mesh;

protected:

};

