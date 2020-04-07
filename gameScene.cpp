#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{

	back = IMAGEMANAGER->addImage("gameLoad", "images/SCENE/credits.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	shopImage = IMAGEMANAGER->addImage("상점", "images/UI/상점.bmp", 100, WINSIZEY / 10, true, RGB(255, 0, 255));
	gameImage = IMAGEMANAGER->addImage("게임시작", "images/UI/게임시작.bmp", 100, WINSIZEY / 10, true, RGB(255, 0, 255));
	invenImage = IMAGEMANAGER->addImage("인벤", "images/UI/창고.bmp", 100, WINSIZEY / 10, true, RGB(255, 0, 255));
	shopRc = RectMakeCenter((WINSIZEX/3)/2,WINSIZEY/2,WINSIZEX/3,WINSIZEY);
	gameRc = RectMakeCenter(WINSIZEX/3 + (WINSIZEX / 3) / 2,WINSIZEY/2,WINSIZEX/3,WINSIZEY);
	invenRc = RectMakeCenter(2*(WINSIZEX/3) + (WINSIZEX / 3) / 2,WINSIZEY/2,WINSIZEX/3,WINSIZEY);
	transparency1 = 150;
	transparency2 = 150;
	transparency3 = 150;
	if (isChange == false) {
		sound = 1.0f;
	}
	else {
		sound = SOUNDMANAGER->getVolume();
	}
	
	SOUNDMANAGER->play("gameSelect", sound);  //노래 재생	

	return S_OK;
}

void gameScene::release()
{
	
}

void gameScene::update()
{	
	if (PtInRect(&shopRc, m_ptMouse)) {
		transparency1--;
		if (transparency1 < 20) {
			transparency1 = 20;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->stop("gameSelect");
			SCENEMANAGER->changeScene("shop");
		}
	}
	else {
		transparency1 = 150;
	}


	if (PtInRect(&invenRc, m_ptMouse)) {
		transparency2--;
		if (transparency2 < 20) {
			transparency2 = 20;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->stop("gameSelect");
			SCENEMANAGER->changeScene("inven");
		}
	}
	else {
		transparency2 = 150;
	}


	if (PtInRect(&gameRc, m_ptMouse)) {
		transparency3--;
		if (transparency3 < 20) {
			transparency3 = 20;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->stop("gameSelect");
			SCENEMANAGER->changeScene("inGame");
		}		
	}
	else {
		transparency3 = 150;
	}
}

void gameScene::render()
{
	IMAGEMANAGER->render("gameLoad", getMemDC());
	FrameRect(getMemDC(), &shopRc, CreateSolidBrush(RGB(255, 255, 255)));
	shopImage->alphaRender(getMemDC(), (WINSIZEX / 3) / 2, WINSIZEY / 2, transparency1);
	
	FrameRect(getMemDC(), &gameRc, CreateSolidBrush(RGB(255, 255, 255)));
	gameImage->alphaRender(getMemDC(), (WINSIZEX / 3)+ (WINSIZEX / 3) /3, WINSIZEY / 2, transparency3);
	FrameRect(getMemDC(), &invenRc, CreateSolidBrush(RGB(255, 255, 255)));
	invenImage->alphaRender(getMemDC(), 2*WINSIZEX /3 + (WINSIZEX / 3) / 2, WINSIZEY / 2, transparency2);
}
