#include "stdafx.h"
#include "progressBar.h"

HRESULT progressBar::init(int x, int y, int width, int height)
{
	_x = static_cast<float>(x);
	_y = static_cast<float>(y);

	_rctProgress = MakeRct(x, y, width, height);

	_progressBarFront = IMG->add("frontBar", "res/images/progressBars/fullBarInActive.bmp", width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMG->add("backBar", "res/images/progressBars/emptyBar.bmp", width, height, true, RGB(255, 0, 255));
	IMG->add("fullBar", "res/images/progressBars/fullBar.bmp", width, height, true, RGB(255, 0, 255));
	_width = static_cast<float>(_progressBarFront->getWidth());

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rctProgress = MakeRctC(static_cast<int>(_x), static_cast<int>(_y), _progressBarFront->getWidth(), _progressBarFront->getHeight());
}

void progressBar::render()
{
	IMG->renderZ(5001,"backBar", getMemDC(),
		_rctProgress.left + _progressBarBack->getWidth() / 2,
		static_cast<int>(_y) + _progressBarBack->getHeight() / 2, 0, 0,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());

	IMG->renderZ(5002, _progressBarFront,getMemDC(),
		_rctProgress.left + _progressBarFront->getWidth() / 2,
		static_cast<int>(_y) + _progressBarFront->getHeight() / 2, 0, 0,
		static_cast<int>(_width), _progressBarFront->getHeight());
}

void progressBar::setGauge(float currVal, float maxVal)
{
	

	if (abs(currVal - maxVal) < FLT_EPSILON)
	{
		_width = _progressBarBack->getWidth();
		_progressBarFront = IMG->find("fullBar");
	}
	else
	{
		_width = (currVal / maxVal) * (_progressBarBack->getWidth() - 32) + 16;
		_progressBarFront = IMG->find("frontBar");
	}
}

void progressBar::updateGauge(float currVal, float maxVal)
{
	if (currVal < FLT_EPSILON)
	{
		_width = 0; return;
	}

	float targetWidth = (currVal / maxVal) * _progressBarBack->getWidth();

	if (abs(currVal - maxVal) < FLT_EPSILON)
	{
		_width = targetWidth;
	}
	else if (_width < ((currVal - 1.f) / maxVal) * _progressBarBack->getWidth())
	{
		_width = ((currVal - 1.f) / maxVal) * _progressBarBack->getWidth();
	}
	else
	{
		if (abs(targetWidth - _width) > 4.f) _width += 4.f * (targetWidth - _width) / abs(targetWidth - _width);
		else _width = targetWidth;
	}
}
