#include "stdafx.h"
#include "bossGatoStage.h"
#include "player.h"

HRESULT bossGatoStage::init()
{
	//_mapImg = imageManager::getSingleton()->add("bossGato", L"res/images/maps/bossGato.bmp");

	load2("res/mapInfo/가토/saveMap1.map");
	currPlPos = &pl->getCrono()->getPos();
	if (getPrevMapNum() == 1) *currPlPos = { 644, 850 };
	else if (getPrevMapNum() == 4) *currPlPos = { 1050, 1000 }; 
	setMapNum(3);

	// ========================================================

	tileMapLoad("보스맵", 1024, 1024);

	exit.push_back({ 542, 962, 542 + 194, 962 + 56 });
	prevPlPos = *currPlPos;
		
	return S_OK;
}

void bossGatoStage::update()
{
	//if (currPlPos->y - probeY > 1024) gameScene::goToMap(2);
	zorderUpdate();
	if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(2);

	mapCollision();
	prevPlPos = *currPlPos;
}

void bossGatoStage::release()
{
	cO.clear();
	eR.clear();
	//_tile.clear();
}

void bossGatoStage::render()
{
	//IMG->render("bossGato", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
	//IMG->render("보스맵", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
	IMG->renderZ(zGrid, IMG->find("보스맵Z"), getMemDC(), 0, 0);
	IMG->renderZ(0, IMG->find("보스맵"), getMemDC(), 0, 0);


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