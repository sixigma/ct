#pragma once
#include "gameNode.h"
#include"character.h"

class crono : public gameNode
{
private:
	tagStatus _croSt;			//크로노 능력치
	tagChaSet _croSet;		//크로노 셋팅
	tagItemStatus _croISt;	//크로노 아이템 능력치

	tagImage im;
	tagAni an;
	bool Cleft, _run;	//좌우반전, 달리기
	int _T;		//방향전환용 int(turn) / 0:front , 1:back , 2:right , 3:left
	int Cc;		//idle 상태의 눈깜빡임 카운트
	int _rcW, _rcH;	//캐릭터 렉트용 x,y축 갈이
	int rad;
public:
	crono() {};
	~crono() {};

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

	//크로노 힘 +
	void plusPower(int power) { _croSt.power += power; }
	void setPower(int power) { _croSt.power = power; }//힘 바꾸기
	//크로노 마력 +
	void plusMagic(int magic) { _croSt.magic += magic; }
	void setMagic(int magic) { _croSt.magic = magic; }//마력 바꾸기
	//크로노 스피드 +
	void plusSpeed(int speed) { _croSt.speed += speed; }
	void setSpeed(int speed) { _croSt.speed = speed; }//스피드 바꾸기
	//크로노 체력 +
	void plusStamina(int stamina) { _croSt.stamina += stamina; }
	void setStamina(int stamina) { _croSt.stamina = stamina; }//체력 바꾸기
	//크로노 민첩 +
	void plusHit(int hit) { _croSt.hit += hit; }
	void setHit(int hit) { _croSt.hit = hit; }//민첩 바꾸기
	//크로노 회피 +
	void plusEvasion(int evasion) { _croSt.evasion += evasion; }
	void setEvasion(int evasion) { _croSt.evasion = evasion; }//회피 바꾸기

	//컨디션(느려짐 등 상태이상) 바꾸기
	void setCondition(int condition) { _croSt.condition = condition; }

	//데미지(hp) -
	void hitDamage(int damage) { _croSt.hp -= damage; }
	//최대hp +
	void plusMaxHP(int maxHP) { _croSt.maxHp += maxHP; }
	void setMaxHP(int maxHP) { _croSt.maxHp = maxHP; }//최대 hp 바꾸기

	//mp -
	void minusMP(int mp) { _croSt.mp -= mp; }
	//최대mp +
	void plusMaxMP(int maxMP) { _croSt.maxMp += maxMP; }
	void setMaxMP(int maxMP) { _croSt.maxMp = maxMP; }//최대 mp 바꾸기

	//소지금 +
	void plusMoney(int money) { _croSt.money += money; }
	void setMoney(int money) { _croSt.money = money; }//소지금 바꾸기

	//경험치 +
	void plusExp(int exp) { _croSt.exp += exp; }
	//최대경험치 바꾸기
	void setMaxExp(int maxExp) { _croSt.maxExp = maxExp; }

	//피격 등에 설정시킬 STATE setter
	void setState(STATE state) { _croSet.state = state; }

	//크로노 현재 힘
	int getPower() { return _croSt.power; }
	//크로노 현재 마력
	int getMagic() { return _croSt.magic; }
	//크로노 현재 스피드
	int getSpeed() { return _croSt.speed; }
	//크로노 현재 체력
	int getStamina() { return _croSt.stamina; }
	//크로노 현재 명중
	int getHit() { return _croSt.hit; }
	//크로노 현재 회피
	int getEvasion() { return _croSt.evasion; }

	//크로노 현재 컨디션
	int getCondition() { return _croSt.condition; }

	//크로노 현재 hp
	int getHP() { return _croSt.hp; }
	//크로노 현재 maxHP
	int getMaxHP() { return _croSt.maxHp; }

	//크로노 현재 mp
	int getMP() { return _croSt.mp; }
	//크로노 현재 maxMP
	int getMaxMP() { return _croSt.maxMp; }

	//크로노 현재 소지금
	int getMoney() { return _croSt.money; }

	//크로노 현재 경험치
	int getExp() { return _croSt.exp; }
	//크로노 현재 최대경험치
	int getMaxExp() { return _croSt.maxExp; }
	//크로노 현재 레벨
	int getLV() { return _croSt.Lv; }

	//피격 등을 확인할 STATE getter
	STATE getState() { return _croSet.state; }

	POINT& getPos() { return _croSet.pt; }

};

