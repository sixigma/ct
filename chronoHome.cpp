#include "stdafx.h"
#include "chronoHome.h"
#include "player.h"
HRESULT chronoHome::init()
{

	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 6) *currPlPos = { 450, 995 };
	else *currPlPos = { 645, 440 };

	setMapNum(5);
	
	// ========================================================


	exit.push_back({ 495, 1005, 495 + 100, 1005 + 100 });

	prevPlPos = *currPlPos;
	gameScene::setViewport(0, 0);
	return S_OK;
}

void chronoHome::update()
{

	if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(6);

	mapCollision();
	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void chronoHome::release()
{
	cO.clear();
	eR.clear();
	tile.clear();
}

void chronoHome::render()
{
	IMG->renderZ(2000, IMG->find("CronoRoomZ1"), getMemDC(), 0, 0);
	IMG->renderZ(0, IMG->find("CronoRoom1"), getMemDC(), 0, 0);

	//IMG->execZ();

#ifdef _DEBUG
	{
		if (KEY->isToggledOn(VK_CAPITAL))
		{
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
			HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			for (size_t i = 0; i < cO.size(); ++i)
			{
				DrawRct(getMemDC(), cO[i]);
			}
			DeleteObject(SelectObject(getMemDC(), hOPen));
			DeleteObject(SelectObject(getMemDC(), hOBrush));
		}
		if (KEY->isToggledOn(VK_CAPITAL))
		{
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 255));
			HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			for (size_t i = 0; i < eR.size(); ++i)
			{
				DrawRct(getMemDC(), eR[i]);
			}
			DeleteObject(SelectObject(getMemDC(), hOPen));
			DeleteObject(SelectObject(getMemDC(), hOBrush));
		}
		if (KEY->isToggledOn(VK_CAPITAL))
		{
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
			HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			for (size_t i = 0; i < exit.size(); ++i)
			{
				DrawRct(getMemDC(), exit[i]);
			}
			DeleteObject(SelectObject(getMemDC(), hOPen));
			DeleteObject(SelectObject(getMemDC(), hOBrush));
		}
	}

#endif
}