#include "stdafx.h"
#include "leeneSquare.h"
#include "player.h"

HRESULT leeneSquare::init()
{
	event1 = 0;
	load2("res/mapInfo/밀레광장/saveMap1.map");
	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 6) *currPlPos = { 1495 + 100, 1750 };
	else if (getPrevMapNum() == 1) *currPlPos = { 1600, 144 }; 
	else *currPlPos = { 1600, 1400 };


	setMapNum(2);

	eR.push_back({ 448, 1108 , 448 + 56, 1108 + 56 }); // 광장 음식 먹는 음식먹는 이벤트
	eR.push_back({ 1854, 510 , 1854+61, 510 + 61 }); //목걸이 있는 위치

	exit.push_back({ 1500, 10, 1700, 30 });
	exit.push_back({ 1495, 1866, 1680, 1866 + 63 });

	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);
	return S_OK;
}

void leeneSquare::release()
{
	cO.clear();
	eR.clear();
	//_tile.clear();

}

void leeneSquare::update()
{
	//if (currPlPos->x - 32 < 0 && currPlPos->y >= 300 && currPlPos->y <= 580) gameScene::goToMap(3); //가토 + &&y?? 의 위치.
	//if (currPlPos->y + 32 > 1500 && currPlPos->x >= 1400 && currPlPos->x <= 1600) gameScene::goToMap(1); //메인 광장가는 위치 &&x는?
	//if (currPlPos->y - 32 < 0) gameScene::goToMap(4); //텔레포트 가는 방향

	zorderUpdate();
	if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(2);
	if (PtInRect(&exit[1], *currPlPos)) gameScene::goToMap(6);
	//if (PtInRect(&exit[2], *currPlPos)) gameScene::goToMap(2);

	if (eR.size() <= 0) return;
	if (PtInRect(&eR[0], *currPlPos))event1 = 1;//보따리 이벤트 접촉
	if (PtInRect(&eR[1], *currPlPos))event2 = 1;//팬던트 이벤트


	mapCollision();
	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void leeneSquare::render()
{
	IMG->renderZ(zGrid, IMG->find("Leene_SquareZ"), getMemDC(), 0, 0);
	IMG->renderZ(0, IMG->find("Leene_Square"), getMemDC(), 0, 0);

	if(event1 == 0)IMG->render("보따리", getMemDC(), eR[0].left, eR[0].top - 64);
	if(event2 == 0)IMG->render("펜던트", getMemDC(), eR[1].left, eR[1].top);
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
