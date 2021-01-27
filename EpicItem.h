#pragma once
#include "gameNode.h"
#include "item.h"

class Epicitem :public gameNode
{
private : 
	itemInit _iInit;
	category _iCategory;
public:
	Epicitem() {};
	~Epicitem() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void itemlist(string _name);
};

