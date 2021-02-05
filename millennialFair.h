#pragma once
#include "gameScene.h"
#include "mapManager.h"



#define MILLENNIALFAIRTILEX 48
#define MILLENNIALFAIRTILEY 29

class millennialFair: public mapManager
{
private:

	image*		_mapImg;
	DWORD		_attribute[MILLENNIALFAIRTILEX * MILLENNIALFAIRTILEY];
	RECT unlandable;

public:

	millennialFair() {}
	~millennialFair() override {}

	HRESULT init() override;
	void update() override;
	void release() override;
	void render() override;
	


};

