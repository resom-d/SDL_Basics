#include "TextScroller.h"
#include "FontMap.h"

TextScroller::TextScroller()
{}


void TextScroller::OnInit(SDL_Renderer* rend, string msg, FontMap fontMap, SDL_Color col, Uint16 speed, SDL_Rect dispRect)
{
	_rend = rend;
	_theMessage = msg;

	_fontMap = fontMap;
	_speed = speed;
	_fontColor = col;
	_currentPosition = 0;
	DisplayRect.x = dispRect.x;
	DisplayRect.y = dispRect.y;
	DisplayRect.w = dispRect.w;
	DisplayRect.h = dispRect.h;
}

void TextScroller::OnLoop()
{
	if (_repeatPause > 0)
	{
		_repeatPause--;
	}
	else
	{
		for (auto loop = 0; loop < _speed; loop++)
		{
			if (++_currentPosition > _lastItemWidth || _screenItems.size() < 1)
			{
				_currentPosition = 0;
				if (_charIndex < _theMessage.length())
				{
					CharItem item = CharItem();
					item.Content = *next(_theMessage.begin(), _charIndex);
					item.ScreenPos = { DisplayRect.x + DisplayRect.w + item.Width, DisplayRect.y };
					item.Texture = _fontMap.GetTexture(item.Content);;
					int w, h;
					SDL_QueryTexture(item.Texture, nullptr, nullptr, &w, &h);
					item.Width = w;
					item.Height = h;
					_lastItemWidth = w;
					_screenItems.push_back(item);
					_charIndex++;
				}
			}
			for (auto item = _screenItems.begin(); item != _screenItems.end(); item++)
			{
				item->ScreenPos.x--;
				if (item->ScreenPos.x < DisplayRect.x - item->Width)
				{
					SDL_DestroyTexture(item->Texture);
					item = _screenItems.erase(item);
				}
				if (_screenItems.size() < 1) break;
			}
		}

		if (_screenItems.size() < 1)
		{
			_charIndex = 0;
			_repeatPause = 10 * GlobalFrameRate;
		}
	}
	GotRenderItems = _screenItems.size() > 0;
}

void TextScroller::OnRender()
{
	SDL_Rect r = DisplayRect;
	//SDL_RenderSetClipRect(_rend, &r);
	for (auto item = _screenItems.begin(); item != _screenItems.end(); item++)
	{
		if (item->ScreenPos.x > DisplayRect.w + DisplayRect.x - 255)
		{
			SDL_SetTextureAlphaMod(item->Texture, DisplayRect.w + DisplayRect.x - item->ScreenPos.x);
		}
		if (item->ScreenPos.x < DisplayRect.x + 255 - item->Width)
		{
			SDL_SetTextureAlphaMod(item->Texture, item->ScreenPos.x + item->Width - DisplayRect.x);
		}
		auto a = ((int)(item->ScreenPos.x)) % SINTABSIZE;
		auto y = DisplayRect.y-item->Height- _sinSize - ((Sintable[a] * _sinSize));
		SDL_Rect sRect = { 0,0, item->Width, item->Height };
		SDL_Rect dRect = { item->ScreenPos.x, y, item->Width, item->Height };
		SDL_RenderCopyEx(_rend, item->Texture, &sRect, &dRect, 0.0, nullptr, SDL_FLIP_NONE);
	}
}

void TextScroller::SetSinusSize(float size)
{
	_sinSize = size;
}

void TextScroller::OnCleanUp()
{
	for (auto item = _screenItems.begin(); item != _screenItems.end(); item++)
	{
		SDL_DestroyTexture(item->Texture);
	}
}

void TextScroller::OnReset(void)
{
	_currentPosition = 0;
	//_screenItems.clear();
	_lastItemWidth = 200;
	_charIndex = 0;
}

