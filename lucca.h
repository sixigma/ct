#pragma once
#include "gameNode.h"
#include"character.h"

class lucca : public gameNode
{
private:
	tagStatus _lucSt;			//루카 능력치
	tagChaSet _lucSet;		//루카 셋팅
	tagItemStatus _lucISt;	//루카 아이템 능력치

	tagImage im;
	tagAni an;
	bool Cleft, _run;	//좌우반전, 달리기
	int _T;		//방향전환용 int(turn) / 0:front , 1:back , 2:right , 3:left
	int Cc;		//idle 상태의 눈깜빡임 카운트
	int rad;	//임시(지름)
public:
	lucca() {};
	~lucca() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void imgSetting();
	void aniSetting();
	void imgSwitch();		//이미지 보이는 방식이 들어간다
	void keySetting();	//키 입력 방식
	//void moveSwitch();	//이동시 스위치(벽부딪치기 등)
	void battleSwitch();	//배틀시 스위치(공격시 렉트 등)

	//setter 

	//루카 힘 +
	void plusPower(int power) { _lucSt.power += power; }
	void setPower(int power) { _lucSt.power = power; }//힘 바꾸기
	//루카 마력 +
	void plusMagic(int magic) { _lucSt.magic += magic; }
	void setMagic(int magic) { _lucSt.magic = magic; }//마력 바꾸기
	//루카 스피드 +
	void plusSpeed(int speed) { _lucSt.speed += speed; }
	void setSpeed(int speed) { _lucSt.speed = speed; }//스피드 바꾸기
	//루카 체력 +
	void plusStamina(int stamina) { _lucSt.stamina += stamina; }
	void setStamina(int stamina) { _lucSt.stamina = stamina; }//체력 바꾸기
	//루카 민첩 +
	void plusHit(int hit) { _lucSt.hit += hit; }
	void setHit(int hit) { _lucSt.hit = hit; }//민첩 바꾸기
	//루카 회피 +
	void plusEvasion(int evasion) { _lucSt.evasion += evasion; }
	void setEvasion(int evasion) { _lucSt.evasion = evasion; }//회피 바꾸기

	//컨디션(느려짐 등 상태이상) 바꾸기
	void setCondition(int condition) { _lucSt.condition = condition; }

	//데미지(hp) -
	void hitDamage(int damage) { _lucSt.hp -= damage; }
	//최대hp +
	void plusMaxHP(int maxHP) { _lucSt.maxHp += maxHP; }
	void setMaxHP(int maxHP) { _lucSt.maxHp = maxHP; }//최대 hp 바꾸기

	//mp -
	void minusMP(int mp) { _lucSt.mp -= mp; }
	//최대mp +
	void plusMaxMP(int maxMP) { _lucSt.maxMp += maxMP; }
	void setMaxMP(int maxMP) { _lucSt.maxMp = maxMP; }//최대 mp 바꾸기

	//소지금 +
	void plusMoney(int money) { _lucSt.money += money; }
	void setMoney(int money) { _lucSt.money = money; }//소지금 바꾸기

	//경험치 +
	void plusExp(int exp) { _lucSt.exp += exp; }
	//최대경험치 바꾸기
	void setMaxExp(int maxExp) { _lucSt.maxExp = maxExp; }

	//피격 등에 설정시킬 STATE setter
	void setState(STATE state) { _lucSet.state = state; }

	//루카 현재 힘
	int getPower() { return _lucSt.power; }
	//루카 현재 마력
	int getMagic() { return _lucSt.magic; }
	//루카 현재 스피드
	int getSpeed() { return _lucSt.speed; }
	//루카 현재 체력
	int getStamina() { return _lucSt.stamina; }
	//루카 현재 명중
	int getHit() { return _lucSt.hit; }
	//루카 현재 회피
	int getEvasion() { return _lucSt.evasion; }

	//루카 현재 컨디션
	int getCondition() { return _lucSt.condition; }

	//루카 현재 hp
	int getHP() { return _lucSt.hp; }
	//루카 현재 maxHP
	int getMaxHP() { return _lucSt.maxHp; }

	//루카 현재 mp
	int getMP() { return _lucSt.mp; }
	//루카 현재 maxMP
	int getMaxMP() { return _lucSt.maxMp; }

	//루카 현재 소지금
	int getMoney() { return _lucSt.money; }

	//루카 현재 경험치
	int getExp() { return _lucSt.exp; }
	//루카 현재 최대경험치
	int getMaxExp() { return _lucSt.maxExp; }
	//루카 현재 레벨
	int getLV() { return _lucSt.Lv; }

	//피격 등을 확인할 STATE getter
	STATE getState() { return _lucSet.state; }

	POINT& getPos() { return _lucSet.pt; }

};

