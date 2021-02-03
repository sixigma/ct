#pragma once
//노래 부르는 연습보스 

//#include "gameNode.h"
#include "gameScene.h"
#include "mapManager.h"
#include "player.h"

#define BOSSTILEX 16
#define BOSSTILEY 16


class bossGatoStage : public mapManager
{
protected:
	image*			 _mapImg;

	//enemymanager
	DWORD			 _attribute[BOSSTILEX * BOSSTILEY];

	float			 _cameraX;
	float			 _cameraY;
public:
	bossGatoStage() {}
	~bossGatoStage() override {}

	virtual HRESULT init() override;
	virtual void update() override;
	virtual void release() override;
	virtual void render() override;


};

