#include "stdafx.h"
#include "inGameScene.h"


inGameScene::inGameScene()
{

}


inGameScene::~inGameScene()
{
}

HRESULT inGameScene::init()
{

	game = new manager;
	game->init();
	uiRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 400, 100);
	play = TIMEMANAGER->getWorldTime();

	IMAGEMANAGER->addImage("exitbutton", "images/UI/button.bmp", 300, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("no", "images/UI/falseBack.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("yes", "images/UI/trueBack.bmp", 60, 60, true, RGB(255, 0, 255));
	
	isExit = false;
	isMenu = false;
	if (isChange == false) {
		sound = 0.5f;
	}
	else {
		sound = SOUNDMANAGER->getVolume();
	}
//	SOUNDMANAGER->play("inGame", sound);  //노래 재생	

	startTime = TIMEMANAGER->getWorldTime();
	score = 0;

	return S_OK;
}

void inGameScene::release()
{
	SAFE_DELETE(game);
}

void inGameScene::update(){	
	
	if (inven->selectPistol() == true || inven->selectRifle() == true || inven->selectShiled() == true) {
		game->update();

		if (game->getPlayerCollsion() == true) {

		}
		if (game->getEnemyCollsion() == true) {
		}

		if (game->getDead() == true) {
			SOUNDMANAGER->stop("inGame");
			SCENEMANAGER->changeScene("dead");			
		}
		else if (game->getFinsih() == true) {
			finishTime = TIMEMANAGER->getWorldTime();
			if (finishTime - startTime < 30.0f) {
				score = 3;
			}
			if (finishTime - startTime >= 30.0f && finishTime - startTime < 60.0f) {
				score = 2;
			}
			if (finishTime - startTime >= 60.0f) {
				score = 1;
			}
			SOUNDMANAGER->stop("inGame");
			SCENEMANAGER->changeScene("finish");			
		}
	}
	else {	
		time = TIMEMANAGER->getWorldTime() - startTime;
		if (time > 2.0f) {
			i = 9.0f - time;
			if (i <= 1.0f) {
				SOUNDMANAGER->stop("inGame");
				SCENEMANAGER->changeScene("gameScene");
			}
		}		
	}	
	
}

void inGameScene::render()
{
	
	if (inven->selectPistol() == true || inven->selectRifle() == true || inven->selectShiled() == true) {	
		game->render();
		
	}
	else
	{
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
		//Rectangle(getMemDC(), uiRc.left, uiRc.top, uiRc.right, uiRc.bottom);
		FrameRect(getMemDC(), &uiRc, CreateSolidBrush(RGB(255, 255, 255)));
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		if (time <= 3.0f) {
			wsprintf(str, "무기가 없는 관계로 게임에 입장이 불가 합니다.");
			TextOut(getMemDC(), WINSIZEX / 2 - 165, WINSIZEY / 2, str, strlen(str));
		}
		else {
			wsprintf(str, "%d초 후 게임 메뉴로 돌아갑니다.",(int)i);
			TextOut(getMemDC(), WINSIZEX / 2 - 110, WINSIZEY / 2, str, strlen(str));
		}
	}
	wsprintf(str, "%f",startTime);
	TextOut(getMemDC(), 0, WINSIZEY / 2, str, strlen(str));
	wsprintf(str, "%f", finishTime);
	TextOut(getMemDC(), 0, WINSIZEY / 2 +100, str, strlen(str));

}
