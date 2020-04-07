#include "stdafx.h"
#include "deadScene.h"


deadScene::deadScene()
{
}


deadScene::~deadScene()
{
}

HRESULT deadScene::init()
{
	charcter = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 100, 100);
	pistolDeadImg = IMAGEMANAGER->addFrameImage("pistolDead", "images/unit/swat_pistol_dead.bmp", 1839, 467, 11, 4, true, RGB(255, 0, 255));
	rifleDeadImg = IMAGEMANAGER->addFrameImage("rifleDead", "images/unit/swat_rifle_dead.bmp", 2478, 665, 14, 4, true, RGB(255, 0, 255));
	shieldDeadImg = IMAGEMANAGER->addFrameImage("shieldDead", "images/unit/swat_shield_dead.bmp", 4320, 720, 24, 4, true, RGB(255, 0, 255));
	menuImg = IMAGEMANAGER->addImage("button", "images/UI/button.bmp", 300, 120, true, RGB(255, 0, 255));
	returnImg = IMAGEMANAGER->addImage("return","images/UI/back.bmp",55,55,true,RGB(255,0,255));
	selectUnit();
	animationEnd = false;
	count = 0;
	index = 0;
	if (isChange == false) {
		sound = 1.0f;
	}
	else {
		sound = SOUNDMANAGER->getVolume();
	}
	SOUNDMANAGER->play("dead", sound);  //노래 재생	

	return S_OK;
}

void deadScene::release()
{
}

void deadScene::update()
{
	deadImage();
	if (animationEnd == true) {
		menuRc = RectMakeCenter(WINSIZEX / 2, charcter.bottom + menuImg->getHeight(),menuImg->getWidth(), menuImg->getHeight());
		returnRc = RectMakeCenter(WINSIZEX / 2, menuRc.bottom + returnImg->getHeight()/2, returnImg->getHeight(), returnImg->getHeight());
		if (PtInRect(&returnRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			SOUNDMANAGER->stop("dead");
			SCENEMANAGER->changeScene("main");
		}
	}
}

void deadScene::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	if (pistol == true) {
		pistolDeadImg->frameRender(getMemDC(), charcter.left, charcter.top, pistolDeadImg->getFrameX(), pistolDeadImg->getFrameY());
	}
	if (rifle == true) {
		rifleDeadImg->frameRender(getMemDC(), charcter.left, charcter.top, rifleDeadImg->getFrameX(), rifleDeadImg->getFrameY());
	}
	if (shield == true) {
		shieldDeadImg->frameRender(getMemDC(), charcter.left, charcter.top, shieldDeadImg->getFrameX(), shieldDeadImg->getFrameY());
	}
	if (animationEnd == true) {	
		menuImg->render(getMemDC(), menuRc.left, menuRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		//색상
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		wsprintf(str, "사망하였습니다.");
		TextOut(getMemDC(), WINSIZEX / 2 - 50,((menuRc.bottom - menuRc.top)/2 + menuRc.top), str, strlen(str));

		returnImg->render(getMemDC(), returnRc.left, returnRc.top);
	}

}

void deadScene::selectUnit()
{
	if (inven->selectPistol() == true) {
		pistol = true;
		rifle = false;
		shield = false;
	}
	if (inven->selectRifle() == true) {
		pistol = false;
		rifle = true;
		shield = false;
	}
	if (inven->selectShiled() == true) {
		pistol = false;
		rifle = false;
		shield = true;
	}
}

void deadScene::deadImage()
{
	count++;
	if (pistol == true) {
		charcter = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, pistolDeadImg->getFrameWidth(), pistolDeadImg->getFrameHeight());
		pistolDeadImg->setFrameY(3); 	
		if (count % 10 == 0)
		{
			index++;
			if (index > 10)
			{
				index = 10;
				animationEnd = true;
			}
		}
		pistolDeadImg->setFrameX(index);
	}
	if (rifle == true) {
		charcter = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, rifleDeadImg->getFrameWidth(), rifleDeadImg->getFrameHeight());
		rifleDeadImg->setFrameY(3);
		if (count % 10 == 0)
		{
			index++;
			if (index > 13)
			{
				index = 13;
				animationEnd = true;
			}
		}
		rifleDeadImg->setFrameX(index);
	}
	if (shield == true) {
		charcter = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, shieldDeadImg->getFrameWidth(), shieldDeadImg->getFrameHeight());
		shieldDeadImg->setFrameY(3);
		if (count % 10 == 0)
		{
			index++;
			if (index > 23)
			{
				index = 23;
				animationEnd = true;
			}
		}
		shieldDeadImg->setFrameX(index);
	}
}


