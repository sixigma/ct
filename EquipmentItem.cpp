#include "stdafx.h"
#include "EquipmentItem.h"

HRESULT EquipmentItem::init(string _name)
{
	itemName = _name;
	
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
		itemCategory = Equipment;
		eC = weapon;
		pC = Crono;
		attack = 3;
		sell = 50;
	}
	if (itemName == "IronBlade")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Crono;

		money = 350;
		sell = 175;
	
		attack = 7;
	}
	if (itemName == "SteelSaber")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Crono;

		money = 800;
		sell = 400;
		
		attack = 15;
	}
	if (itemName == "LodeSword")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Crono;

		money = 4000;
		sell = 2000;

		attack = 20;
	}
	if (itemName == "RedKatana")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Crono;

		money = 4500;
		sell = 2250;

		attack = 30;
		magic = 2;
	}
	//=======================================marle====
	if (itemName == "BronzeBow")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Marle;

		money = 0;
		sell = 40;

		attack = 3;
	}

	if (itemName == "IronBow")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Marle;

		money = 850;
		sell = 425;

		attack = 15;
	}

	if (itemName == "LodeBow")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Marle;

		money = 0;
		sell = 850;

		attack = 20;
	}

	if (itemName == "RobinBow")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Marle;

		money = 2850;
		sell = 1425;

		attack = 25;
	}

	//==============================Lucca

	if (itemName == "AirGun")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Lucca;

		money = 0;
		sell = 150;

		attack = 5;
	}

	if (itemName == "DartGun")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Lucca;

		money = 800;
		sell = 400;

		attack = 7;
	}

	if (itemName == "AutoGun")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Lucca;

		money = 1200;
		sell = 600;

		attack = 15;
	}

	if (itemName == "PlasmaGun")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Lucca;

		money = 3200;
		sell = 1600;

		attack = 25;
	}

	//============================Robo

	if (itemName == "TinArm")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Robo;

		money = 0;
		sell = 500;

		attack = 20;
	}

	if (itemName == "HameerArm")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Robo;

		money = 3500;
		sell = 1750;

		attack = 25;
	}

	if (itemName == "MirageHand")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Robo;

		money = 0;
		sell = 2750;

		attack = 30;
	}

	//========================================Frog===
	if (itemName == "BronzeEdge")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Frog;

		money = 0;
		sell = 175;

		attack = 6;
	}
	if (itemName == "IronSword")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Frog;

		money = 0;
		sell = 550;

		attack = 10;
	}
	if (itemName == "Masamune")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Frog;

		money = 0;
		sell = 0;

		attack = 75;
	}

	//================================Ayla===============
	if (itemName == "Fist")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Ayla;

		//아일라의 무기는 레벨에 따라 자동변환 1~71
	}
	if (itemName == "IronFist")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Ayla;

		//아일라의 무기는 레벨에 따라 자동변환 72~95
		//크리티컬 확률 증가
		//혼란 부여 확정
	}
	if (itemName == "BronzeFist")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Ayla;

		//아일라의 무기는 레벨에 따라 자동변환 96~99
		//최고 대미지 9999
	}
	//==================Magus ======================
	if (itemName == "DarkScythe")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Magus;

		money = 0;
		sell = 10000;

		attack = 120;
	}
	if (itemName == "Hurricane")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Magus;

		money = 35000;
		sell = 17500;

		attack = 135;
	}
	if (itemName == "StarScythe")
	{
		itemCategory = Equipment;
		eC = weapon;
		pC = Magus;

		
		sell = 21000;

		attack = 150;
	}
	//===================================Armor
	if (itemName == "HideTunic")
	{
		itemCategory = Equipment;
		eC = armor;
		pC = All;

		sell = 40;

		defense = 5;
	}
	if (itemName == "karateGi")
	{
		itemCategory = Equipment;
		eC = armor;
		pC = All;

		money = 300;
		sell = 150;

		defense = 10;
	}
	if (itemName == "BronzeMail")
	{
		itemCategory = Equipment;
		eC = armor;
		pC = Crono, Robo, Frog, Magus;

		money = 520;
		sell = 260;

		defense = 16;
	}
	if (itemName == "MaidenSuit")
	{
		itemCategory = Equipment;
		eC = armor;
		pC = Marle, Lucca, Ayla;

		money = 560;
		sell = 280;

		defense = 18;
	}
	if (itemName == "IronSuit")
	{
		itemCategory = Equipment;
		eC = armor;
		pC = All;

		money = 800;
		sell = 400;

		defense = 25;
	}
	if (itemName == "TitanVest")
	{
		itemCategory = Equipment;
		eC = armor;
		pC = All;

		money = 1200;
		sell = 600;

		defense = 32;
	}

	if (itemName == "GoldSuit")
	{
		itemCategory = Equipment;
		eC = armor;
		pC = All;

		money = 1300;
		sell = 650;

		defense = 39;
	}
	//=================helmet=============
	if (itemName == "hideCap")
	{
		itemCategory = Equipment;
		eC = helmet;
		pC = All;

		money = 0;
		sell = 25;

		defense = 3;
	}

	if (itemName == "BronzeHelm")
	{
		itemCategory = Equipment;
		eC = helmet;
		pC = All;

		money = 200;
		sell = 100;

		defense = 8;
	}

	if (itemName == "IronHelm")
	{
		itemCategory = Equipment;
		eC = helmet;
		pC = All;

		money = 500;
		sell = 250;

		defense = 14;
	}
	if (itemName == "Beret")
	{
		itemCategory = Equipment;
		eC = helmet;
		pC = Marle, Lucca, Ayla;

		money = 700;
		sell = 350;

		defense = 17;
	}
	if (itemName == "GoldHelm")
	{
		itemCategory = Equipment;
		eC = helmet;
		pC = Crono, Robo, Frog, Magus;

		money = 0;
		sell = 600;

		defense = 18;
	}
	//==============================acce======
	if (itemName == "Bandana")
	{
		itemCategory = Equipment;
		eC = accessory;
		pC = All;

		speed = 1;

		itemTip = "Speed + 1";
	}
	if (itemName == "Ribbon")
	{
		itemCategory = Equipment;
		eC = accessory;
		pC = All;

		hit = 2;

		itemTip = "Hit + 1";
	}
	if (itemName == "PowerGlove")
	{
		itemCategory = Equipment;
		eC = accessory;
		pC = All;

		power = 2;

		itemTip = "power + 2";
	}
	if (itemName == "Amulet")
	{
		itemCategory = Equipment;
		eC = accessory;
		pC = All;
		//모든 상태이상 면역

		itemTip = "prevents all status debuff";
	}
}
