#include "stdafx.h"
#include "ExpendableItem.h"

HRESULT ExpendableItem::init(string _name)
{
	itemName = _name;
	itemCategory = Expendable;
	itemlist();
	return S_OK;
}

void ExpendableItem::release()
{
}

void ExpendableItem::update()
{
}

void ExpendableItem::render()
{
}

void ExpendableItem::itemlist()
{
	if (itemName == "Elixr")
	{
		attack = 3;
	}
	if (itemName == "Bandana")
	{
		speed = 1;
	}

}
