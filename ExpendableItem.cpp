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
	if (itemName == "Tonic")
	{
		money = 10;
		sell = 5;
		recoveryHp = 50;
		itemTip = "Restores 50 HP";
	}
	if (itemName == "Mid Tonic")
	{
		money = 100;
		sell = 50;
		recoveryHp = 200;
		itemTip = "Restores 200HP";
	}
	if (itemName == "Full Tonic")
	{
		money = 700;
		sell = 350;
		recoveryHp = 500;
		itemTip = "Restores 200HP";
	}
	if (itemName == "Ether")
	{
		money = 800;
		sell = 400;
		recoveryMp = 10;
		itemTip = "Restores 10MP";
	}
	if (itemName == "Mid Ether")
	{
		money = 2000;
		sell = 1000;
		recoveryMp = 30;
		itemTip = "Restores 30MP";
	}
	if (itemName == "Full Ether")
	{
		money = 6000;
		sell = 3000;
		recoveryMp = 60;
		itemTip = "Restores 60MP";
	}
	if (itemName == "Elixer")
	{
		money = 800;
		sell = 400;
		recoveryHp = maxHp;
		recoveryMp = maxMp;
		itemTip = "Restores Full Mp,Hp";
	}
	if (itemName == "powerTab")
	{
		power = 1;
		sell = 5;
		itemTip = "Power + 1";
	}
	if (itemName == "magicTab")
	{
		magic = 1;
		sell = 5;
		itemTip = "Magic + 1";
	}
	if (itemName == "speedTab")
	{
		speed = 1;
		sell = 5;
		itemTip = "speed + 1";
	}

}