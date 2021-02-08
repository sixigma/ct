#pragma once
#include "gameNode.h"
#include "character.h"
class frog : public gameNode
{
private:
	tagStatus		_frogSt;	//개구리 능력치
	tagStatus		_itemSt;
	tagChaSet		_frogSet;	//개구리 셋팅

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
	void setPower(int power) { _frogSt.power = power; }//힘 setter
	//개구리 마력 +
	void plusMagic(int magic) { _frogSt.magic += magic; }
	void setMagic(int magic) { _frogSt.magic = magic; }//마력 setter
	//개구리 스피드 +
	void plusSpeed(int speed) { _frogSt.speed += speed; }
	void setSpeed(int speed) { _frogSt.speed = speed; }//스피드 setter
	//개구리 체력 +
	void plusStamina(int stamina) { _frogSt.stamina += stamina; }
	void setStamina(int stamina) { _frogSt.stamina = stamina; }//체력 setter
	//개구리 민첩 +
	void plusHit(int hit) { _frogSt.hit += hit; }
	void setHit(int hit) { _frogSt.hit = hit; }//민첩 setter
	//개구리 회피 +
	void plusEvasion(int evasion) { _frogSt.evasion += evasion; }
	void setEvasion(int evasion) { _frogSt.evasion = evasion; }//회피 setter

	//컨디션(느려짐 등 상태이상) setter
	void setCondition(int condition) { _frogSt.condition = condition; }

	//데미지(hp) -
	void hitDamage(int damage) { _frogSt.hp -= damage; }
	//최대hp +
	void plusMaxHP(int maxHP) { _frogSt.maxHp += maxHP; }
	void setMaxHP(int maxHP) { _frogSt.maxHp = maxHP; }//최대 hp setter

	//mp -
	void minusMP(int mp) { _frogSt.mp -= mp; }
	//최대mp +
	void plusMaxMP(int maxMP) { _frogSt.maxMp += maxMP; }
	void setMaxMP(int maxMP) { _frogSt.maxMp = maxMP; }//최대 mp setter

	//소지금 +
	void plusMoney(int money) { _frogSt.money += money; }
	void setMoney(int money) { _frogSt.money = money; }//소지금 setter

	//경험치 +
	void plusExp(int exp) { _frogSt.exp += exp; }
	//최대경험치 setter
	void setMaxExp(int maxExp) { _frogSt.maxExp = maxExp; }

	//피격 등에 설정시킬 STATE setter
	void setState(STATE state) { _frogSet.state = state; }

	//방향전환 T setter
	void setT(int T) { _T = T; }

	//트리거타임 setter
	void setTriggerTime(int triggerTime) { _frogSet.triggerTime = triggerTime; }

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
	int getTriggerTime() { return _frogSet.triggerTime; }

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

	//방향확인용 T getter
	int getT() { return _T; }

	//아이템 공격력 setter
	int getItemAtk() { return _itemSt.atk; }
	//아이템 마력 setter
	int getItemMagic() { return _itemSt.magic; }
	//아이템 힘 setter
	int getItemPower() { return _itemSt.power; }
	//아이템 스피드 setter
	int getItemSpeed() { return  _itemSt.speed; }
	//아이템 체력 setter
	int getItemStamina() { return _itemSt.stamina; }
	//아이템 민첩 setter
	int getItemHit() { return  _itemSt.hit; }
	//아이템 회피 setter
	int getItemEvasion() { return  _itemSt.evasion; }
	//아이템 최대 hp setter
	int getItemMaxHP() { return  _itemSt.maxHp; }
	//아이템 최대 mp setter
	int getItemMaxMP() { return  _itemSt.maxMp; }
	//아이템 특수능력 setter
	int getItemAbility() { return _itemSt.ability; }

	POINT& getPos() { return _frogSet.pt; }

};

