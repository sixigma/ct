#include "stdafx.h"
#include "millennialFair.h"	//메인광장
#include "player.h"

HRESULT millennialFair::init()
{
	setMapNum(1);
	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 6) *currPlPos = { 1560, 1733 };
	else if (getPrevMapNum() == 2) *currPlPos = { 1562, 1369 }; //millennialFair에서 leene로 가는 방향
	else *currPlPos = { 1560, 1733 };



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


	if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(2);
	if (PtInRect(&exit[1], *currPlPos)) gameScene::goToMap(2);
	
	

	if (currPlPos->y > 32 + 1856) currPlPos->y = 32 + 1856; 
	mapCollision();
	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;

}

void millennialFair::release()
{
	cO.clear();
	eR.clear();
	tile.clear();
}

void millennialFair::render()
{
	IMG->renderZ(2000, IMG->find("Leene_SquareZ2"), getMemDC(), 0, 0);
	IMG->renderZ(0, IMG->find("Leene_Square2"), getMemDC(), 0, 0);

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

