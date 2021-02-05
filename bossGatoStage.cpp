#include "stdafx.h"
#include "bossGatoStage.h"
#include "player.h"

HRESULT bossGatoStage::init()
{
	//_mapImg = imageManager::getSingleton()->add("bossGato", L"res/images/maps/bossGato.bmp");
	setMapNum(3);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 2) *currPlPos = { 660, 780 };
	else if (getPrevMapNum() == 4) *currPlPos = { 1050, 1000 }; 
	
	cO.push_back({ 0,0, 120,780 });
	cO.push_back({ 0,770, 545, 980 });
	cO.push_back({ 120,0, 190,700 });
	cO.push_back({ 190,0, 260,380 });
	cO.push_back({ 260,0, 320,320 });
	cO.push_back({ 320,0, 450,260 });
	cO.push_back({ 450,0, 580,300 });
	cO.push_back({ 580,0, 675,250 });
	cO.push_back({ 675,0, 1030,200 });
	cO.push_back({ 950,0, 1030,980 });
	cO.push_back({ 900,570, 1030,980 });
	cO.push_back({ 740,765, 1030,980 });
	// ========================================================


	eR.push_back({ 532, 731, 532 + 233, 731 +35 });

	exit.push_back({ 542, 962, 542 + 194, 962 + 56 });
	prevPlPos = *currPlPos;
		
	return S_OK;
}

void bossGatoStage::update()
{
	//if (currPlPos->y - probeY > 1024) gameScene::goToMap(2);
	for (size_t i = 0; i < exit.size(); ++i)
	{
		if (PtInRect(&exit[0], *currPlPos)) gameScene::goToMap(2);
	}

	mapCollision();
	prevPlPos = *currPlPos;
}

void bossGatoStage::release()
{
	
}

void bossGatoStage::render()
{
	IMG->render("bossGato", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);

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