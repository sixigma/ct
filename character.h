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

	int element;		//속성

	int condition;		//상태이상
};
enum STATE			//상태이넘
{
	NORMAL_IDLE,	//평상시
	NORMAL_WALK,	//걸을 때
	NORMAL_RUN,		//달릴 때
	NORMAL_TALK,	//대화할 때
	NORMAL_EVENT,	//이벤트
	NORMAL_READY,	//배틀 승리 후 주인공에게 모일 때
	BATTLE_READY,	//준비(배틀 시작시 각자리로 날아갈 때)
	BATTLE_STANDBY,	//대기
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
struct tagItemStatus	//아이템 능력치
{
	int weapon;			//무기		공격력+
	int weapon2;		//무기2		특수능력

	int head;			//머리		방어+
	int head2;			//머리2		특수능력

	int armor;			//갑옷		방어+
	int armor2;			//갑옷2		특수능력

	int acc;			//액세서리	능력치+
	int acc2;			//액세서리2	능력치+

	int money;			//구입 / 판매가격
};

struct tagChaSet	//캐릭터 셋팅
{
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
