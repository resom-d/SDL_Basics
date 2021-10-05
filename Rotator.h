#include "Basics.h"
#include "Pointlist2D.h"
#include "SDL_Extras.h"

class Rotator : public EngineBase
{

public:
	Rotator();

	bool EngineBase::OnInit(SDL_Renderer* rend, SDL_Window* win);
	void EngineBase::OnEvent(SDL_Event* Event);
	int EngineBase::OnExecute();
	void EngineBase::OnLoop();
	void EngineBase::OnRender();
	void EngineBase::OnCleanup();
	void EngineBase::OnExit();
	void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod);
	void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod);
	void OnLoopPhase_1();
	void OnLoopPhase_2();
	void OnRenderPhase_1();
	void OnRenderPhase_2();

private:
	Uint16 _phase = 1;
	long _frameCounter = 0;
	long _framePause = 6 * GlobalFrameRate;
	long _framePause1 = 6 * GlobalFrameRate;
	long _framePause2 = 6 * GlobalFrameRate;
	SDL_FPoint _hexagonP[6];
	SDL_FPoint _starFigureP[16] = {
		{-4,0},
		{-1,1},
		{-0.4, 0.4},
		{-1,2},
		{0,4},
		{1,2},
		{0.4,0.4},
		{1,1},
		{4,0},
		{1,-1},
		{0.4,0 - 0.4},
		{1,-2},
		{0,-4},
		{-1,-2},
		{-0.4,-0.4},
		{-1,-1},
	};
	Pointlist2D _hexagon;
	Pointlist2D _starfigure;
	SDL_FPoint _originP;
	float _scale = 1.00;
	float _scaleInc = 0.001;
	float _originalScale = 40.0;
	Uint16 _scalePause = 10 * GlobalFrameRate;
	SDL_FPoint _scalePoint[4];
	SDL_FPoint _vScalePoint[4];
	SDL_FPoint _screenCenter;
	Uint16 _noFigures = 6;
	Uint16 _noRepeats = 12;
	Uint16 _noFiguresShown = 0;
	Uint16 _showFigureDir = 1;
	float _repeatScale = -0.9;
	int _rotationV = 0;
	int _rotationV1 = 0;
	int _rotationV2 = 0;
	float _scaleVX = 1.0;
	float _scaleVY = 1.0;
	float _scaleXMin = 1.0;
	float _scaleXMax = 6.0;
	float _scaleVX1 = 0.6;
	float _scaleVY1 = 0.6;
	float _scaleVX2 = 0.6;
	float _scaleVY2 = 0.6;
	float _zoomX = 0.04;
	float _zoomX1 = 0.04;
	float _zoomX2 = 0.06;

protected:

};