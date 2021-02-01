#pragma once
#include "gameNode.h"
#include "character.h"
struct tagPlImage
{
	image* idle;		//보통
	image* walk;		//걷기
	image* run;			//달리기
	image* Bready;		//배틀 준비
	image* rush;		//달려들기
	image* atk;			//공격/크리
	image* spin;		//스핀
	image* hit;			//피격
	image* hit2;		//피격2		
	image* win;			//승리포즈
	image* Bwin;		//배틀 승리
	image* downs;		//쓰러지기 직전
	image* down;		//쓰러짐
	image* cantRun;		//달리다 벽에 부딪힐 때	
	image* drink;		//마시기		
	image* handsUp;		//손 올리기	
	image* ladder;		//사다리		
	image* tied;		//묶임		
	image* what;		//궁금		

};

struct tagPlAni
{
	animation* idle_front, *idle_back, *idle_right;			//서있을 때의 애니		front : 앞 / back : 뒤 / right : 오른쪽
	animation* walk_front, *walk_back, *walk_right;			//걸을 때의 애니			front : 앞 / back : 뒤 / right : 오른쪽
	animation* run_front, *run_back, *run_right;			//달릴 때의 애니			front : 앞 / back : 뒤 / right : 오른쪽
	animation* Bready_front, *Bready_back, *Bready_left;	//배틀 준비중의 애니		front : 앞 / back : 뒤 / left : 왼쪽
	animation* SB_front, *SB_back, *SB_left;				//스탠바이 중의 애니		front : 앞 / back : 뒤 / left : 왼쪽
	animation* rush_front, *rush_back, *rush_right;			//달려들 때의 애니		front : 앞 / back : 뒤 / right : 오른쪽
	animation* atk_front, *atk_back, *atk_right;			//공격할 때의 애니		front : 앞 / back : 뒤 / right : 오른쪽
	animation* cri_front, *cri_back, *cri_right;			//공격-크리티컬 때의 애니	front : 앞 / back : 뒤 / right : 오른쪽
	animation* hit_front, *hit_back, *hit_right;			//피격 때의 애니			front : 앞 / back : 뒤 / right : 오른쪽
	animation* hit2_front, *hit2_right;						//피격 때의 애니2			front : 앞 / back : 뒤
	animation* spin;										//스핀 때의 애니
	animation* downs_front, *downs_back, *downs_right;		//쓰러지기 직전의 애니	front : 앞 / back : 뒤 / right : 오른쪽
	animation* down;										//쓰러졌을 때의 애니		
	animation* Bwin_front, *Bwin_back, *Bwin_left;			//이겼을 때의 애니		front : 앞 / back : 뒤 / left : 왼쪽
	animation* win;											//승리포즈만 취할 때

	animation* cantRun_front, *cantRun_back, *cantRun_right;//못달린다				front : 앞 / back : 뒤 / right : 오른쪽
	animation* drink;										//마시기
	animation* handsUp_front, *handsUp_back;				//손들기					front : 앞 / back : 뒤
	animation* ladder;										//사다리					
	animation* tied_front, *tied_back, *tied_right;			//묶임					front : 앞 / back : 뒤 / right : 오른쪽
	animation* what_front, *what_back, *what_right;			//?						front : 앞 / back : 뒤 / right : 오른쪽
};

class player : public gameNode
{
private:
	tagStatus _Pst;			//플레이어 능력치
	tagChaSet _Pset;		//플레이어 셋팅
	tagItemStatus _PIst;	//플레이어 아이템 능력치

	tagPlImage im;
	tagPlAni an;
	bool Cleft, _run;	//좌우반전, 달리기
	int _T;		//방향전환용 int(turn) / 0:front , 1:back , 2:right , 3:left
	int Cc;		//idle 상태의 눈깜빡임 카운트

public:
	player() {};
	~player() {};

	HRESULT init();
	void release();
	void update();
	void render();

	void imgSetting();
	void aniSetting();
	void imgSwitch();		//이미지 보이는 방식이 들어간다
	void keySetting();	//키 입력 방식
	//void moveSwitch();	//이동시 스위치(벽부딪치기 등)
	//void battleSwitch();	//배틀시 스위치(공격시 렉트 등)

	//setter 
	
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

	//피격 등에 설정시킬 STATE setter
	void setState(STATE state) { _Pset.state = state; }

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

	//피격 등을 확인할 STATE getter
	STATE getState() { return _Pset.state; }

	//플레이어 현재 이름
	string getName() { return _Pset.name; }
};