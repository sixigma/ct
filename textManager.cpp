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

textManager::textManager():
	_shouldWindowUseTheTopPane(FALSE), _shouldBeAutoClosed(FALSE), _isGoingToBeAutoClosed(FALSE),
	_shouldWindowHaveChoices(FALSE), _isWholeCurrStrShown(FALSE),
	_windowClipCount(0), _waitCount(0), _fP(new fontParser), _choiceSelected(0)
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
	clearLineQ();
	clearMsgQ();

	iSS.clear();
	iSS.str(string());
}

void textManager::enqueueLine(string line, int forWhichChoice)
{
	_dialogLineQ.push(make_pair(forWhichChoice, line));
}

void textManager::enqueueMsg(string line, bool isShownLetterByLetter)
{
	_battleMsgQ.push(make_pair(isShownLetterByLetter, line));
}

void textManager::clearLineQ()
{
	if (!_dialogLineQ.empty()) _dialogLineQ = {};
}

void textManager::clearMsgQ()
{
	if (!_battleMsgQ.empty()) _battleMsgQ = {};
}

void textManager::updateDialog()
{
	if (_textWindowState == TEXT_WINDOW_STATE::INVISIBLE)
	{
		if (!_dialogLineQ.empty()) // 출력 대기 중인 스트링이 있으면
		{
			_textWindowState = TEXT_WINDOW_STATE::OPENING;
			_windowClipCount = 0;
			_waitCount = 0;
			_isWholeCurrStrShown = FALSE;
			_shouldWindowHaveChoices = FALSE;
			_shouldBeAutoClosed = FALSE;
			_isGoingToBeAutoClosed = FALSE;
			if (!_currStr.empty()) _currStr.clear();

			// istringstream 변수 비우기
			iSS.clear();
			iSS.str(string());
		}
	}
	else if (_textWindowState == TEXT_WINDOW_STATE::OPENING)
	{
		++_windowClipCount;
		if (_windowClipCount > 10) _textWindowState = TEXT_WINDOW_STATE::VISIBLE;
	}
	else if (_textWindowState == TEXT_WINDOW_STATE::VISIBLE)
	{
		if (_dialogLineQ.empty()) // 출력 대기 중인 스트링이 없으면
		{
			_textWindowState = TEXT_WINDOW_STATE::CLOSING;
			_windowClipCount = 0;
		}
		else if (_waitCount > 0)
		{
			--_waitCount;
		}
		else if (!_isWholeCurrStrShown)
		{
			if (iSS.rdbuf()->in_avail() == 0 && _currStr == "")
			{
				if (_choiceSelected != 0)
				{
					while (!_dialogLineQ.empty() && (_dialogLineQ.front().first != _choiceSelected && _dialogLineQ.front().first != 0))
					{
						_dialogLineQ.pop();
						if (_dialogLineQ.empty()) return;
					}
				}
				iSS.str(_dialogLineQ.front().second);
			}
			
			iSS.get(_character);
			if (iSS.fail())
				_isWholeCurrStrShown = TRUE;
			else if (_character == '<')
			{
				iSS.get(_character);
				if (iSS.fail())
					_isWholeCurrStrShown = TRUE;
				else
				{
					string tempStr = "";
					while (true)
					{
						tempStr += _character;
						iSS.get(_character);
						if (iSS.fail())
						{
							_isWholeCurrStrShown = TRUE;
							break;
						}
						else if (_character == '>')
						{
							if (tempStr[0] == 'w') // 기다리기이면(즉 <w자연수>가 있으면)
							{
								try
								{
									int count = stoi(tempStr.substr(1));
									if (count > 0) _waitCount = count;
								}
								catch (const invalid_argument& e)
								{
									UNREFERENCED_PARAMETER(e);
								}
							}
							else if (tempStr == "acf") // 강제 자동 닫기(시간이 지나야만 닫는다.)이면(즉 <acf>가 있으면)
							{
								_waitCount = 60;
								_isGoingToBeAutoClosed = TRUE;
								_shouldBeAutoClosed = TRUE;
							}
							else if (tempStr.substr(0, 3) == "acf") // 강제 자동 닫기(시간이 지나야만 닫는다.)이면(즉 <acf자연수>가 있으면)
							{
								try
								{
									int count = stoi(tempStr.substr(3));
									if (count > 0) _waitCount = count;
									_isGoingToBeAutoClosed = TRUE;
									_shouldBeAutoClosed = TRUE;
								}
								catch (const invalid_argument& e)
								{
									UNREFERENCED_PARAMETER(e);
								}
							}
							else if (tempStr.substr(0,2) == "ac") // 자동 닫기이면(즉 <ac자연수>가 있으면)
							{
								try
								{
									int count = stoi(tempStr.substr(2));
									if (count > 0) _waitCount = count;
									_isGoingToBeAutoClosed = TRUE;
								}
								catch (const invalid_argument& e)
								{
									UNREFERENCED_PARAMETER(e);
								}
							}
							else if (tempStr == "ac") // 자동 닫기이면(즉 <ac>가 있으면)
							{
								_waitCount = 60;
								_isGoingToBeAutoClosed = TRUE;
							}
							else if (tempStr == "c") // 선택지 손가락 아이콘 보이기이면(즉 <c>가 있으면)
							{
								_shouldWindowHaveChoices = TRUE;
								_choiceSelected = 1; // 기본으로 처음 것이 선택된 상태가 되게 한다.
							}
							else if (tempStr == "zc") // 선택 초기화이면
							{
								_choiceSelected = 0;
							}
							break;
						}
					}
				}
			}
			else if (_character == '[')
			{
				_currStr += _character;
				iSS.get(_character);
				if (iSS.fail())
					_isWholeCurrStrShown = TRUE;
				else
				{
					string tempStr = "";
					while (true)
					{
						tempStr += _character;
						iSS.get(_character);
						if (iSS.fail())
						{
							_isWholeCurrStrShown = TRUE;
							break;
						}
						else if (_character == ']')
						{
							_currStr += tempStr + ']';
							break;
						}
					}
				}
			}
			else if (_character == '\\')
			{
				_currStr += _character;
				iSS.get(_character);
				if (iSS.fail())
					_isWholeCurrStrShown = TRUE;
				else
					_currStr += _character;
			}
			else
				_currStr += _character;
		}
		else if (_isWholeCurrStrShown)
		{
			if (KEY->down('V') && !_shouldBeAutoClosed || _isGoingToBeAutoClosed && _waitCount == 0)
			{
				iSS.clear();
				iSS.str(string());
				_isWholeCurrStrShown = FALSE;
				_isGoingToBeAutoClosed = FALSE;
				_shouldBeAutoClosed = FALSE;
				_currStr = "";
				_dialogLineQ.pop();
				if (_shouldWindowHaveChoices) _shouldWindowHaveChoices = FALSE;
			}
			else if (_shouldWindowHaveChoices)
			{
				if (KEY->down(VK_DOWN) && _choiceSelected == 1) _choiceSelected = 2;
				else if (KEY->down(VK_UP) && _choiceSelected == 2) _choiceSelected = 1;
			}
		}
	}
	else if (_textWindowState == TEXT_WINDOW_STATE::CLOSING)
	{
		++_windowClipCount;
		if (_windowClipCount > 10) _textWindowState = TEXT_WINDOW_STATE::INVISIBLE;
	}
}

void textManager::updateBattleMsg()
{
	// 리마인더: 작성 필요
	// 리마인더: 전투 메시지이면 자동 닫기는 _battleMsgCount에 의존하여야 한다.



	switch (_battleMsgSpeed)
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
	if (_textWindowState != TEXT_WINDOW_STATE::INVISIBLE)
	{
		PatBlt(_hTextWindowDC, 0, 0, WINW, 320, BLACKNESS);

		// 글 출력 창 DC 비트맵 클리핑 영역 지정하기
		if (_textWindowState == TEXT_WINDOW_STATE::OPENING)
		{
			IMG->setRctClipRgn(_hTextWindowDC, 0, 16 * (10 - _windowClipCount), WINW, 32 * _windowClipCount);
		}
		else if (_textWindowState == TEXT_WINDOW_STATE::CLOSING)
		{
			IMG->setRctClipRgn(_hTextWindowDC, 0, 16 * _windowClipCount, WINW, 32 * (10 - _windowClipCount));
		}

		// 글 출력 창 DC 비트맵에 창 출력하기
		IMG->render("대사 출력 창 스킨", _hTextWindowDC, 0, 0);

		// 글 출력 창 DC 비트맵에 대사 출력하기
		TXT->render(_hTextWindowDC, _currStr, 31, 40, fontIdx, colorIdx);

		// 선택지가 있다면 글 출력 창 DC 비트맵에 선택 손가락 아이콘을 출력하기
		if (_shouldWindowHaveChoices)
		{
			switch (_choiceSelected)
			{
				case 1:
					_currPosX = 64;
					_currPosY -= ((*fontInfo)[32].height + 32);
					break;
				case 2:
					_currPosX = 64;
					_currPosY -= 16;
					break;
			}
			IMG->frameRender("흰색 타일셋0", _hTextWindowDC, _currPosX, _currPosY, 0, 2);
			IMG->frameRender("흰색 타일셋0", _hTextWindowDC, _currPosX + 32, _currPosY, 1, 2);
			IMG->frameRender("흰색 타일셋0", _hTextWindowDC, _currPosX, _currPosY + 32, 0, 3);
			IMG->frameRender("흰색 타일셋0", _hTextWindowDC, _currPosX + 32, _currPosY + 32, 1, 3);
		}

		// 글 출력 창 DC 비트맵에 있는 창과 대사를 hDC 비트맵에 출력하기
		if (_shouldWindowUseTheTopPane)
		{
			BitBlt(hDC, 0, 31, WINW, 320, _hTextWindowDC, 0, 0, SRCCOPY);
			//IMG->resetClipRgn(_hTextWindowDC);
		}
		else
		{
			BitBlt(hDC, 0, WINH - 51 - 320, WINW, 320, _hTextWindowDC, 0, 0, SRCCOPY);
			//IMG->resetClipRgn(_hTextWindowDC);
		}
	}
}

void textManager::renderBattleMsg(HDC hDC, int fontIdx, int colorIdx)
{
	if (_textWindowState != TEXT_WINDOW_STATE::INVISIBLE)
	{
		PatBlt(_hTextWindowDC, 0, 0, WINW, 320, BLACKNESS);

		// 글 출력 창 DC 비트맵에 창 출력하기
		// 리마인더: 작성 필요: IMG->frameRender("-----------", _hTextWindowDC, 0, 0, 0, _textWindowSkin);

		// 글 출력 창 DC 비트맵에 대사 출력하기
		TXT->render(_hTextWindowDC, _currStr, 31, 40, fontIdx, colorIdx);

		// 글 출력 창 DC 비트맵에 있는 창과 대사를 hDC 비트맵에 출력하기
		if (_shouldWindowUseTheTopPane)
		{
			// 리마인더: 작성 필요: BitBlt(hDC, 0, 31, WINW, 320, _hTextWindowDC, 0, 0, SRCCOPY);
		}
		else
		{
			// 리마인더: 작성 필요: BitBlt(hDC, 0, WINH - 51 - 320, WINW, 320, _hTextWindowDC, 0, 0, SRCCOPY);
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
		if (chr == '\n') // \n: 개행
		{
			_currPosX = destX;
			_currPosY += (*fontInfo)[32].height + 16;
		}
		else if (chr == '\t') // \t: 세 칸 띄기
		{
			_currPosX += (*fontInfo)[32].width * 3;
		}
		else if (chr == '\\' && i < text.size() - 1 && text[i + 1] == 'n') // \\n: raw string literal 개행
		{
			_currPosX = destX;
			_currPosY += (*fontInfo)[32].height + 16;
			i += 1;
			continue;
		}
		else if (chr == '\\' && i < text.size() - 1 && text[i + 1] == 't') // \\t: raw string literal 세 칸 띄기
		{
			_currPosX += (*fontInfo)[32].width * 3;
			i += 1;
			continue;
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
