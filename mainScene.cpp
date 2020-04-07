#include "stdafx.h"
#include "mainScene.h"




mainScene::mainScene()
{
}


mainScene::~mainScene()
{
}

HRESULT mainScene::init()
{


	
	IMAGEMANAGER->addImage("title", "images/scene/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button", "images/UI/button.bmp", 200, 55, true, RGB(255, 0, 255));
	gameButton = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	mapToolButton = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 80, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	soundButton = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 160, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	exitButton = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 240, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	
	SOUNDMANAGER->addSound("inGame", "sound/on_sight.mp3", false, true);
	SOUNDMANAGER->addSound("gameSelect", "sound/asymmetric_tactics.mp3", false, true);
	SOUNDMANAGER->addSound("mainGame", "sound/alpha.mp3", false, true);
	SOUNDMANAGER->addSound("maptool", "sound/tactical_intervention.mp3", false, true);
	SOUNDMANAGER->addSound("win", "sound/승리.mp3", false, true);
	SOUNDMANAGER->addSound("dead", "sound/Russian_Celebration.mp3", false, true);
	SOUNDMANAGER->addSound("shop", "sound/hazardous_devices.mp3", false, true);

	

	if (isChange == false) {
		sound = 1.0f;
	}
	else{
		sound = SOUNDMANAGER->getVolume();
	}
	SOUNDMANAGER->play("mainGame", sound);  //노래 재생	

	return S_OK;
}

void mainScene::release()
{
}

void mainScene::update()
{
	if (PtInRect(&gameButton, m_ptMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		SOUNDMANAGER->stop("mainGame");
		SCENEMANAGER->changeScene("gameScene");
	}

	if (PtInRect(&mapToolButton, m_ptMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		SOUNDMANAGER->stop("mainGame");
		SCENEMANAGER->changeScene("maptool");
	}

	if (PtInRect(&soundButton, m_ptMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		
		SOUNDMANAGER->stop("mainGame");
		SCENEMANAGER->changeScene("sound");
	}

	if (PtInRect(&exitButton, m_ptMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		exit(0);
	}
}

void mainScene::render()
{
	IMAGEMANAGER->findImage("title")->render(getMemDC());

	IMAGEMANAGER->findImage("button")->render(getMemDC(), gameButton.left, gameButton.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 25, WINSIZEY / 2 - 10, "START", 5);
	IMAGEMANAGER->findImage("button")->render(getMemDC(), mapToolButton.left, mapToolButton.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 30, WINSIZEY / 2 + 70, "MAPTOOL", 7);
	IMAGEMANAGER->findImage("button")->render(getMemDC(), soundButton.left, soundButton.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 27, WINSIZEY / 2 + 150, "OPTION", 6);
	IMAGEMANAGER->findImage("button")->render(getMemDC(), exitButton.left, exitButton.top);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	TextOut(getMemDC(), WINSIZEX / 2 - 15, WINSIZEY / 2 + 230, "EXIT", 4);
}
