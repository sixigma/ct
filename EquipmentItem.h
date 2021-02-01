#pragma once
#include "gameNode.h"
#include "item.h"
enum equipCategory // 장비 카테고리 equipCategory
{
	head,
	armor,
	accessory,
	weapon
};
class EquipmentItem :public item
{
private : 
	equipCategory eC;
public:
	EquipmentItem() {};
	~EquipmentItem() {};

	HRESULT init(string _name)override;
	void release()override;
	void update()override;
	void render()override;

	void itemlist();
};

