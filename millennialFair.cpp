#include "stdafx.h"
#include "millennialFair.h"	//메인광장
#include "player.h"

HRESULT millennialFair::init()
{
	setMapNum(1);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 0) *currPlPos = { 1550, 1500 };
	else if (getPrevMapNum() == 2) *currPlPos = { 1625, 200 }; //millennialFair에서 leene로 가는 방향
	else *currPlPos = { 1550, 1500 };

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


	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);

	return S_OK;
}
//3072 1856
void millennialFair::update()
{
	
	
	if (currPlPos->x + 32 > 3072) currPlPos->x = 3072;	//x축의 오른쪽
	if (currPlPos->x < 32) currPlPos->x = 32;			//x축의 왼쪽

	if (currPlPos->y - 32 <32 && currPlPos->x >= 1500 && currPlPos->x <= 1750) gameScene::goToMap(2);	//y축의 위쪽

	

	if (currPlPos->y > 32 + 1856) currPlPos->y = 32 + 1856; 

	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;

}

void millennialFair::release()
{
	cO.clear();
	eR.clear();
}

void millennialFair::render()
{
	IMG->render("millennialFair", getMemDC(), _currOrg.x, _currOrg.y,_currOrg.x,_currOrg.y, WINW, WINH);
}

void millennialFair::mapTool()
{
}

void millennialFair::loadMap()
{
}
