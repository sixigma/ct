#include "stdafx.h"
#include "millennialFair.h"	//메인광장
#include "player.h"

millennialFair::millennialFair(): event1(0), event2(0)
{
}

HRESULT millennialFair::init()
{
	load2("res/mapInfo/린광장/saveMap1.map");
	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 6) *currPlPos = { 1560, 1733 };
	else if (getPrevMapNum() == 3)
	{
		*currPlPos = { 70, 432 };
		pl->getCrono()->setT(2);
	}
	else *currPlPos = { 1578, 1334 };

	setMapNum(1);

	eR.push_back({ 464, 1080, 464 + 56, 1080 + 56 }); // 음식 보따리 이벤트
	eR.push_back({ 1854, 510, 1854 + 61, 510 + 61 }); // Marle 목걸이 이벤트

	exit.push_back({ 1440, 1410 , 1440 + 256, 1410 + 64});
	exit.push_back({ 0, 320 , 64, 320 + 256 });
	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);

	return S_OK;
}

void millennialFair::update()
{

	if (PtInRect(&exit[0], *currPlPos))
	{
		gameScene::goToMap(1);
		return;
	}
	else if (PtInRect(&exit[1], *currPlPos))
	{
		gameScene::goToMap(3);
		return;
	}
	else if (currPlPos->y > 32 + 1856) currPlPos->y = 32 + 1856;
	else if (PtInRect(&eR[0], *currPlPos)) event1 = 1;//보따리 이벤트 접촉
	else if (PtInRect(&eR[1], *currPlPos)) event2 = 1;//팬던트 이벤트

	zorderUpdate();
	mapCollision();
	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void millennialFair::release()
{
	cO.clear();
	eR.clear();
	exit.clear();
	//_tile.clear();
}

void millennialFair::render()
{
	IMG->renderZ(zGrid, "Leene_SquareZ2", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
	IMG->renderZ(0, "Leene_Square2", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);


	if (event1 == 0) IMG->renderZ(currPlPos->y - 1, "보따리", getMemDC(), eR[0].left, eR[0].top - 64);
	if (event2 == 0) IMG->renderZ(currPlPos->y - 1, "펜던트", getMemDC(), eR[1].left, eR[1].top);

#ifdef _DEBUG
	{
		if (KEY->isToggledOn(VK_CAPITAL))
		{
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0));
			HPEN hOPen = (HPEN)SelectObject(getMemDC(), hPen);
			HBRUSH hOBrush = (HBRUSH)SelectObject(getMemDC(), hBrush);
			for (int y = 0; y < _crtYsize; ++y)
			{
				for (int x = 0; x < _crtXsize - 18; ++x)
				{
					if (!_tile[y][x].rectYes) continue;
					DrawRct(getMemDC(), _tile[y][x].rect);
				}
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

