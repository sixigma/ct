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

	int  event1;
	int  event2;

public:

	millennialFair();
	~millennialFair() override {}

	HRESULT init() override;
	void update() override;
	void release() override;
	void render() override;
	
	int getEvent1() { return event1; }
	int getEvent2() { return event2; }
};

