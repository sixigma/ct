#include "stdafx.h"
#include "loadingScene.h"
#include "gameScene.h"
#include "startScene.h"
#include <process.h> // _beginthreadex

loadingScene::loadingScene(): _currentCount(0), _progressPieAngle(0), _relSecondEndPointX(PROGRESS_PIE_OUTER_RADIUS), _relSecondEndPointY(PROGRESS_PIE_OUTER_RADIUS * 2) {}

loadingScene::~loadingScene() {}

HRESULT loadingScene::init()
{
	_hTempDC = CreateCompatibleDC(getMemDC());
	_hBitmap = CreateCompatibleBitmap(getMemDC(), WINW, WINH);
	_hOBitmap = (HBITMAP)SelectObject(_hTempDC, _hBitmap);
	_hBrush[0] = CreateSolidBrush(RGB(10, 255, 255)); // 하늘색
	_hBrush[1] = CreateSolidBrush(RGB(255, 255, 10)); // 노란색
	_hBrush[2] = CreateSolidBrush(RGB(255, 10, 10)); // 빨간색
	_hBrush[3] = CreateSolidBrush(RGB(132, 255, 148)); // 녹색
	_hOBrush = (HBRUSH)SelectObject(_hTempDC, _hBrush[0]);

	_hPrgDC = CreateCompatibleDC(getMemDC());
	_hPrgBitmap = CreateCompatibleBitmap(getMemDC(), PROGRESS_PIE_OUTER_RADIUS * 2, PROGRESS_PIE_OUTER_RADIUS * 2);
	_hOPrgBitmap = (HBITMAP)SelectObject(_hPrgDC, _hPrgBitmap);
	_hPrgPen = CreatePen(PS_NULL, 1, NULL);
	_hOPrgPen = (HPEN)SelectObject(_hPrgDC, _hPrgPen);
	SelectObject(_hPrgDC, GetStockObject(DC_BRUSH));

	_hThread = (HANDLE)_beginthreadex(NULL, 0, threadFunc, this, CREATE_SUSPENDED, NULL);
	if (!_hThread)
	{
		return E_FAIL;
	}
	ResumeThread(_hThread);

	return S_OK;
}

void loadingScene::release()
{
	SelectObject(_hPrgDC, _hOPrgPen);
	SelectObject(_hTempDC, _hOBrush);
	DeleteObject(_hPrgPen);
	DeleteObject(_hBrush[0]);
	DeleteObject(_hBrush[1]);
	DeleteObject(_hBrush[2]);
	DeleteObject(_hBrush[3]);
	DeleteObject(SelectObject(_hTempDC, _hOBitmap));
	DeleteObject(SelectObject(_hPrgDC, _hOPrgBitmap));
	DeleteDC(_hTempDC);
	DeleteDC(_hPrgDC);
}

void loadingScene::update()
{
	_progressRatio = static_cast<float>(_currentCount) / static_cast<float>(MAX_SLEEP_CALLS);
	_progressPieAngle = _progressRatio * PI2;
	_relSecondEndPointX = static_cast<float>(PROGRESS_PIE_OUTER_RADIUS) + static_cast<float>(PROGRESS_PIE_OUTER_RADIUS) * sinf(_progressPieAngle);
	_relSecondEndPointY = static_cast<float>(PROGRESS_PIE_OUTER_RADIUS) - static_cast<float>(PROGRESS_PIE_OUTER_RADIUS) * cosf(_progressPieAngle);
}

void loadingScene::render()
{
	PatBlt(_hPrgDC, 0, 0, PROGRESS_PIE_OUTER_RADIUS * 2, PROGRESS_PIE_OUTER_RADIUS * 2, BLACKNESS);
	SetDCBrushColor(_hPrgDC, RGB(71, 71, 71));
	Ellipse(_hPrgDC, 0, 0, PROGRESS_PIE_OUTER_RADIUS * 2, PROGRESS_PIE_OUTER_RADIUS * 2);
	SetDCBrushColor(_hPrgDC, RGB(216 - static_cast<int>(_progressRatio * 20.f), 176 + static_cast<int>(_progressRatio * 79.f), 64));
	Pie(_hPrgDC, 0, 0, PROGRESS_PIE_OUTER_RADIUS * 2, PROGRESS_PIE_OUTER_RADIUS * 2,
		static_cast<int>(_relSecondEndPointX), static_cast<int>(_relSecondEndPointY), PROGRESS_PIE_OUTER_RADIUS, 0);
	SetDCBrushColor(_hPrgDC, RGB(0, 0, 0));
	Ellipse(_hPrgDC, 10, 10, PROGRESS_PIE_INNER_DIAMETER, PROGRESS_PIE_INNER_DIAMETER);
	BitBlt(getMemDC(),
		   WINW - PROGRESS_PIE_OUTER_RADIUS * 2 - 20, WINH - PROGRESS_PIE_OUTER_RADIUS * 2 - 20,
		   WINW - PROGRESS_PIE_OUTER_RADIUS * 2, WINH - PROGRESS_PIE_OUTER_RADIUS * 2,
		   _hPrgDC, 0, 0, SRCCOPY);

	// 로딩 완료 시
	if (_currentCount == MAX_SLEEP_CALLS)
	{
		CloseHandle(_hThread);
		SC->changeScene("시작 화면");
	}
}

unsigned CALLBACK loadingScene::threadFunc(LPVOID params)
{
	loadingScene* loadingParams = (loadingScene*)params;

	// 장면
	SC->addScene("시작 화면", new startScene);
	SC->addScene("게임 장면", new gameScene);
	++loadingParams->_currentCount;
	
	// 시작 화면 그림

	++loadingParams->_currentCount;

	// 맵 그림

	++loadingParams->_currentCount;

	// 캐릭터 그림
	loadingParams->playerImgs(); ++loadingParams->_currentCount;
	loadingParams->enemyImgs(); ++loadingParams->_currentCount;

	// 화면 배경 그림
	IMG->add("검은 화면", "res/images/blackBg.bmp", WINW, WINH);
	++loadingParams->_currentCount;

	// 기타 그림
	IMG->addF("텍스트 창 스킨 셋", "res/images/textWindowSkins.bmp", 1024, 2560, 1, 8);
	IMG->addF("흰색 타일셋0", "res/images/tilesets/tileset0.bmp", 384, 256, 12, 8, TRUE, RGB(255, 0, 255));
	IMG->addF("비활성 타일셋0", "res/images/tilesets/tileset0Inactive.bmp", 384, 256, 12, 8, TRUE, RGB(255, 0, 255));
	IMG->addF("하늘색 타일셋0", "res/images/tilesets/tileset0.bmp", 384, 256, 12, 8, TRUE, RGB(255, 0, 255));
	IMG->addF("빨간색 타일셋0", "res/images/tilesets/tileset0.bmp", 384, 256, 12, 8, TRUE, RGB(255, 0, 255));
	IMG->addF("노란색 타일셋0", "res/images/tilesets/tileset0.bmp", 384, 256, 12, 8, TRUE, RGB(255, 0, 255));
	IMG->addF("녹색 타일셋0", "res/images/tilesets/tileset0.bmp", 384, 256, 12, 8, TRUE, RGB(255, 0, 255));
	IMG->add("흰색 대화 글꼴", "res/fonts/dialogGlyphs.bmp", 456, 240, TRUE, RGB(255, 0, 255));
	IMG->add("흰색 UI 글꼴", "res/fonts/monoGlyphs.bmp", 512, 160, TRUE, RGB(255, 0, 255));
	IMG->add("비활성 대화 글꼴", "res/fonts/dialogGlyphsInactive.bmp", 456, 240, TRUE, RGB(255, 0, 255));
	IMG->add("비활성 UI 글꼴", "res/fonts/monoGlyphsInactive.bmp", 512, 160, TRUE, RGB(255, 0, 255));
	IMG->add("하늘색 대화 글꼴", "res/fonts/dialogGlyphs.bmp", 456, 240, TRUE, RGB(255, 0, 255));
	IMG->add("하늘색 UI 글꼴", "res/fonts/monoGlyphs.bmp", 512, 160, TRUE, RGB(255, 0, 255));
	IMG->add("빨간색 대화 글꼴", "res/fonts/dialogGlyphs.bmp", 456, 240, TRUE, RGB(255, 0, 255));
	IMG->add("빨간색 UI 글꼴", "res/fonts/monoGlyphs.bmp", 512, 160, TRUE, RGB(255, 0, 255));
	IMG->add("녹색 대화 글꼴", "res/fonts/dialogGlyphs.bmp", 456, 240, TRUE, RGB(255, 0, 255));
	IMG->add("녹색 UI 글꼴", "res/fonts/monoGlyphs.bmp", 512, 160, TRUE, RGB(255, 0, 255));
	IMG->add("노란색 대화 글꼴", "res/fonts/dialogGlyphs.bmp", 456, 240, TRUE, RGB(255, 0, 255));
	IMG->add("노란색 UI 글꼴", "res/fonts/monoGlyphs.bmp", 512, 160, TRUE, RGB(255, 0, 255));
	++loadingParams->_currentCount;

	// 실제 그림 색상 변경
	// 하늘색
	PatBlt(loadingParams->_hTempDC, 0, 0, 384, 256, PATCOPY);
	BitBlt(IMG->find("하늘색 타일셋0")->getMemDC(), 0, 0, 384, 256, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("하늘색 타일셋0")->changeColor(RGB(255, 0, 255) & RGB(10, 255, 255), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 456, 240, PATCOPY);
	BitBlt(IMG->find("하늘색 대화 글꼴")->getMemDC(), 0, 0, 456, 240, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("하늘색 대화 글꼴")->changeColor(RGB(255, 0, 255) & RGB(10, 255, 255), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 512, 160, PATCOPY);
	BitBlt(IMG->find("하늘색 UI 글꼴")->getMemDC(), 0, 0, 512, 160, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("하늘색 UI 글꼴")->changeColor(RGB(255, 0, 255) & RGB(10, 255, 255), RGB(255, 0, 255));
	// 노란색
	SelectObject(loadingParams->_hTempDC, loadingParams->_hBrush[1]);
	PatBlt(loadingParams->_hTempDC, 0, 0, 384, 256, PATCOPY);
	BitBlt(IMG->find("노란색 타일셋0")->getMemDC(), 0, 0, 384, 256, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("노란색 타일셋0")->changeColor(RGB(255, 0, 255) & RGB(255, 255, 10), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 456, 240, PATCOPY);
	BitBlt(IMG->find("노란색 대화 글꼴")->getMemDC(), 0, 0, 456, 240, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("노란색 대화 글꼴")->changeColor(RGB(255, 0, 255) & RGB(255, 255, 10), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 512, 160, PATCOPY);
	BitBlt(IMG->find("노란색 UI 글꼴")->getMemDC(), 0, 0, 512, 160, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("노란색 UI 글꼴")->changeColor(RGB(255, 0, 255) & RGB(255, 255, 10), RGB(255, 0, 255));
	// 빨간색
	SelectObject(loadingParams->_hTempDC, loadingParams->_hBrush[2]);
	PatBlt(loadingParams->_hTempDC, 0, 0, 384, 256, PATCOPY);
	BitBlt(IMG->find("빨간색 타일셋0")->getMemDC(), 0, 0, 384, 256, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("빨간색 타일셋0")->changeColor(RGB(255, 0, 255) & RGB(255, 10, 10), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 456, 240, PATCOPY);
	BitBlt(IMG->find("빨간색 대화 글꼴")->getMemDC(), 0, 0, 456, 240, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("빨간색 대화 글꼴")->changeColor(RGB(255, 0, 255) & RGB(255, 10, 10), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 512, 160, PATCOPY);
	BitBlt(IMG->find("빨간색 UI 글꼴")->getMemDC(), 0, 0, 512, 160, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("빨간색 UI 글꼴")->changeColor(RGB(255, 0, 255) & RGB(255, 10, 10), RGB(255, 0, 255));
	// 녹색
	SelectObject(loadingParams->_hTempDC, loadingParams->_hBrush[3]);
	PatBlt(loadingParams->_hTempDC, 0, 0, 384, 256, PATCOPY);
	BitBlt(IMG->find("녹색 타일셋0")->getMemDC(), 0, 0, 384, 256, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("녹색 타일셋0")->changeColor(RGB(255, 0, 255) & RGB(132, 255, 148), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 456, 240, PATCOPY);
	BitBlt(IMG->find("녹색 대화 글꼴")->getMemDC(), 0, 0, 456, 240, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("녹색 대화 글꼴")->changeColor(RGB(255, 0, 255) & RGB(132, 255, 148), RGB(255, 0, 255));
	PatBlt(loadingParams->_hTempDC, 0, 0, 512, 160, PATCOPY);
	BitBlt(IMG->find("녹색 UI 글꼴")->getMemDC(), 0, 0, 512, 160, loadingParams->_hTempDC, 0, 0, SRCAND);
	IMG->find("녹색 UI 글꼴")->changeColor(RGB(255, 0, 255) & RGB(132, 255, 148), RGB(255, 0, 255));
	++loadingParams->_currentCount;

	ifstream file;
	string line;
	// 배경음
	//file.open("res/bgm/fileList.txt");
	//if (file.is_open())
	//{
	//	while (getline(file, line))
	//	{
	//		if (line == "3 - Title Screen.mp3")
	//		{
	//			SND->addSound(line, "res/bgm/3 - Title Screen.mp3", true, false);
	//		}
	//		else
	//		{
	//			SND->addSound(line, "res/bgm/" + line, true, true);
	//		}
	//	}
	//}
	//file.close();
	++loadingParams->_currentCount;

	// 효과음
	//file.open("res/sfx/fileList.txt");
	//if (file.is_open())
	//{
	//	while (getline(file, line))
	//	{
	//		SND->addSound(line, "res/sfx/" + line, false, false);
	//	}
	//}
	//file.close();
	++loadingParams->_currentCount;

	// 글꼴 사용 준비
	TXT->prepareToUseFonts();

	while (loadingParams->_currentCount != MAX_SLEEP_CALLS)
	{
		Sleep(1);
		++loadingParams->_currentCount;
	}
	return 0;
}

void loadingScene::playerImgs()
{

}

void loadingScene::enemyImgs()
{

}