#include "stdafx.h"
#include "teleport.h"
#include "player.h"

HRESULT teleport::init()
{
	setMapNum(4);
	currPlPos = &pl->getPos();
	if (getPrevMapNum() == 2) *currPlPos = { 800, 200 };
	//else if (getPrevMapNum() == 3) *currPlPos = { 1050, 1000 };
	else *currPlPos = { 800, 200 };

	prevPlPos = *currPlPos;
	gameScene::setViewport(currPlPos->x, currPlPos->y);
	return S_OK;
}

void teleport::release()
{
}

void teleport::update()
{
	if (currPlPos->y - 32 > 1024) gameScene::goToMap(2);

	gameScene::updateViewport(currPlPos->x, currPlPos->y);
	prevPlPos = *currPlPos;
}

void teleport::render()
{
	IMG->render("teleport", getMemDC(), _currOrg.x, _currOrg.y, _currOrg.x, _currOrg.y, WINW, WINH);
}
