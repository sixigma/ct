#include "stdafx.h"
#include "startScene.h"
#include "videoPlayer.h"

startScene::startScene(): vP(new videoPlayer)
{

}

startScene::~startScene()
{
	SAFE_DEL(vP);
}

HRESULT startScene::init()
{
	vP->init();
	if (!KEY->press(VK_SPACE))
	{
		vP->playOpening();
	}
	return S_OK;
}

void startScene::release()
{
	vP->release();
}

void startScene::update()
{
	vP->update();
}

void startScene::render()
{
	if (KEY->press(VK_SPACE))
	{
		_isScrBlackingOut = TRUE;
		SC->changeScene("게임 장면");
	}
}