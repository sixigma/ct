#pragma once
#include "gameNode.h"
#include"character.h"

class crono : public gameNode
{
private:
	tagStatus _croSt;		//크로노 능력치
	tagStatus _itemSt;		//크로노 아이템 능력치
	tagChaSet _croSet;		//크로노 셋팅

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

	//크로노 공격력 setter
	void plusAtk(int atk) { _croSt.atk += atk; }
	void setAtk(int atk) { _croSt.atk = atk; }
	//크로노 마력 +
	void plusMagic(int magic) { _croSt.magic += magic; }
	void setMagic(int magic) { _croSt.magic = magic; }//마력 setter
	//크로노 힘 +
	void plusPower(int power) { _croSt.power += power; }
	void setPower(int power) { _croSt.power = power; }//힘 setter
	//크로노 스피드 +
	void plusSpeed(int speed) { _croSt.speed += speed; }
	void setSpeed(int speed) { _croSt.speed = speed; }//스피드 setter
	//크로노 체력 +
	void plusStamina(int stamina) { _croSt.stamina += stamina; }
	void setStamina(int stamina) { _croSt.stamina = stamina; }//체력 setter
	//크로노 민첩 +
	void plusHit(int hit) { _croSt.hit += hit; }
	void setHit(int hit) { _croSt.hit = hit; }//민첩 setter
	//크로노 회피 +
	void plusEvasion(int evasion) { _croSt.evasion += evasion; }
	void setEvasion(int evasion) { _croSt.evasion = evasion; }//회피 setter

	//컨디션(느려짐 등 상태이상) setter
	void setCondition(int condition) { _croSt.condition = condition; }

	//데미지(hp) -
	void hitDamage(int damage) { _croSt.hp -= damage; }
	//최대hp +
	void plusMaxHP(int maxHP) { _croSt.maxHp += maxHP; }
	void setMaxHP(int maxHP) { _croSt.maxHp = maxHP; }//최대 hp setter

	//mp -
	void minusMP(int mp) { _croSt.mp -= mp; }
	//최대mp +
	void plusMaxMP(int maxMP) { _croSt.maxMp += maxMP; }
	void setMaxMP(int maxMP) { _croSt.maxMp = maxMP; }//최대 mp setter

	//소지금 +
	void plusMoney(int money) { _croSt.money += money; }
	void setMoney(int money) { _croSt.money = money; }//소지금 setter

	//경험치 +
	void plusExp(int exp) { _croSt.exp += exp; }
	//최대경험치 setter
	void setMaxExp(int maxExp) { _croSt.maxExp = maxExp; }


	//피격 등에 설정시킬 STATE setter
	void setState(STATE state) { _croSet.state = state; }

	//방향전환 T setter
	void setT(int T) { _T = T; }

	//트리거타임 setter
	void setTriggerTime(int triggerTime) { _croSet.triggerTime = triggerTime; }

	//아이템 공격력 setter
	void setItemAtk(int atk) { _itemSt.atk = atk; }
	//아이템 마력 setter
	void setItemMagic(int magic) { _itemSt.magic = magic; }
	//아이템 힘 setter
	void setItemPower(int power) { _itemSt.power = power; }
	//아이템 스피드 setter
	void setItemSpeed(int speed) { _itemSt.speed = speed; }
	//아이템 체력 setter
	void setItemStamina(int stamina) { _itemSt.stamina = stamina; }
	//아이템 민첩 setter
	void setItemHit(int hit) { _itemSt.hit = hit; }
	//아이템 회피 setter
	void setItemEvasion(int evasion) { _itemSt.evasion = evasion; }
	//아이템 최대 hp setter
	void setItemMaxHP(int maxHP) { _itemSt.maxHp = maxHP; }
	//아이템 최대 mp setter
	void setItemMaxMP(int maxMP) { _itemSt.maxMp = maxMP; }
	//아이템 특수능력 setter
	void setItemAbility(int ability) { _itemSt.ability = ability; }

	//getter

	//트리거타임 getter
	int getTriggerTime() { return _croSet.triggerTime; }

	//크로노 현재 공격력
	int getAtk() { return _croSt.atk; }
	//크로노 현재 마력
	int getMagic() { return _croSt.magic; }
	//크로노 현재 힘
	int getPower() { return _croSt.power; }
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

	//방향확인용 T getter
	int getT() { return _T; }

	//아이템 공격력 setter
	int getItemAtk() { return _itemSt.atk ; }
	//아이템 마력 setter
	int getItemMagic() { return _itemSt.magic ; }
	//아이템 힘 setter
	int getItemPower() { return _itemSt.power ; }
	//아이템 스피드 setter
	int getItemSpeed() { return  _itemSt.speed ; }
	//아이템 체력 setter
	int getItemStamina() { return _itemSt.stamina ; }
	//아이템 민첩 setter
	int getItemHit() { return  _itemSt.hit ; }
	//아이템 회피 setter
	int getItemEvasion() { return  _itemSt.evasion ; }
	//아이템 최대 hp setter
	int getItemMaxHP() { return  _itemSt.maxHp ; }
	//아이템 최대 mp setter
	int getItemMaxMP() { return  _itemSt.maxMp ; }
	//아이템 특수능력 setter
	int getItemAbility() { return _itemSt.ability ; }

	POINT& getPos() { return _croSet.pt; }

};

