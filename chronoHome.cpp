#include "stdafx.h"
#include "chronoHome.h"
#include "player.h"
HRESULT chronoHome::init()
{
	setMapNum(5);
	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 6) *currPlPos = { 310, 700 };
	else *currPlPos = { 675, 495 };

	
	// ========================================================


	exit.push_back({ 432, 740, 432 + 50, 740 + 102 });

	prevPlPos = *currPlPos;
	gameScene::setViewport(0, 0);
	return S_OK;
}

void chronoHome::update()
{
	for (size_t i = 0; i < exit.size(); ++i)
	{
	if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(6);
	}


	mapCollision();
	prevPlPos = *currPlPos;
}

void chronoHome::release()
{
	
}

void chronoHome::render()
{
	IMG->render("크로노집위", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);

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