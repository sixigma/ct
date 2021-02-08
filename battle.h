#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include <memory>
#include <queue>
#include <functional>

constexpr int maxTriggerTime = 2000;

class enemy;
class player;
class crono;
class lucca;

enum class BATTLE_STATE
{
	BATTLE_NOT_START_YET,		// 배틀 시작전의 상태
	BATTLE_POS_RDY,				// 배틀 위치를 잡을 떄의 상태
	BATTLE_UI_SHOWUP,			// 배틀 UI 시작
	BATTLE_ATK_RDY,				// 캐릭터 무기 준비
	BATTLE_RUNNING,				// 배틀 진행
	BATTLE_ALL_ENEMY_DOWN,		// 모든 적 다운,승리 모션 진행
	BATTLE_CHECK_REWARD_RDY,	// 얻은 아이템,골드,exp 확인 준비
	BATTLE_CHECK_REWARD_START,	// 얻은 아이템,골드,exp 확인
	BATTLE_UI_CLOSE,			// 배틀 ui 종료
	BATTLE_RES_PLAYER,			// 죽은 플레이어들 부활(플레이어가 전멸 아닐 때만)
	BATTLE_END					// 배틀 종료
};

class battle : public gameNode
{
private:

	queue<function<bool()>> _actionQueue;
	queue<string> _msgQueue;
	vector<gameNode*>* _playerVector;
	vector<enemy*>*	_enemyVector;
	vector<POINT>*	_PlBattleStartPos;
	vector<POINT>* _EmBattleStartPos;


	BATTLE_STATE _battleState;

	shared_ptr<progressBar> _plTurnBar[3], _emTurnBar[3];

	crono* _crono;
	lucca* _lucca;

	int arrowPointer;
	int preArrowPointer;
	int _msgIntervalCount;
	int _blinkCount[3]; // HP 10 이하일 때 사용하는 변수

	int _yOffset;

	bool _shouldPopUpAction[3];

	TEXT_WINDOW_STATE _textWindowState;

	HDC hTempDC;


	int _battleWindowOpeningCnt;
	int _battleWindowClipCount;
	int _enemyRemainingCnt;


public:
	battle();
	~battle() override;


	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;


	int getArrowPointer() { return arrowPointer; }
	//shared_ptr<progressBar> getp1TurnBar() { return _plTurnBar[]; }
	int& getBlinkCount(int i) { return _blinkCount[i]; }
	// void setBlinkCount(int newCount, int i) { _blinkCount[i] = newCount; }
	void updateBattleWindow();
	void renderBattleWindow();

	void init(vector<enemy*>* _enemyVector, vector<gameNode*>* _playerVector,
			  vector<POINT>* _PlBattleStartPos, vector<POINT>* _EmBattleStartPos );
};

