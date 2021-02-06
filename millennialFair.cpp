#include "stdafx.h"
#include "millennialFair.h"	//메인광장
#include "player.h"

HRESULT millennialFair::init()
{
	setMapNum(1);
	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 6) *currPlPos = { 1560, 1733 };
	else if (getPrevMapNum() == 2) *currPlPos = { 1625, 200 }; //millennialFair에서 leene로 가는 방향
	else *currPlPos = { 1560, 1733 };

	cO.push_back({ 0, 0 , 1280, 384 });
	cO.push_back({ 0, 383 , 260, 383+497 });
	cO.push_back({ 0, 826 , 135, 1029+826 });
	cO.push_back({ 1268 , 0 , 1268+170, 241 });
	cO.push_back({ 1697  , 0 , 1697 + 193 , 241 });
	//map 2 입구쪽 의자
	cO.push_back({ 1268  , 235 , 1268 + 206 , 235+78 });
	cO.push_back({ 1661  , 235 , 1661 + 206 , 235 + 78 });
	//
	cO.push_back({ 1858  , 0 , 1858 + 1220 , 399});
	cO.push_back({ 2880  , 361 , 2880 + 186 , 361+571 });
	//텐트쪽
	cO.push_back({ 2558  , 398 , 2558 + 342 , 398+200 });
	cO.push_back({ 2658  , 398 , 2558 + 342 , 398 + 200 });

	//나무위
	cO.push_back({ 134, 1159 , 134+51, 1159+694 });
	cO.push_back({ 176, 1339 , 176+128, 1339+522 });
	cO.push_back({ 285, 1402 , 285+170, 1402+453 });

	cO.push_back({ 450, 1666 , 450+1024, 1666+190 });
	cO.push_back({ 1656, 1614 , 1656+1415, 1614 + 244 });
	cO.push_back({ 1719, 1577 , 1719 + 1354, 1577 + 79 });
	cO.push_back({ 2625, 1285 , 2625 + 446 , 1285 + 377 });
	cO.push_back({ 2765, 1224 , 2765 + 303  , 1224 + 122 });
	cO.push_back({ 2836, 1146  , 2836 + 235, 1146 + 129 });
	cO.push_back({ 2880 , 838   , 2880 + 192, 838 + 341 });

	//나가보리기
	exit.push_back({ 1471, 1816 , 1471 +201, 1816 + 48});
	exit.push_back({ 1413, 0 , 1413 + 313, 44 });
	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);

	return S_OK;
}
//3072 1856
void millennialFair::update()
{
	
	
	if (currPlPos->x + 32 > 3072) currPlPos->x = 3072;	//x축의 오른쪽
	if (currPlPos->x < 32) currPlPos->x = 32;			//x축의 왼쪽


	if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(6);
	if (PtInRect(&exit[1], *currPlPos)) gameScene::goToMap(2);
	
	

	if (currPlPos->y > 32 + 1856) currPlPos->y = 32 + 1856; 
	mapCollision();
	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;

}

void millennialFair::release()
{
	
}

void millennialFair::render()
{
	IMG->renderZ(2000, IMG->find("CronoRoomZ1"), getMemDC(), 0, 0);
	IMG->renderZ(0, IMG->find("CronoRoom1"), getMemDC(), 0, 0);
	
	IMG->execZ();

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

