#include "stdafx.h"
#include "leeneSquare.h"
#include "player.h"

HRESULT leeneSquare::init()
{
	event1 = 0;

	setMapNum(2);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 1) *currPlPos = { 1600, 1400 };
	else if (getPrevMapNum() == 3) *currPlPos = { 100, 500 }; //가토방에서 다시 leene로 왔을 때 위치
	else if (getPrevMapNum() == 4) *currPlPos = { 1593, 340 }; //텔레포트
	else *currPlPos = { 1600, 1400 };

	cO.push_back({0, 0 , 1530, 380});
	cO.push_back({1660, 0 , 2200, 200 });
	cO.push_back({ 1725, 200 , 2230, 415 });
	cO.push_back({ 1725, 200 , 1980, 480 });
	cO.push_back({ 2045, 400 , 2175, 480 });
	cO.push_back({ 450, 380 , 1385, 480 });
	cO.push_back({ 510, 480 , 930, 600 });
	cO.push_back({ 640, 600 , 930, 670 });
	cO.push_back({ 250, 700 , 380, 970 });
	cO.push_back({ 250, 970 , 320, 1030 });
	cO.push_back({ 0, 570 , 250, 1480 });
	cO.push_back({ 0, 1280 , 1440, 1480 });
	cO.push_back({ 1695, 1280 , 3080, 1460 });
	cO.push_back({ 450, 830 , 570, 1120 });
	cO.push_back({ 700, 840 , 830, 1180 });
	cO.push_back({ 830, 830 , 890, 1020 });
	cO.push_back({ 895, 670 , 930, 895 });
	cO.push_back({ 895, 895 , 1025, 1150 });
	cO.push_back({ 1150, 895 , 1270, 1215 });
	cO.push_back({ 1150, 895 , 1280, 1460 });
	cO.push_back({ 1270, 960 , 1440, 1460 });
	cO.push_back({ 1695, 960 , 1900, 1460 });
	
	cO.push_back({ 1880, 1285 , 3880, 1460 });

	cO.push_back({ 1850, 895 , 1978, 1215 });
	cO.push_back({ 2110, 895 , 2338, 1215 });
	cO.push_back({ 2210, 0 , 2241, 1215 });
	cO.push_back({ 2240, 800 , 2300, 1152 });
	cO.push_back({ 2230, 800 , 2367, 1185 });
	cO.push_back({ 2225, 0 , 2300, 666 });
	cO.push_back({ 2275, 0 , 2625, 605 });
	cO.push_back({ 2430, 595 , 2620, 667 });
	cO.push_back({ 2620, 475 , 2750, 733 });
	cO.push_back({ 2595, 0 , 3070, 572 });
	cO.push_back({ 2750, 835 , 2905, 1147 });
	cO.push_back({ 2880, 538 , 3069, 1413 });
	cO.push_back({ 2300, 801 , 2437, 1186 });
	cO.push_back({ 1405, 690 , 1520, 769 });
	cO.push_back({ 1620, 690 , 1735, 769 });
	cO.push_back({ 955, 420 , 1092, 420+189 });
	cO.push_back({ 1155, 465 , 1157+65, 465+145 });
	cO.push_back({ 1345, 465 , 1345+65, 465 + 145 });

	eR.push_back({ 448, 1108 , 448 + 56, 1108 + 56 }); // 광장 음식 먹는 음식먹는 이벤트
	eR.push_back({ 1854, 510 , 1854+61, 510 + 61 }); //목걸이 있는 위치

	exit.push_back({ 1473, 1424, 1473 + 190, 1424 + 43 });
	exit.push_back({ 0, 335, 65, 335 + 249 });
	exit.push_back({ 1468, 0, 1468 + 199, 63 });

	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);
	return S_OK;
}

void leeneSquare::release()
{

}

void leeneSquare::update()
{
	//if (currPlPos->x - 32 < 0 && currPlPos->y >= 300 && currPlPos->y <= 580) gameScene::goToMap(3); //가토 + &&y?? 의 위치.
	//if (currPlPos->y + 32 > 1500 && currPlPos->x >= 1400 && currPlPos->x <= 1600) gameScene::goToMap(1); //메인 광장가는 위치 &&x는?
	//if (currPlPos->y - 32 < 0) gameScene::goToMap(4); //텔레포트 가는 방향

	for (size_t i = 0; i < exit.size(); ++i)
	{
		if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(1);
		if (PtInRect(&exit[1], *currPlPos)) gameScene::goToMap(3);
		if (PtInRect(&exit[2], *currPlPos)) gameScene::goToMap(4);
	}
	if (currPlPos->x + 32 > 3072) currPlPos->x = 3072; //x의 우측.
	
	for (size_t i = 0; i < eR.size(); ++i)
	{
		if (PtInRect(&eR[0], *currPlPos))event1 = 1;//보따리 이벤트 접촉
		if (PtInRect(&eR[1], *currPlPos))event2 = 1;//팬던트 이벤트
	}


	mapCollision();
	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void leeneSquare::render()
{
	IMG->render("leeneSquare", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
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
