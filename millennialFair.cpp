#include "stdafx.h"
#include "millennialFair.h"	//메인광장
#include "player.h"

HRESULT millennialFair::init()
{
	load2("res/mapInfo/린광장/saveMap1.map");
	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 6) *currPlPos = { 1560, 1733 };
	else if (getPrevMapNum() == 3) *currPlPos = { 70, 400 }; 
	else *currPlPos = { 1578, 1334 };

	setMapNum(1);

	//나가보리기
	exit.push_back({ 1440, 1410 , 1440 + 256, 1410 + 64});
	exit.push_back({ 0, 320 , 64, 320 + 256 });
	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);

	return S_OK;
}
//3072 1856
void millennialFair::update()
{
	zorderUpdate();


	if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(1);
	if (PtInRect(&exit[1], *currPlPos)) gameScene::goToMap(3);
	
	

	if (currPlPos->y > 32 + 1856) currPlPos->y = 32 + 1856; 
	mapCollision();
	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;

}

void millennialFair::release()
{
	cO.clear();
	eR.clear();
	//_tile.clear();
}

void millennialFair::render()
{
	IMG->renderZ(zGrid, IMG->find("Leene_SquareZ2"), getMemDC(), 0, 0);
	IMG->renderZ(0, IMG->find("Leene_Square2"), getMemDC(), 0, 0);

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

