#pragma once
#include "singleton.h"
#include <fstream>
#include <queue>
#include "fontParser.h"
#include <sstream>

// 대사 창 상태
enum class TEXT_WINDOW_STATE
{
	INVISIBLE, // 화면에 보이지 않는 상태(갱신하지 않는다.)
	OPENING, // 열리고 있는 상태
	VISIBLE, // 화면에 보이는 상태
	CLOSING // 닫히고 있는 상태
};

class fontParser;

class textManager : public singleton<textManager>
{
private:
	BOOL _shouldWindowUseTheTopPane;
	BOOL _shouldWindowHaveChoices; // 선택지용 변수
	int _choiceSelected; // 선택지용 변수(1: 처음 답; 2: 두 번째 답)
	BOOL _shouldBeAutoClosed;
	BOOL _isWholeCurrStrShown;
	fontParser* _fP;
	vector<CD>* fontInfo;
	HDC _hTextWindowDC;
	HBITMAP _hTextWindowBitmap, _hOTextWindowBitmap;
	int _currPosX, _currPosY, _waitCount; // 글 출력용 변수
	int _windowClipCount; // 창을 열고 닫을 때 쓰는 변수
	int _battleMsgCount; // 전투 메시지 표시 시간을 계산할 때 쓰는 변수

	image* _currFontImage;
	TEXT_WINDOW_STATE _textWindowState;
	//HRGN _hClipRegion;
	queue<pair<int, string>> _dialogLineQ;
	queue<pair<bool, string>> _battleMsgQ;

	istringstream iSS;
	char _character;

	void setCurrFontImage(int searchValue);

public:
	textManager();
	~textManager();

	void prepareToUseFonts();

	HRESULT init();
	void release();

	void toggleTextWindowPos() { _shouldWindowUseTheTopPane = !_shouldWindowUseTheTopPane; }

	// 출력할 대사 스트링을 대기열에 추가하는 함수
	void enqueueLine(string line, int forWhichChoice = 0);

	// 출력할 전투 메시지를 대기열에 추가하는 함수(isShownLetterByLetter로 한 번에 한 줄을 전부 출력할지 여부를 지정한다.)
	void enqueueMsg(string line, bool isShownLetterByLetter = false);

	// 대사 스트링 대기열을 비우는 함수
	void clearLineQ();

	// 전투 메시지 스트링 대기열을 비우는 함수
	void clearBattleMsg();

	// 현 상태에 맞게 출력할 대사 스트링을 준비하는 함수(_currStr 사용)
	void updateDialog();

	// 현 상태에 맞게 출력할 전투 메시지 스트링을 준비하는 함수(_currStr 사용)
	void updateBattleMsg();

	// 글 출력 창 상태를 설정하는 함수(0 INVISIBLE, 1 OPENING, 2 VISIBLE, 3 CLOSING)
	void setTextWindowState(int value) { _textWindowState = static_cast<TEXT_WINDOW_STATE>(value); }

	// 글 출력 창 상태를 반환하는 함수
	TEXT_WINDOW_STATE getTextWindowState() { return _textWindowState; }

	// 글 출력 창 스킨과 스트링을 출력하는 함수(창 표시 후 일정 간격마다 글자 하나 더 출력한다.)
	void renderDialog(HDC hDC, int fontIdx = 0, int colorIdx = 0);

	// 글 출력 창 스킨과 전투 메시지 스트링을 출력하는 함수(각 메시지 창이 닫히는 속도는 _battleMsgSpeed에 의존한다.)
	void renderBattleMsg(HDC hDC, int fontIdx = 0, int colorIdx = 0);

	// 특정 스트링을 즉시 출력하는 함수
	// fontIdx: 0 가변 폭(기본), 1 고정 폭
	// colorIdx: 0 하양(기본), 1 하늘, 2 빨강, 3 노랑, 4 초록, 5 비활성 색
	// 참고(기본 글꼴): \n 개행, { 음표, | 하트, } 줄임표, ` 쌍따옴표 열기, ~ 무한대
	void render(HDC hDC, string text, int destX = 0, int destY = 0, int fontIdx = 0, int colorIdx = 0);

	// 선택지 변수를 초기화하는 함수
	void resetChoiceSelected() { _choiceSelected = 0; }
};

