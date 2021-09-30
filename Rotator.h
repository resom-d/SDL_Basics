#include "Basics.h"
extern double Sintable[SINTABSIZE];
extern double Costable[SINTABSIZE];

class Rotator : public EngineBase
{

public:
	Rotator();
	Rotator(SDL_Renderer *rend, SDL_Rect winFrame);
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
	SDL_Rect _windowFrame;
	SDL_Point _hexagon[6];
	SDL_Point _hexagonBuf[6];
	SDL_Point _originP;
	int _rotationV = 0;
	int _rotationV1 = 45;
	int _rotationV2 = 90;
	double _scaleVX = 1.0;
	double _scaleVX1 = 1.0;
	double _scaleVX2 = 1.0;
	double _scaleVY = 1.0;
	double _scaleVY1 = 1.0;
	double _scaleVY2 = 1.0;
	double _zoomX = 0.01;
	long _frameCounter = 0;
	long _framePause = 0;
	
protected:

};