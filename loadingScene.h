#pragma once
#include "gameNode.h"

constexpr int MAX_SLEEP_CALLS = 100;
constexpr int PROGRESS_PIE_OUTER_RADIUS = 40;
constexpr int PROGRESS_PIE_INNER_DIAMETER = (PROGRESS_PIE_OUTER_RADIUS * 2) - 10;

class loadingScene: public gameNode
{
private:
	HDC	_hTempDC, _hPrgDC;
	HBITMAP _hBitmap, _hOBitmap, _hPrgBitmap, _hOPrgBitmap;
	HBRUSH _hBrush[4], _hOBrush;
	HPEN _hPrgPen, _hOPrgPen;
	HANDLE _hThread;
	vector<POINT> _needleVertices;
	float _progressRatio, _progressPieAngle, _relSecondEndPointX, _relSecondEndPointY;

public:
	loadingScene();
	~loadingScene() override;

	int _currentCount;

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	static unsigned CALLBACK threadFunc(LPVOID params);

	void playerImgs();
	void enemyImgs();
};

