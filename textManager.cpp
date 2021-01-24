#include "stdafx.h"
#include "textManager.h"

void textManager::setCurrFontImage(int searchValue)
{
	switch (searchValue)
	{
		case 0:
			_currFontImage = IMG->find("흰색 대화 글꼴");
			break;
		case 1:
			_currFontImage = IMG->find("하늘색 대화 글꼴");
			break;
		case 2:
			_currFontImage = IMG->find("빨간색 대화 글꼴");
			break;
		case 3:
			_currFontImage = IMG->find("노란색 대화 글꼴");
			break;
		case 4:
			_currFontImage = IMG->find("녹색 대화 글꼴");
			break;
		case 5:
			_currFontImage = IMG->find("비활성 대화 글꼴");
			break;
		case 100:
			_currFontImage = IMG->find("흰색 UI 글꼴");
			break;
		case 101:
			_currFontImage = IMG->find("하늘색 UI 글꼴");
			break;
		case 102:
			_currFontImage = IMG->find("빨간색 UI 글꼴");
			break;
		case 103:
			_currFontImage = IMG->find("노란색 UI 글꼴");
			break;
		case 104:
			_currFontImage = IMG->find("녹색 UI 글꼴");
			break;
		case 105:
			_currFontImage = IMG->find("비활성 UI 글꼴");
			break;
		default:
			return;
	}
}

textManager::textManager(): _shouldWindowUseTheTopPane(FALSE), _count(0), _fP(new fontParser), _yesOrNo(FALSE)
{
	HDC hDC = GetDC(_hWnd);
	_hTextWindowDC = CreateCompatibleDC(hDC);
	_hTextWindowBitmap = CreateCompatibleBitmap(hDC, WINW, 320);
	_hOTextWindowBitmap = (HBITMAP)SelectObject(_hTextWindowDC, _hTextWindowBitmap);
	ReleaseDC(_hWnd, hDC);
	_textWindowState = TEXT_WINDOW_STATE::INVISIBLE;
}
textManager::~textManager()
{
	_textWindowState = TEXT_WINDOW_STATE::INVISIBLE;
	DeleteObject(SelectObject(_hTextWindowDC, _hOTextWindowBitmap));
	DeleteObject(_hTextWindowBitmap);
	DeleteDC(_hTextWindowDC);
	SAFE_DEL(_fP);
}

HRESULT textManager::init()
{
	
	return S_OK;
}

void textManager::release()
{
	clearQueue();
}

void textManager::enqueueLine(string line)
{
	// 리마인더: 작성 중

}

void textManager::clearQueue()
{
	if (!_dialogLineQ.empty())
	{
		_dialogLineQ = {};
	}
}

void textManager::updateDialog()
{
	// 리마인더: 작성 중

	switch (_textSpeed)
	{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
	}

}

void textManager::renderDialog(HDC hDC, int fontIdx, int colorIdx)
{
	if (_currentLine != "" && _textWindowState != TEXT_WINDOW_STATE::INVISIBLE)
	{
		if (_shouldWindowUseTheTopPane)
		{
			IMG->frameRender("텍스트 창 스킨 셋", _hTextWindowDC, 0, 0, 0, _textWindowSkin);
			// 리마인더: 작성 중

			BitBlt(hDC, 0, 31, WINW, 320, _hTextWindowDC, 0, 0, SRCCOPY);
		}
		else
		{
			IMG->frameRender("텍스트 창 스킨 셋", _hTextWindowDC, 0, 0, 0, _textWindowSkin);
			// 리마인더: 작성 중

			BitBlt(hDC, 0, WINH - 51 - 320, WINW, 320, _hTextWindowDC, 0, 0, SRCCOPY);
		}
	}
	
}

void textManager::prepareToUseFonts()
{
	_fP->parseFnt(0, "res/fonts/dialogGlyphs.fnt");
	_fP->parseFnt(1, "res/fonts/monoGlyphs.fnt");
}

void textManager::render(HDC hDC, string text, int destX, int destY, int fontIdx, int colorIdx)
{
	if (fontIdx < 2) fontInfo = _fP->getFontInfo(fontIdx);
	else return;

	setCurrFontImage(fontIdx * 100 + colorIdx);

	_currPosX = destX;
	_currPosY = destY;

	for (size_t i = 0; i < text.size(); ++i)
	{
		char chr = text[i];
		if (chr == '\n')
		{
			_currPosX = destX;
			_currPosY += (*fontInfo)[32].height + 16;
		}
		else if (chr == '\\' && i < text.size() - 1 && text[i + 1] == 'n')
		{
			_currPosX = destX;
			_currPosY += (*fontInfo)[32].height + 16;
			i += 2;
			if (i < text.size()) chr = text[i];
			else continue;
		}
		else if (chr == '[')
		{
			if (i < text.size() - 2 && text[i + 2] == ']')
			{
				setCurrFontImage(fontIdx * 100 + text[i + 1] - '0');
				i += 2;
				chr = text[i];
			}
		}
		else if ((*fontInfo)[chr].width == 0) continue;
		_currFontImage->render(hDC, _currPosX, _currPosY, (*fontInfo)[chr].x, (*fontInfo)[chr].y, (*fontInfo)[chr].width, (*fontInfo)[chr].height);

		_currPosX += (*fontInfo)[chr].width;
	}
}
