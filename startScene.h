#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:

public:
	startScene();
	~startScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

