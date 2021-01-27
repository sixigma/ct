#pragma once

struct itemInit
{
	string itemName;
	int attack;			//장비공격력
	int defense;		//장비 방어력
	int power;			//물리공격데미지관련	
	int magic;			//마법공격데미지관련	
	int speed;			//속도타이먼관련
			
	int hit;			//명중률
	int evasion;		//회피율	

	int stamina;		//물리방어관련
	int magicDefense;	//마법방어관련

	int recoveryHp;		//체력회복
	int maxHp;			//최대체력증가
	int recoveryMp;		//마나회복
	int maxMp;			//최대마나증가
	int money;			//가격
};

enum category
{
	expendable,
	equipment,
	etc
};

