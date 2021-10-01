#include "Basics.h"
#include "Pointlist2D.h"

class Rotator : public EngineBase
{

public:
	Rotator();
	Rotator(SDL_Renderer *rend, SDL_FRect winFrame);
	bool EngineBase::OnInit();
	void EngineBase::OnEvent(SDL_Event* Event);
	int EngineBase::OnExecute();
	void EngineBase::OnLoop();
	void EngineBase::OnRender();
	void EngineBase::OnCleanup();
	void EngineBase::OnExit();
	void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod);
	void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod);
	
private:
	
	SDL_Renderer *_renderer = nullptr;
	SDL_FRect _windowFrame;
	SDL_FPoint _hexagonP[6];
	SDL_FPoint _starFigureP[16] = {
		{-4,0},
		{-1,1},
		{-0.2, 0.2},
		{-1,2},
		{0,4},
		{1,2},
		{0.2,0.2},
		{1,1},
		{4,0},
		{1,-1},
		{0.2,0-0.2},
		{1,-2},
		{0,-4},
		{-1,-2},
		{-0.2,-0.2},
		{-1,-1},
	};
	
	Pointlist2D _hexagon;
	Pointlist2D _starfigure;

	SDL_FPoint _originP;
	int _rotationV = 0;
	int _rotationV1 = 45;
	int _rotationV2 = 90;
	float _scaleVX = 0.8;
	float _scaleVY = 0.8;
	float _scaleVX1 = 0.6;
	float _scaleVY1 = 0.6;
	float _scaleVX2 = 0.6;
	float _scaleVY2 = 0.6;
	float _zoomX = 0.02;
	float _zoomX1 = 0.04;
	float _zoomX2 = 0.06;
	long _frameCounter = 0;
	long _framePause = 6 * GlobalFrameRate;
	long _framePause1 = 6 * GlobalFrameRate;
	long _framePause2 = 6 * GlobalFrameRate;
	
protected:

};