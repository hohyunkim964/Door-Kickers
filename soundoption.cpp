#include "stdafx.h"
#include "soundoption.h"

HRESULT soundoption::init()
{
	IMAGEMANAGER->addImage("buttonUI", "images/UI/back.bmp", 55, 55, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("cursor", "images/UI/cursor.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("soundbar", "images/UI/사운드바.bmp", 550, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mute", "images/UI/mute.bmp", 100, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background", "images/Scene/title.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_bgImage = IMAGEMANAGER->addImage("black", "images/UI/black.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	soundBar = RectMakeCenter(WINSIZEX / 2 + 100, WINSIZEY / 2, 550, 30);
	cursorX = (soundBar.right - soundBar.left) / 2 + soundBar.left;
	cursor = RectMakeCenter(WINSIZEX / 2 + 100 + cursorX, WINSIZEY / 2, 50, 50);
	_mute = RectMakeCenter(WINSIZEX / 2 - 300, WINSIZEY / 2, 100, 100);
	_backRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200, IMAGEMANAGER->findImage("buttonUI")->getWidth(), IMAGEMANAGER->findImage("buttonUI")->getHeight());

	if (isChange == false) {
		sound = 1.0f;
	}
	else {
		sound = SOUNDMANAGER->getVolume();
	}
	SOUNDMANAGER->play("gameSelect", sound);  //노래 재생	

	return S_OK;
}

void soundoption::release()
{

}

void soundoption::update()
{
	cursorPostion();
	volume();
	mute();
	if (PtInRect(&_backRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isChange = true;
		SOUNDMANAGER->stop("gameSelect");
		SCENEMANAGER->changeScene("main");
	}
}

void soundoption::render()
{

	IMAGEMANAGER->render("background", getMemDC());
	_bgImage->alphaRender(getMemDC(), 150);

	IMAGEMANAGER->render("soundbar", getMemDC(), soundBar.left, soundBar.top);

	IMAGEMANAGER->render("cursor", getMemDC(), cursor.left, cursor.top);

	IMAGEMANAGER->render("mute", getMemDC(), _mute.left, _mute.top);
	IMAGEMANAGER->findImage("buttonUI")->render(getMemDC(), _backRc.left, _backRc.top);

}

void soundoption::mute()
{
	if (PtInRect(&_mute, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		soundNum = 0.0f;
		SOUNDMANAGER->setVolume(soundNum);
		SOUNDMANAGER->pause("gameSelect");
		SOUNDMANAGER->resume("gameSelect", soundNum);
	}
}

void soundoption::volume()
{
	y = m_ptMouse.y;
	if ((y <= WINSIZEY / 2 + 25 && y >= WINSIZEY / 2 - 25) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
		x = m_ptMouse.x;
		if (x < 387) {
			soundNum = 0.0f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(362, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 387 && x < 437)
		{
			soundNum = 0.1f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(412, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 437 && x < 487) {
			soundNum = 0.2f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(462, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 487 && x < 537) {
			soundNum = 0.3f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(512, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 537 && x < 587) {
			soundNum = 0.4f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(562, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 587 && x < 637) {
			soundNum = 0.5f;
			cursor = RectMakeCenter(612, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 637 && x < 687) {
			soundNum = 0.6f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(662, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 687 && x < 737) {
			soundNum = 0.7f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(712, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 737 && x < 787) {
			soundNum = 0.8f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(762, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 787 && x < 837) {
			soundNum = 0.9f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(812, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
		else if (x >= 837) {
			soundNum = 1.0f;
			SOUNDMANAGER->setVolume(soundNum);
			cursor = RectMakeCenter(862, WINSIZEY / 2, 50, 50);
			SOUNDMANAGER->pause("gameSelect");
			SOUNDMANAGER->resume("gameSelect", soundNum);
		}
	}
}

void soundoption::cursorPostion()
{
	if (SOUNDMANAGER->getVolume() == 1.0f) {
		cursor = RectMakeCenter(862, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.9f) {
		cursor = RectMakeCenter(812, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.8f) {
		cursor = RectMakeCenter(762, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.7f) {
		cursor = RectMakeCenter(712, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.6f) {
		cursor = RectMakeCenter(662, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.5f) {
		cursor = RectMakeCenter(612, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.4f) {
		cursor = RectMakeCenter(562, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.3f) {
		cursor = RectMakeCenter(512, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.2f) {
		cursor = RectMakeCenter(462, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.1f) {
		cursor = RectMakeCenter(412, WINSIZEY / 2, 50, 50);
	}
	if (SOUNDMANAGER->getVolume() == 0.0f) {
		cursor = RectMakeCenter(362, WINSIZEY / 2, 50, 50);
	}

}
