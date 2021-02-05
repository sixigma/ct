#include "stdafx.h"
#include "chronoHome2.h"
#include "player.h"
HRESULT chronoHome2::init()
{

	setMapNum(6);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 5) *currPlPos = { 765, 385 };
	if (getPrevMapNum() == 1) *currPlPos = { 710, 715 };
	else *currPlPos = { 765, 385 };

	// ========================================================


	exit.push_back({ 569, 195, 569+58, 195+130 });
	exit.push_back({ 640, 781, 640 + 131, 781 + 40 });
	prevPlPos = *currPlPos;
	gameScene::setViewport(0, 0);
	return S_OK;
}

void chronoHome2::update()
{
	for (size_t i = 0; i < exit.size(); ++i)
	{
		if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(5);
		if (PtInRect(&exit[1], *currPlPos)) gameScene::goToMap(1);
	}

	mapCollision();
	prevPlPos = *currPlPos;
}

void chronoHome2::release()
{
	
}

void chronoHome2::render()
{
	IMG->render("크로노집아래", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);

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