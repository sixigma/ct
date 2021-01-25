#pragma once
#include "gameNode.h"
#include "character.h"
class player : public gameNode
{
private:
	tagStatus _Pst;			//플레이어 능력치
	tagChaSet _Pset;		//플레이어 셋팅
	tagItemStatus _PIst;	//플레이어 아이템 능력치

public:
	player() {};
	~player() {};

	HRESULT init();
	void release();
	void update();
	void render();

	//void imgSwitch();		//이미지 보이는 방식이 들어간다
	//void keySetting();	//키 입력 방식
	//void moveSwitch();	//이동시 스위치(벽부딪치기 등)
	//void battleSwitch();	//배틀시 스위치(공격시 렉트 등)

	//setter (대부분 +,- 시킨다)
	
	//플레이어 힘 +
	void plusPower(int power) { _Pst.power += power; }
	void setPower(int power) { _Pst.power = power; }//힘 바꾸기
	//플레이어 마력 +
	void plusMagic(int magic) { _Pst.magic += magic; }		
	void setMagic(int magic) { _Pst.magic = magic; }//마력 바꾸기
	//플레이어 스피드 +
	void plusSpeed(int speed) { _Pst.speed += speed; }		
	void setSpeed(int speed) { _Pst.speed = speed; }//스피드 바꾸기
	//플레이어 체력 +
	void plusStamina(int stamina) { _Pst.stamina += stamina; }
	void setStamina(int stamina) { _Pst.stamina = stamina; }//체력 바꾸기
	//플레이어 민첩 +
	void plusHit(int hit) { _Pst.hit += hit; }				
	void setHit(int hit) { _Pst.hit = hit; }//민첩 바꾸기
	//플레이어 회피 +
	void plusEvasion(int evasion) { _Pst.evasion += evasion; }
	void setEvasion(int evasion) { _Pst.evasion = evasion; }//회피 바꾸기
	
	//컨디션(느려짐 등 상태이상) 바꾸기
	void setCondition(int condition) { _Pst.condition = condition; }

	//데미지(hp) -
	void hitDamage(int damage) { _Pst.hp -= damage; }		
	//최대hp +
	void plusMaxHP(int maxHP) { _Pst.maxHp += maxHP; }		
	void setMaxHP(int maxHP) { _Pst.maxHp = maxHP; }//최대 hp 바꾸기
	//플레이어 이름 바꾸기
	void setName(string name) { _Pset.name = name; }

	//mp -
	void minusMP(int mp) { _Pst.mp -= mp; }					
	//최대mp +
	void plusMaxMP(int maxMP) { _Pst.maxMp += maxMP; }		
	void setMaxMP(int maxMP) { _Pst.maxMp = maxMP; }//최대 mp 바꾸기

	//소지금 +
	void plusMoney(int money) { _Pst.money += money; }
	void setMoney(int money) { _Pst.money = money; }//소지금 바꾸기

	//경험치 +
	void plusExp(int exp) { _Pst.exp += exp; }				
	//최대경험치 바꾸기
	void setMaxExp(int maxExp) { _Pst.maxExp = maxExp; }	

	//플레이어 현재 힘
	int getPower() { return _Pst.power; }
	//플레이어 현재 마력
	int getMagic() { return _Pst.magic; }
	//플레이어 현재 스피드
	int getSpeed() { return _Pst.speed; }
	//플레이어 현재 체력
	int getStamina() { return _Pst.stamina; }
	//플레이어 현재 명중
	int getHit() { return _Pst.hit; }
	//플레이어 현재 회피
	int getEvasion() { return _Pst.evasion; }
	
	//플레이어 현재 컨디션
	int getCondition() { return _Pst.condition; }
	
	//플레이어 현재 hp
	int getHP() { return _Pst.hp; }
	//플레이어 현재 maxHP
	int getMaxHP() { return _Pst.maxHp; }

	//플레이어 현재 mp
	int getMP() { return _Pst.mp; }
	//플레이어 현재 maxMP
	int getMaxMP() { return _Pst.maxMp; }

	//플레이어 현재 소지금
	int getMoney() { return _Pst.money; }

	//플레이어 현재 경험치
	int getExp() { return _Pst.exp; }
	//플레이어 현재 최대경험치
	int getMaxExp() { return _Pst.maxExp; }
	//플레이어 현재 레벨
	int getLV() { return _Pst.Lv; }

	//플레이어 현재 이름
	string getName() { return _Pset.name; }
};