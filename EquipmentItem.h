#pragma once
#include "gameNode.h"
#include "item.h"
enum equipCategory // 장비 카테고리 equipCategory
{
	helmet,
	armor,
	accessory,
	weapon
};
enum playerCategory
{
	Crono,
	Marle,
	Lucca,
	Robo,
	Frog,
	Ayla,
	Magus,
	All
};
class EquipmentItem :public item
{
private : 
	equipCategory eC;
	playerCategory pC;
public:
	EquipmentItem() {};
	~EquipmentItem() {};

	HRESULT init(string _name)override;
	void release()override;
	void update()override;
	void render()override;

	void itemlist();
};

