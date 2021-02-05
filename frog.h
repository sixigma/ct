#pragma once
#include "gameNode.h"
#include "character.h"
class frog : public gameNode
{
private:
	tagStatus		_frogSt;	//개구리 능력치
	tagChaSet		_frogSet;	//개구리 셋팅
	tagItemStatus	_frogISt;	//개구리 아이템 능력치

	tagImage im;
	tagAni an;
	bool Cleft, _run;	//좌우반전, 달리기
	int _T;		//방향전환용 int(turn) / 0:front , 1:back , 2:right , 3:left
	int Cc;		//idle 상태의 눈깜빡임 카운트
	int rad;
public:
	frog() {};
	~frog() {};

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

	//개구리 힘 +
	void plusPower(int power) { _frogSt.power += power; }
	void setPower(int power) { _frogSt.power = power; }//힘 바꾸기
	//개구리 마력 +
	void plusMagic(int magic) { _frogSt.magic += magic; }
	void setMagic(int magic) { _frogSt.magic = magic; }//마력 바꾸기
	//개구리 스피드 +
	void plusSpeed(int speed) { _frogSt.speed += speed; }
	void setSpeed(int speed) { _frogSt.speed = speed; }//스피드 바꾸기
	//개구리 체력 +
	void plusStamina(int stamina) { _frogSt.stamina += stamina; }
	void setStamina(int stamina) { _frogSt.stamina = stamina; }//체력 바꾸기
	//개구리 민첩 +
	void plusHit(int hit) { _frogSt.hit += hit; }
	void setHit(int hit) { _frogSt.hit = hit; }//민첩 바꾸기
	//개구리 회피 +
	void plusEvasion(int evasion) { _frogSt.evasion += evasion; }
	void setEvasion(int evasion) { _frogSt.evasion = evasion; }//회피 바꾸기

	//컨디션(느려짐 등 상태이상) 바꾸기
	void setCondition(int condition) { _frogSt.condition = condition; }

	//데미지(hp) -
	void hitDamage(int damage) { _frogSt.hp -= damage; }
	//최대hp +
	void plusMaxHP(int maxHP) { _frogSt.maxHp += maxHP; }
	void setMaxHP(int maxHP) { _frogSt.maxHp = maxHP; }//최대 hp 바꾸기

	//mp -
	void minusMP(int mp) { _frogSt.mp -= mp; }
	//최대mp +
	void plusMaxMP(int maxMP) { _frogSt.maxMp += maxMP; }
	void setMaxMP(int maxMP) { _frogSt.maxMp = maxMP; }//최대 mp 바꾸기

	//소지금 +
	void plusMoney(int money) { _frogSt.money += money; }
	void setMoney(int money) { _frogSt.money = money; }//소지금 바꾸기

	//경험치 +
	void plusExp(int exp) { _frogSt.exp += exp; }
	//최대경험치 바꾸기
	void setMaxExp(int maxExp) { _frogSt.maxExp = maxExp; }

	//피격 등에 설정시킬 STATE setter
	void setState(STATE state) { _frogSet.state = state; }

	//개구리 현재 힘
	int getPower() { return _frogSt.power; }
	//개구리 현재 마력
	int getMagic() { return _frogSt.magic; }
	//개구리 현재 스피드
	int getSpeed() { return _frogSt.speed; }
	//개구리 현재 체력
	int getStamina() { return _frogSt.stamina; }
	//개구리 현재 명중
	int getHit() { return _frogSt.hit; }
	//개구리 현재 회피
	int getEvasion() { return _frogSt.evasion; }

	//개구리 현재 컨디션
	int getCondition() { return _frogSt.condition; }

	//개구리 현재 hp
	int getHP() { return _frogSt.hp; }
	//개구리 현재 maxHP
	int getMaxHP() { return _frogSt.maxHp; }

	//개구리 현재 mp
	int getMP() { return _frogSt.mp; }
	//개구리 현재 maxMP
	int getMaxMP() { return _frogSt.maxMp; }

	//개구리 현재 소지금
	int getMoney() { return _frogSt.money; }

	//개구리 현재 경험치
	int getExp() { return _frogSt.exp; }
	//개구리 현재 최대경험치
	int getMaxExp() { return _frogSt.maxExp; }
	//개구리 현재 레벨
	int getLV() { return _frogSt.Lv; }

	//피격 등을 확인할 STATE getter
	STATE getState() { return _frogSet.state; }

	POINT& getPos() { return _frogSet.pt; }

};

