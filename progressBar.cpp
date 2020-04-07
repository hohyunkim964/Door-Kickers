#include "stdafx.h"
#include "progressBar.h"
progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(char * frontImage, char * backImage, float x, float y, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	_progressBarFront = new image;
	_progressBarFront->init(frontImage, x, y, width, height, true, RGB(255, 0, 255));

	_progressBarBack = new image;
	_progressBarBack->init(backImage, x, y, width, height, true, RGB(255, 0, 255));


	_width = _progressBarFront->getWidth();

	return S_OK;
}

void progressBar::release()
{
	SAFE_DELETE(_progressBarFront);
	SAFE_DELETE(_progressBarBack);
}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		_progressBarBack->getWidth(), _progressBarBack->getHeight());
}

void progressBar::render()
{
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	_progressBarFront->render(getMemDC(),_rcProgress.left, _y, 0, 0, _width, _progressBarBack->getHeight());

}
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge)* _progressBarBack->getWidth();
}
