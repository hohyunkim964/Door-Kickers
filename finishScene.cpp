#include "stdafx.h"
#include "finishScene.h"


finishScene::finishScene()
{
}


finishScene::~finishScene()
{
}

HRESULT finishScene::init()
{	
	
	IMAGEMANAGER->addImage("1", "images/UI/1.bmp", 228, 93, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "images/UI/2.bmp", 228, 93, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("3", "images/UI/3.bmp", 228, 93, true, RGB(255, 0, 255));
	scoreRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 300, 100);
	IMAGEMANAGER->addImage("return", "images/UI/back.bmp", 55, 55, true, RGB(255, 0, 255));
	backRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2+200, IMAGEMANAGER->findImage("return")->getWidth(), IMAGEMANAGER->findImage("return")->getHeight());
	if (isChange == false) {
		sound = 1.0f;
	}
	else {
		sound = SOUNDMANAGER->getVolume();
	}
	SOUNDMANAGER->play("win", sound);  //노래 재생	

	return S_OK;
}

void finishScene::release()
{
}

void finishScene::update()
{
	if (score == 1) {
		scoreRc = RectMakeCenter(WINSIZEX - 2*(IMAGEMANAGER->findImage("1")->getWidth()), 2*IMAGEMANAGER->findImage("1")->getHeight(), IMAGEMANAGER->findImage("1")->getWidth(), IMAGEMANAGER->findImage("1")->getHeight());
	}
	if (score == 2) {
		scoreRc = RectMakeCenter(WINSIZEX - 2 * (IMAGEMANAGER->findImage("2")->getWidth()), 2*IMAGEMANAGER->findImage("2")->getHeight(), IMAGEMANAGER->findImage("2")->getWidth(), IMAGEMANAGER->findImage("2")->getHeight());
	}
	if (score == 3) {
		scoreRc = RectMakeCenter(WINSIZEX - 2 * (IMAGEMANAGER->findImage("3")->getWidth()), 2*IMAGEMANAGER->findImage("3")->getHeight(), IMAGEMANAGER->findImage("3")->getWidth(), IMAGEMANAGER->findImage("3")->getHeight());
	}
	if (PtInRect(&backRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		SOUNDMANAGER->stop("win");
		SCENEMANAGER->changeScene("main");
	}
	i = finishTime - startTime;
}

void finishScene::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	if (score == 1) {
		Rectangle(getMemDC(), scoreRc.left, scoreRc.top, scoreRc.right, scoreRc.bottom);
		IMAGEMANAGER->render("1", getMemDC(), scoreRc.left, scoreRc.top);
	}
	if (score == 2) {
		Rectangle(getMemDC(), scoreRc.left, scoreRc.top, scoreRc.right, scoreRc.bottom);
		IMAGEMANAGER->render("2", getMemDC(), scoreRc.left, scoreRc.top);
	}
	if (score == 3) {
		Rectangle(getMemDC(), scoreRc.left, scoreRc.top, scoreRc.right, scoreRc.bottom);
		IMAGEMANAGER->render("3", getMemDC(), scoreRc.left, scoreRc.top);
	}
	Rectangle(getMemDC(), backRc.left, backRc.top, backRc.right, backRc.bottom);
	IMAGEMANAGER->render("return", getMemDC(), backRc.left, backRc.top);

	SetBkMode(getMemDC(), TRANSPARENT);
	//색상
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	wsprintf(str, "승리");
	TextOut(getMemDC(), WINSIZEX / 2 ,WINSIZEY/2 - 10 , str, strlen(str));
	wsprintf(str, "플레이 타임 :  %d 초", (int)i);
	TextOut(getMemDC(), WINSIZEX / 2 - 50, WINSIZEY / 2 - 50, str, strlen(str));

}
