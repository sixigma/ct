#pragma once

struct tagStatus	//능력치
{
	int power;			//힘(근접무기공격력 + )	(최대 100)
	int magic;			//마력(마법공격력)(최대 100)
	int speed;			//배틀시 게이지 차징속도 증가(최대16)(헤이스트 등 특정 스킬로 인한 max 24)
	int stamina;		//체력(방어력 + / 최대 hp +)(최대 100)
	int hit;			//명중(원거리 공격력)
	int evasion;		//회피

	int atk;			//공격력(힘 + 무기공격력)
	int def, Mdef;		//방어력, 마법방어력

	int hp, maxHp;		//체력, 최대체력
	int mp, maxMp;		//mp, 최대mp
	int exp, maxExp;	//경험치
	int Lv;				//레벨
	int money;			//돈

	int ability;		//특수능력(아이템)

	int element;		//속성

	int condition;		//상태이상

	int techPoint;		//기술 숙련도 점수
};
enum STATE			//상태이넘
{
	NORMAL_IDLE,	//평상시
	NORMAL_WALK,	//걸을 때
	NORMAL_RUN,		//달릴 때
	NORMAL_TALK,	//대화할 때
	NORMAL_EVENT,	//이벤트
	NORMAL_READY,	//배틀 승리 후 주인공에게 모일 때
	GETTING_READY,	//준비(배틀 시작시 각자리로 날아갈 때)
	BATTLE_READY,	//대기
	BATTLE_MOVE,	//배틀시 일반움직임
	BATTLE_RUSH,	//배틀시 달려들기
	BATTLE_ATK,		//근거리와 원거리 구분짓기
	BATTLE_SKILL,	//스킬
	BATTLE_RETURN,	//배틀시 공격 후 돌아오기
	BATTLE_HIT,		//피격
	BATTLE_HELP,	//배틀 중 hp가 0이 되었을 때 그로기상태
	BATTLE_WIN,	//승리시(경험치, 골드 등 얻을 때)
	BATTLE_LOSE	//패배시(전부가 hp0이 될 때)
};
struct tagChaSet	//캐릭터 셋팅
{
	int triggerTime;	//전투 타이머 변수

	POINT pt;			//캐릭터 포인트
	POINT atk;			//캐릭터 공격시 공격지점 포인트

	POINT atkS;			//공격시 출발포인트
	POINT shadow;		//위치 지정용 그림자
	float Dis;			//자신과 상대 사이의 거리
	float angle;		//자신과 상대 사이의 각도
	float Sangle;		//출발지점과 자신 사이 거리

	RECT rc;			//캐릭터 렉트
	RECT Arc;			//공격 렉트

	image* img;			//이미지
	animation* ani;		//애니
	image* Sha;			//그림자 이미지

	image* Bimg;		//슬로우 등에 사용할 뒷배경 이미지
	animation* Bani;	//슬로우 등에 사용할 뒷배경 애니

	image* Oimg;		//(Other)혼란 등의 상태이상에 사용될 이미지
	animation* Oani;	//(Other)혼란 등의 상태이상에 사용될 애니

	string weapon;		//캐릭터 현재 무기
	string head;		//캐릭터 현재 머리방어구
	string armor;		//캐릭터 현재 갑옷
	string acc; 		//캐릭터 현재 액세서리
	string name;		//캐릭터 이름

	STATE state;		//스테이트 이넘
};

struct tagImage
{
	image* idle;		//보통
	image* walk;		//걷기
	image* run;			//달리기
	image* Bready;		//배틀 준비
	image* rush;		//달려들기
	image* atk;			//공격/크리
	image* atk2;		//공격2(원거리)
	image* spin;		//스핀(크로노 스킬)
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
	image* skill;		//스킬
	image* skill2;		//스킬2
	image* skill3;		//스킬3
	image* smile;		//웃음
	image* glass;		//안경(루카)
};

struct tagAni
{
	//0 : front / 1 : back / 2 : right / 3 : left
	//보통은 위와 같이 적용되지만, 일부 이미지는 2장 / 1장만 있을 수도 있다

	animation* idle_0, *idle_1, *idle_2;					//서있을 때의 애니			0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* walk_0, *walk_1, *walk_2;					//걸을 때의 애니			0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* run_0, *run_1, *run_2;						//달릴 때의 애니			0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* Bready_0, *Bready_1, *Bready_3, *Bready_2;	//배틀 준비중의 애니		0 : 앞 / 1 : 뒤 / 3 : 왼쪽
	animation* SB_0, *SB_1, *SB_3, *SB_2;					//스탠바이 중의 애니		0 : 앞 / 1 : 뒤 / 3 : 왼쪽
	animation* rush_0, *rush_1, *rush_2;					//달려들 때의 애니			0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* atk_0, *atk_1, *atk_2;						//공격할 때의 애니			0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* cri_0, *cri_1, *cri_2;						//공격-크리티컬 때의 애니	0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* atk2_0, *atk2_1, *atk2_2;					//원거리 공격할 때의 애니	0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* hit_0, *hit_1, *hit_2;						//피격 때의 애니			0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* hit2_0, *hit2_2, *hit2_1;					//피격 때의 애니2			0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* spin;										//스핀 때의 애니
	animation* downs_0, *downs_1, *downs_2;					//쓰러지기 직전의 애니		0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* down;										//쓰러졌을 때의 애니		
	animation* down_0, *down_1, *down_2;					//쓰러졌을 때의 애니(방향이 나뉘어있을때 씀)
	animation* Bwin;										//이겼을 때의 애니(방향 상관없을 때 씀)
	animation* Bwin_0, *Bwin_1, *Bwin_3, *Bwin_2;			//이겼을 때의 애니			0 : 앞 / 1 : 뒤 / 3 : 왼쪽
	animation* win;											//승리포즈만 취할 때

	animation* cantRun_0, *cantRun_1, *cantRun_2;			//못달린다				0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* drink;										//마시기
	animation* handsUp_0, *handsUp_1;						//손들기					0 : 앞 / 1 : 뒤
	animation* ladder;										//사다리					
	animation* tied_0, *tied_1, *tied_2;					//묶임					0 : 앞 / 1 : 뒤 / 2 : 오른쪽
	animation* what_0, *what_1, *what_2;					//?						0 : 앞 / 1 : 뒤 / 2 : 오른쪽

	animation* skill_0, *skill_1, *skill_2, *skill_3;		//스킬
	animation* skill2_0, *skill2_1, *skill2_2, *skill2_3;	//스킬2
	animation* skill3_0, *skill3_1, *skill3_2, *skill3_3;	//스킬3
	animation* glass_0, *glass_2;							//안경 애니

	animation*  oneArr_0, *oneArr_1, *oneArr_2;	//한장의 애니일 때 / 각 숫자는 세로로 몇째줄인지 알려줌
	animation* twoArrT_0, *twoArrT_1, *twoArrT_2;	//두장의 애니일 때 / 반복할 때
	animation* twoArrF_0, *twoArrF_1, *twoArrF_2;	//두장의 애니일 때 / 반복 안할 때
};

