#pragma once
#include <SDL.h>

class GameEvents
{

public:
	virtual void OnEvent(SDL_Event* Event) = 0;
	virtual void OnInputFocus() = 0;
	virtual void OnInputBlur() = 0;
	virtual void OnKeyDown(SDL_Keycode sym, SDL_Keycode mod) = 0;
	virtual void OnKeyUp(SDL_Keycode sym, SDL_Keycode mod) = 0;
	virtual void OnMouseFocus() = 0;
	virtual void OnMouseBlur() = 0;
	virtual void OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) = 0;
	virtual void OnMouseWheel(bool Up, bool Down) = 0;
	virtual void OnLButtonDown(int mX, int mY) = 0;
	virtual void OnLButtonUp(int mX, int mY) = 0;
	virtual void OnRButtonDown(int mX, int mY) = 0;
	virtual void OnRButtonUp(int mX, int mY) = 0;
	virtual void OnMButtonDown(int mX, int mY) = 0;
	virtual void OnMButtonUp(int mX, int mY) = 0;
	virtual void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value) = 0;
	virtual void OnJoyButtonDown(Uint8 which, Uint8 button) = 0;
	virtual void OnJoyButtonUp(Uint8 which, Uint8 button) = 0;
	virtual void OnJoyHat(Uint8 which, Uint8 hat, Uint8 value) = 0;
	virtual void OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) = 0;
	virtual void OnMinimize() = 0;
	virtual void OnRestore() = 0;
	virtual void OnResize(int w, int h) = 0;
	virtual void OnExpose() = 0;
	virtual void OnUser(Uint8 type, int code, void* data1, void* data2) = 0;

private:
protected:
};

