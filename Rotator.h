#include "EngineBase.h"
#include "Basics.h"
#include "Pointlist2D.h"
#include "SDL_Extras.h"
class Rotator : public EngineBase
{

public:
	Rotator();

	bool EngineBase::OnInit(SDL_Renderer* rend, SDL_Window* win);
	void EngineBase::OnEvent(SDL_Event* event);
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
	Uint16 _phase = 0;
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
	SDL_FPoint _springFigure[35] = {
	{-4, 2},
	 {-3, 1},
	 {-3, 0.5},
	{-2.5, 1},
	{-2, 0.5},
	 {-1.5, 1},
	 {-1, 0.5},
	 {-0.5, 1},
	 {0, 0.5},
	 {0.5, 1},
	 {1, 0.6},
	 {1.5, 1},
	 {2, 0.5},
	{2.5, 1},
	{3, 0.5},
	{3, 1},
	{4, 2},
	{4.5, 0},
	{4, -2},
	{3, -1},
	{3, -0.5},
	{2.5, -1},
	{2, -0.5},
	{1.5, -1},
	{1, -0.5},
	{0.5, -1},
	{0, -0.5},
	{-0.5, -1},
	{-1, -0.5},
	{-1.5, -1},
	{-2, -0.5},
	{-2.6, -1},
	{-3, -0.5},
	{-3, -1},
	{-4, -2},
	};
	Pointlist2D _hexagon;
	Pointlist2D _starfigure;
	SDL_FPoint _originP;
	SDL_FPoint _screenCenter;
	// phase 1
	float _scaleVX = 1.0;
	float _scaleVY = 1.0;
	float _scaleXMin = 1.0;
	float _scaleXMax = 6.0;
	float _zoomX = 0.04;
	float _zoomX1 = 0.04;
	float _zoomX2 = 0.06;
	float _repeatScale = -0.9;
	int _rotationP1[3] = { 0, 0, 0 };
	// phase 2
	float _scale = 1.00;
	float _scaleInc = 0.001;
	float _originalScale = 40.0;
	Uint16 _scalePause = 10 * GlobalFrameRate;
	SDL_FPoint _scalePoint;
	SDL_FPoint _vScalePoint = {1.0, 0.5};
	Uint16 _noFigures = 6;
	Uint16 _noRepeats = 12;
	Uint16 _noFiguresShown = 0;
	Uint16 _showFigureDir = 1;
	int _rotationP2[3] = { 0, 0, 0 };
	
protected:

};