#include "stdafx.h"
#include "maptoolScene.h"


maptoolScene::maptoolScene()
{
}


maptoolScene::~maptoolScene()
{
}

HRESULT maptoolScene::init()
{
	mapmade = new maptool;
	mapmade->init();

	IMAGEMANAGER->addImage("exitbutton", "images/UI/button.bmp", 300, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("no", "images/UI/falseBack.bmp", 60, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("yes", "images/UI/trueBack.bmp", 60, 60, true, RGB(255, 0, 255));
	isExit = false;
	isMenu = false;
	if (isChange == false) {
		sound = 1.0f;
	}
	else {
		sound = SOUNDMANAGER->getVolume();
	}

	SOUNDMANAGER->play("maptool", sound);  //노래 재생	

	return S_OK;
}

void maptoolScene::release()
{
	SAFE_DELETE(mapmade);
}

void maptoolScene::update()
{
	mapmade->update();
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) {
		isMenu = true;
		if (isExit == false) {
			isExit = true;
			backRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, IMAGEMANAGER->findImage("exitbutton")->getWidth(), IMAGEMANAGER->findImage("exitbutton")->getHeight());
			trueRc = RectMakeCenter(WINSIZEX / 2 - 2 * (IMAGEMANAGER->findImage("yes")->getWidth() / 2), backRc.bottom - (IMAGEMANAGER->findImage("yes")->getHeight() / 2), IMAGEMANAGER->findImage("yes")->getWidth(), IMAGEMANAGER->findImage("yes")->getHeight());
			falseRc = RectMakeCenter(WINSIZEX / 2 + 2 * (IMAGEMANAGER->findImage("no")->getWidth() / 2), backRc.bottom - (IMAGEMANAGER->findImage("yes")->getHeight() / 2), IMAGEMANAGER->findImage("no")->getWidth(), IMAGEMANAGER->findImage("no")->getHeight());
		}
		else if (isExit == true) {
			isExit = false;
			backRc = RectMakeCenter(WINSIZEX + 500, WINSIZEY / 2, IMAGEMANAGER->findImage("exitbutton")->getWidth(), IMAGEMANAGER->findImage("exitbutton")->getHeight());
			trueRc = RectMakeCenter(WINSIZEX + 500, WINSIZEY / 2, IMAGEMANAGER->findImage("yes")->getWidth(), IMAGEMANAGER->findImage("yes")->getHeight());
			falseRc = RectMakeCenter(WINSIZEX + 500, WINSIZEY / 2, IMAGEMANAGER->findImage("no")->getWidth(), IMAGEMANAGER->findImage("no")->getHeight());
		}
	}
	if (isMenu == true) {
		if (PtInRect(&trueRc, m_ptMouse)) {
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
				SOUNDMANAGER->stop("maptool");
				SCENEMANAGER->changeScene("main");
			}
		}
		if (PtInRect(&falseRc, m_ptMouse) ){
			if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
 				isExit = false;
				isMenu = false;
			}
		}
	}


}

void maptoolScene::render()
{
	mapmade->render();
	if (isExit == true) {
		SetBkMode(getMemDC(), TRANSPARENT);
		//색상
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		char str[256];
		//Rectangle(getMemDC(), backRc.left, backRc.top, backRc.right, backRc.bottom);
		IMAGEMANAGER->render("exitbutton", getMemDC(), backRc.left, backRc.top);

		sprintf_s(str, "뒤로 돌아가시겠습니까 ?");
		TextOut(getMemDC(), backRc.left + 70, ((backRc.bottom - backRc.top) / 2) + backRc.top - (backRc.bottom - backRc.top) / 3, str, strlen(str));

		//Rectangle(getMemDC(), trueRc.left, trueRc.top, trueRc.right, trueRc.bottom);
		IMAGEMANAGER->render("yes", getMemDC(), trueRc.left, trueRc.top);
		//Rectangle(getMemDC(), falseRc.left, falseRc.top, falseRc.right, falseRc.bottom);
		IMAGEMANAGER->render("no", getMemDC(), falseRc.left, falseRc.top);
	}
}
