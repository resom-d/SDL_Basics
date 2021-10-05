#include "ChaosTris.h"
#include <algorithm>

void RemoveDoubles(vector<SDL_Point>& v)
{
	auto comp = [](const SDL_Point& lhs, const SDL_Point& rhs) {return lhs.x == rhs.x; };
	auto pred = [](const SDL_Point& lhs, const SDL_Point& rhs) {return lhs.y < rhs.y; };
	//sort(v.begin(), v.end(), pred);
	auto last = std::unique(v.begin(), v.end(), comp);
	v.erase(last, v.end());
}

ChaosTris::ChaosTris()
{
}

bool ChaosTris::OnInit(SDL_Renderer* rend, SDL_Window* win)
{
	_renderer = rend;
	_window = win;
	return true;
}
bool ChaosTris::OnInitA(SDL_Renderer* rend, SDL_Window* win, FontMap chrmap)
{
	_renderer = rend;
	_window = win;
	_chrMap = chrmap;
	srand(time(0));

	SDL_GetWindowSize(_window, &_windowFrame.w, &_windowFrame.h);

	for (int p = 0; p < 50; p++)
	{
		SDL_Point point = { rand() % 1600, rand() % 900 };
		_points.push_back(point);
	}	

	_lastTarget = _points[16];


	return true;
};

int ChaosTris::OnExecute()
{
	return 1;
};

void ChaosTris::OnEvent(SDL_Event* event)
{

};

void ChaosTris::OnLoop()
{
	for (int i = 0; i < 1000; i++)
	{
		SDL_Point np, op, fp;
		bool found = false;
		RemoveDoubles(_points);
		Uint16 newP = rand() * 777  % _points.size();

		if (_points[newP].x > _lastTarget.x)
		{
			fp.x = (_points[newP].x - _lastTarget.x) / 2;
		}
		else
		{
			fp.x = (_lastTarget.x - _points[newP].x) / 2;
		}
		if (_points[newP].y > _lastTarget.y)
		{
			fp.y = (_points[newP].y - _lastTarget.y) / 2;
		}
		else
		{
			fp.y = (_lastTarget.y - _points[newP].y) / 2;
		}
		_points.push_back(fp);

		_lastTarget = _points[newP];
	}

};

void ChaosTris::OnRender()
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	for (auto i = _points.begin(); i != _points.end(); i++)
	{
		SDL_RenderDrawPoint(_renderer, i->x, i->y);
	}
	_chrMap.RenderStringAt(_renderer, "Points drawn " + to_string( _points.size()), {100, 750}, 32, nullptr);
}

void ChaosTris::OnCleanup()
{

}

void ChaosTris::OnExit()
{
}

void ChaosTris::OnKeyDown(SDL_Keycode sym, SDL_Keycode mod)
{
}

void ChaosTris::OnKeyUp(SDL_Keycode sym, SDL_Keycode mod)
{
}