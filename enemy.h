#pragma once
#include "character.h"
#include "gameNode.h"

class crono;
class lucca;

struct tagEnemyImg
{

	image* idle;		//보통
	image* talk;		//대화
	image* move;		//이동
	image* rush;		//달려들기
	image* atk;			//공격/크리
	image* hit;			//피격
	image* down;		//쓰러짐	
	image* other1;		//부가연출1
	image* other2;		//부가연출2

};

struct tagEnemyAni

{
	animation* wait;	//전투전 대기중일 때
	animation* talk;	//대화할 때
	animation* idle_front, *idle_back, *idle_right, *idle_left;		//서있을 때의 애니		
	animation* move_front, *move_back, *move_right, *move_left;			//달릴 때의 애니			
	animation* SB_front, *SB_back, *SB_right, *SB_left;				//스탠바이 중의 애니		
	animation* rush_front, *rush_back, *rush_right, *rush_left;		//달려들 때의 애니		
	animation* atk_front, *atk_back, *atk_right, *atk_left;			//공격할 때의 애니	
	animation* hit_front, *hit_back, *hit_right, *hit_left;			//피격 때의 애니		
	animation* hit;	//피격 1장일 때
	animation* down;												//쓰러졌을 때의 애니		
	animation* Oth_F, *Oth_B, *Oth_L, *Oth_R;//임시로 만든 애니
};
	

class enemy : public gameNode
{
protected:
	STATE _State;
	tagStatus _Status;
	tagItemStatus _ItemStatus;
	tagChaSet _ChaSet;
	tagEnemyImg _Img;
	tagEnemyAni _Ani;

private:

	crono* _crono;
	lucca* _lucca;

public:
	enemy();
	~enemy();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool attack(float Distance);

	//getter
	int getEnemyExp() { return _Status.exp; }
	int getEnemyHP() { return _Status.hp; }
	int getTriggerTime() { return _ChaSet.triggerTime; }
	int getSpeed() { return _Status.speed; }

	//setter
	void setTriggerTime(int triggerTime) { _ChaSet.triggerTime = triggerTime; }
	void hitDamage(int damage) { _Status.hp -= min(damage, _Status.hp); }
	void setEnemyPos(POINT pt) { _ChaSet.pt = pt; }
};
