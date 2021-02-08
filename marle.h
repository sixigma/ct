#pragma once
#include "gameNode.h"
#include"character.h"

class marle : public gameNode
{
private:
	tagStatus _marSt;		//마루 능력치
	tagStatus _itemSt;		//마루 아이템 능력치
	tagChaSet _marSet;		//마루 셋팅

	tagImage im;
	tagAni an;
	bool Cleft, _run;	//좌우반전, 달리기
	int _T;		//방향전환용 int(turn) / 0:front , 1:back , 2:right , 3:left
	int Cc;		//idle 상태의 눈깜빡임 카운트
	int hitCol;		//피격시 카운트
	bool Latk;		//원거리 공격 bool
	int Dcheck;		//다운 체크용 int
	int rad;	//임시(지름)
public:
	 marle() {};
	~marle() {};

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

	//마루 공격력
	void plusAtk(int atk) { _marSt.atk += atk; }
	void setAtk(int atk) { _marSt.atk = atk; }
	//마루 마력 +
	void plusMagic(int magic) { _marSt.magic += magic; }
	void setMagic(int magic) { _marSt.magic = magic; }//마력 setter
	//마루 힘 +
	void plusPower(int power) { _marSt.power += power; }
	void setPower(int power) { _marSt.power = power; }//힘 setter
	//마루 스피드 +
	void plusSpeed(int speed) { _marSt.speed += speed; }
	void setSpeed(int speed) { _marSt.speed = speed; }//스피드 setter
	//마루 체력 +
	void plusStamina(int stamina) { _marSt.stamina += stamina; }
	void setStamina(int stamina) { _marSt.stamina = stamina; }//체력 setter
	//마루 민첩 +
	void plusHit(int hit) { _marSt.hit += hit; }
	void setHit(int hit) { _marSt.hit = hit; }//민첩 setter
	//마루 회피 +
	void plusEvasion(int evasion) { _marSt.evasion += evasion; }
	void setEvasion(int evasion) { _marSt.evasion = evasion; }//회피 setter

	//컨디션(느려짐 등 상태이상) setter
	void setCondition(int condition) { _marSt.condition = condition; }

	//데미지(hp) -
	void hitDamage(int damage) { _marSt.hp -= damage; }
	//최대hp +
	void plusMaxHP(int maxHP) { _marSt.maxHp += maxHP; }
	void setMaxHP(int maxHP) { _marSt.maxHp = maxHP; }//최대 hp setter

	//mp -
	void minusMP(int mp) { _marSt.mp -= mp; }
	//최대mp +
	void plusMaxMP(int maxMP) { _marSt.maxMp += maxMP; }
	void setMaxMP(int maxMP) { _marSt.maxMp = maxMP; }//최대 mp setter

	//소지금 +
	void plusMoney(int money) { _marSt.money += money; }
	void setMoney(int money) { _marSt.money = money; }//소지금 setter

	//경험치 +
	void plusExp(int exp) { _marSt.exp += exp; }
	//최대경험치 setter
	void setMaxExp(int maxExp) { _marSt.maxExp = maxExp; }

	//피격 등에 설정시킬 STATE setter
	void setState(STATE state) { _marSet.state = state; }

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

	//마루 현재 힘
	int getPower() { return _marSt.power; }
	//마루 현재 마력
	int getMagic() { return _marSt.magic; }
	//마루 현재 스피드
	int getSpeed() { return _marSt.speed; }
	//마루 현재 체력
	int getStamina() { return _marSt.stamina; }
	//마루 현재 명중
	int getHit() { return _marSt.hit; }
	//마루 현재 회피
	int getEvasion() { return _marSt.evasion; }

	//마루 현재 컨디션
	int getCondition() { return _marSt.condition; }

	//마루 현재 hp
	int getHP() { return _marSt.hp; }
	//마루 현재 maxHP
	int getMaxHP() { return _marSt.maxHp; }

	//마루 현재 mp
	int getMP() { return _marSt.mp; }
	//마루 현재 maxMP
	int getMaxMP() { return _marSt.maxMp; }

	//마루 현재 소지금
	int getMoney() { return _marSt.money; }

	//마루 현재 경험치
	int getExp() { return _marSt.exp; }
	//마루 현재 최대경험치
	int getMaxExp() { return _marSt.maxExp; }
	//마루 현재 레벨
	int getLV() { return _marSt.Lv; }

	//피격 등을 확인할 STATE getter
	STATE getState() { return _marSet.state; }

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

	POINT& getPos() { return _marSet.pt; }

	bool white()
	{
		if (_marSet.state == BATTLE_HIT)
		{
			if (hitCol % 4 == 0)return true;
			else return false;
		}
		else return false;
	}


};

