#include "stdafx.h"
#include "EquipmentItem.h"

HRESULT EquipmentItem::init(string _name)
{
	itemName = _name;
	itemCategory = Equipment;
	itemlist();
	return S_OK;
}

void EquipmentItem::release()
{
}

void EquipmentItem::update()
{
	
}

void EquipmentItem::render()
{
}

void EquipmentItem::itemlist()
{
	if (itemName == "WoodenSword")
	{
		eC = weapon;
		attack = 3;
	}
	if (itemName == "Bandana")
	{
		eC = head;
		speed = 1;
	}

}
