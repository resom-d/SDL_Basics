#include "TextRoller.h"

TextRoller::TextRoller()
{
}

bool TextRoller::OnInit(SDL_Renderer* rend, SDL_Window* win)
{
	_renderer = rend;
	_window = win;
	_fontOne.OnInit(_renderer, "", "Resources/fonts/segoeui.ttf", { 0,255,0,255 }, _fontSize);
	DisplayRect = { 20, 50, 200, 800 };
	return true;
}

int TextRoller::OnExecute()
{
	return 1;
}

void  TextRoller::OnLoop()
{
	if (_repeatPause > 0)
	{
		_repeatPause--;
		return;
	}

	for (auto loop = 0; loop < _speed; loop++)
	{
		if (++_currentPosition > _lastItemHeight || _screenItems.size() < 1)
		{
			_currentPosition = 0;
			if (_charIndex >= _theMessage.length())
			{
				_charIndex = 0;
			}
			CharItem item = CharItem();
			item.Content = *next(_theMessage.begin(), _charIndex);
			item.Texture = _fontOne.GetTexture(item.Content);;
			SDL_QueryTexture(item.Texture, nullptr, nullptr, &item.Width, &item.Height);
			item.ScreenPos = { DisplayRect.x, DisplayRect.y + DisplayRect.h - item.Height };
			_lastItemHeight = item.Height;
			_screenItems.push_back(item);
			_charIndex++;

		}
		for (auto item = _screenItems.begin(); item != _screenItems.end(); item++)
		{
			item->ScreenPos.y--;
			if (item->ScreenPos.y < (DisplayRect.y))
			{
				SDL_DestroyTexture(item->Texture);
				item = _screenItems.erase(item);
			}
			if (_screenItems.size() < 1) break;
		}
		if (_screenItems.size() < 1)
		{
			_charIndex = 0;
			_repeatPause = 0 * GlobalFrameRate;
		}
	}
}

void  TextRoller::OnRender()
{
	for (auto item = _screenItems.begin(); item != _screenItems.end(); item++)
	{
		if (item->ScreenPos.y > DisplayRect.y + DisplayRect.h - 255)
		{
			SDL_SetTextureAlphaMod(item->Texture, DisplayRect.y + DisplayRect.h - item->ScreenPos.y);
		}
		if (item->ScreenPos.y < DisplayRect.y + 255)
		{
			SDL_SetTextureAlphaMod(item->Texture, item->ScreenPos.y - DisplayRect.y);
		}
		SDL_Rect sRect = { 0,0, item->Width, item->Height };
		SDL_Rect dRect = { item->ScreenPos.x, item->ScreenPos.y, item->Width, item->Height };
		SDL_RenderCopyEx(_renderer, item->Texture, &sRect, &dRect, 0.0, nullptr, SDL_FLIP_NONE);
	}
}

void  TextRoller::OnCleanup()
{
	_fontOne.OnCleanUp();
	for (auto item = _screenItems.begin(); item != _screenItems.end(); item++)
	{
		SDL_DestroyTexture(item->Texture);
	}
}

void  TextRoller::OnExit()
{}

void  TextRoller::OnEvent(SDL_Event* event)
{

}
