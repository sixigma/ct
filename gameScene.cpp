#include "stdafx.h"
#include "gameScene.h"

int gameScene::_countForReEnablingKeyInput;

gameScene::gameScene(int anyNum)
{
	UNREFERENCED_PARAMETER(anyNum);

	_currOrg = _newOrg = { 0, 0 };

	_totRegion = { 0, 0, WINW, WINH };
	_camMovLim = { _totRegion.left, _totRegion.top, _totRegion.right - _totRegion.left - WINW, _totRegion.bottom - _totRegion.top - WINH };

	_p = new player;
	_p->init();
}

gameScene::~gameScene()
{
	_p->release();
	SAFE_DEL(_p);
}

HRESULT gameScene::init() {	return S_OK; } // 변경 금지
void gameScene::release() { } // 변경 금지

void gameScene::update()
{
	if (TXT->getTextWindowState1() != TEXT_WINDOW_STATE::INVISIBLE
		|| TXT->getTextWindowState2() != TEXT_WINDOW_STATE::INVISIBLE)
	{
		if (KEY->down('X')) TXT->toggleTextWindowPos();
	}

	_p->update();





	// 출력할 글 갱신
	if (_isInBattle) TXT->updateBM();
	else if (_isMenuDisplayed) TXT->updateC();
	else TXT->updateL();
}

void gameScene::render()
{
#ifdef _DEBUG
	char str[256];
	//if (KEY->isToggledOn(VK_TAB)) DrawRct(getMemDC(), _p->getPos().x - 32, _p->getPos().y - 8, 64, 8);
#endif

	PatBlt(getMemDC(), 0, 0, WINW, WINH, BLACKNESS);
	//
	_p->render();
	//

	// 글 출력
	if (TXT->getTextWindowState1() != TEXT_WINDOW_STATE::INVISIBLE
		|| TXT->getTextWindowState2() != TEXT_WINDOW_STATE::INVISIBLE)
	{
		if (_isInBattle) TXT->renderBM(getMemDC());
		else TXT->renderL(getMemDC());
	}
	else if (_isMenuDisplayed) TXT->renderC(getMemDC(), _menuMsgPos.x, _menuMsgPos.y);

#ifdef _DEBUG
		{
			if (KEY->isToggledOn(VK_SCROLL))
			{
				//sprintf_s(str, "Player pos: %d, %d", _p->getPos().x, _p->getPos().y);
				//TextOut(getMemDC(), 0, 48, str, static_cast<int>(strlen(str)));

				sprintf_s(str, "Pointer pos: %d, %d (%d, %d)", _mouse.x + _currOrg.x, _mouse.y + _currOrg.y, _mouse.x, _mouse.y);
				TextOut(getMemDC(), 0, 64, str, static_cast<int>(strlen(str)));

				if (_mouse.x + 42 < WINW)
				{
					Rectangle(getMemDC(), _mouse.x + 9, _mouse.y + 9, _mouse.x + 10 + 33, _mouse.y + 10 + 33);
					StretchBlt(getMemDC(), _mouse.x + 10, _mouse.y + 10, 32, 32, getMemDC(), _mouse.x - 8, _mouse.y - 8, 16, 16, SRCCOPY);
					DrawLine(getMemDC(), _mouse.x + 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x + 26 + _currOrg.x, _mouse.y + 30 + _currOrg.y);
					DrawLine(getMemDC(), _mouse.x + 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x + 30 + _currOrg.x, _mouse.y + 26 + _currOrg.y);
				}
				else
				{
					Rectangle(getMemDC(), _mouse.x - 43, _mouse.y + 9, _mouse.x + 10 - 19, _mouse.y + 10 + 33);
					StretchBlt(getMemDC(), _mouse.x - 42, _mouse.y + 10, 32, 32, getMemDC(), _mouse.x - 8, _mouse.y - 8, 16, 16, SRCCOPY);
					DrawLine(getMemDC(), _mouse.x - 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x - 26 + _currOrg.x, _mouse.y + 30 + _currOrg.y);
					DrawLine(getMemDC(), _mouse.x - 26 + _currOrg.x, _mouse.y + 26 + _currOrg.y, _mouse.x - 22 + _currOrg.x, _mouse.y + 26 + _currOrg.y);
				}
			}
		}
#endif
}

void gameScene::updateViewport(int x, int y)
{
	if (y - VIEWPORT_UPDATE_OFFSET > _currOrg.y + WINH / 2)
	{
		if (_currOrg.y < _camMovLim.bottom)
			_newOrg.y = _currOrg.y + static_cast<int>(static_cast<float>(_camMovLim.bottom - _currOrg.y) / 12.f) + 1;
		if (y < _newOrg.y + WINH / 2) _newOrg.y = y - WINH / 2;
	}
	else if (y + VIEWPORT_UPDATE_OFFSET < _currOrg.y + WINH / 2)
	{
		if (_currOrg.y > _camMovLim.top)
			_newOrg.y = _currOrg.y - static_cast<int>(static_cast<float>(_currOrg.y - _camMovLim.top) / 12.f) - 1;
		if (y > _newOrg.y + WINH / 2) _newOrg.y = y - WINH / 2;
	}
	if (x - VIEWPORT_UPDATE_OFFSET > _currOrg.x + WINW / 2)
	{
		if (_currOrg.x < _camMovLim.right)
			_newOrg.x = _currOrg.x + static_cast<int>(static_cast<float>(_camMovLim.right - _currOrg.x) / 12.f) + 1;
		if (x < _newOrg.x + WINW / 2) _newOrg.x = x - WINW / 2;
	}
	else if (x + VIEWPORT_UPDATE_OFFSET < _currOrg.x + WINW / 2)
	{
		if (_currOrg.x > _camMovLim.left)
			_newOrg.x = _currOrg.x - static_cast<int>(static_cast<float>(_currOrg.x - _camMovLim.left) / 12.f) - 1;
		if (x > _newOrg.x + WINW / 2) _newOrg.x = x - WINW / 2;
	}
	if (_newOrg.x != _currOrg.x || _newOrg.y != _currOrg.y)
	{
		_currOrg.x = _newOrg.x;
		_currOrg.y = _newOrg.y;
	}
}

void gameScene::setViewport(int x, int y)
{
	if (y - VIEWPORT_UPDATE_OFFSET > _currOrg.y + WINH / 2)
	{
		_newOrg.y = min(y - WINH / 2, _camMovLim.bottom);
	}
	else if (y + VIEWPORT_UPDATE_OFFSET < _currOrg.y + WINH / 2)
	{
		_newOrg.y = max(y - WINH / 2, _camMovLim.top);
	}
	if (x - VIEWPORT_UPDATE_OFFSET > _currOrg.x + WINW / 2)
	{
		_newOrg.x = min(x - WINW / 2, _camMovLim.right);
	}
	else if (x + VIEWPORT_UPDATE_OFFSET < _currOrg.x + WINW / 2)
	{
		_newOrg.x = max(x - WINW / 2, _camMovLim.left);
	}
	_currOrg.x = _newOrg.x;
	_currOrg.y = _newOrg.y;
}
