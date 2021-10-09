#include "SDLEvents.h"


SDLEvents::SDLEvents() {};

//SDLEvents::~SDLEvents() {};

void SDLEvents::OnEvent(SDL_Event* Event)
{
	switch (Event->type)
	{
	case SDL_KEYDOWN: {
		OnKeyDown(Event->key.keysym.sym, Event->key.keysym.mod);
		break;
	}

	case SDL_KEYUP: {
		OnKeyUp(Event->key.keysym.sym, Event->key.keysym.mod);
		break;
	}

	case SDL_MOUSEMOTION: {
		OnMouseMove(Event->motion.x, Event->motion.y, Event->motion.xrel, Event->motion.yrel, (Event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0, (Event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0, (Event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0);
		break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		switch (Event->button.button)
		{
		case SDL_BUTTON_LEFT: {
			OnLButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			OnRButtonDown(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			OnMButtonDown(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}

	case SDL_MOUSEBUTTONUP: {
		switch (Event->button.button)
		{
		case SDL_BUTTON_LEFT: {
			OnLButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			OnRButtonUp(Event->button.x, Event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			OnMButtonUp(Event->button.x, Event->button.y);
			break;
		}
		}
		break;
	}

	case SDL_JOYAXISMOTION: {
		OnJoyAxis(Event->jaxis.which, Event->jaxis.axis, Event->jaxis.value);
		break;
	}

	case SDL_JOYBALLMOTION: {
		OnJoyBall(Event->jball.which, Event->jball.ball, Event->jball.xrel, Event->jball.yrel);
		break;
	}

	case SDL_JOYHATMOTION: {
		OnJoyHat(Event->jhat.which, Event->jhat.hat, Event->jhat.value);
		break;
	}

	case SDL_JOYBUTTONDOWN: {
		OnJoyButtonDown(Event->jbutton.which, Event->jbutton.button);
		break;
	}

	case SDL_JOYBUTTONUP: {
		OnJoyButtonUp(Event->jbutton.which, Event->jbutton.button);
		break;
	}

	case SDL_QUIT: {
		OnExit();
		break;
	}

	case SDL_SYSWMEVENT: {
		//Ignore
		break;
	}


	default: {
		OnUser(Event->user.type, Event->user.code, Event->user.data1, Event->user.data2);
		break;
	}
	}
}

void SDLEvents::OnInputFocus()
{
	//Pure virtual, do nothing
}

void SDLEvents::OnInputBlur()
{
	//Pure virtual, do nothing
}

void SDLEvents::OnKeyDown(SDL_Keycode sym, SDL_Keycode mod)
{

}

void SDLEvents::OnKeyUp(SDL_Keycode sym, SDL_Keycode mod)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnMouseFocus()
{
	//Pure virtual, do nothing
}

void SDLEvents::OnMouseBlur()
{
	//Pure virtual, do nothing
}

void SDLEvents::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnMouseWheel(bool Up, bool Down)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnLButtonDown(int mX, int mY)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnLButtonUp(int mX, int mY)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnRButtonDown(int mX, int mY)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnRButtonUp(int mX, int mY)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnMButtonDown(int mX, int mY)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnMButtonUp(int mX, int mY)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnJoyButtonDown(Uint8 which, Uint8 button)
{
	std::cout << "joybutton down event." << std::endl;
}

void SDLEvents::OnJoyButtonUp(Uint8 which, Uint8 button)
{
	std::cout << "joybutton up event." << std::endl;
}

void SDLEvents::OnJoyHat(Uint8 which, Uint8 hat, Uint8 value)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnMinimize()
{
	//Pure virtual, do nothing
}

void SDLEvents::OnRestore()
{
	//Pure virtual, do nothing
}

void SDLEvents::OnResize(int w, int h)
{
	//Pure virtual, do nothing
}

void SDLEvents::OnExpose()
{
	//Pure virtual, do nothing
}

void SDLEvents::OnExit()
{

}

void SDLEvents::OnUser(Uint8 type, int code, void* data1, void* data2)
{
	//Pure virtual, do nothing
}

