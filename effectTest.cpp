#include "stdafx.h"
#include "effectTest.h"
effectTest::effectTest()
{
}


effectTest::~effectTest()
{
}

HRESULT effectTest::init()
{
	IMAGEMANAGER->addImage("¹è°æ", "images/»ç³ª.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	////Æø¹ß ÀÌÆåÆ® ÀÌ¹ÌÁö
	//IMAGEMANAGER->addImage("Æø¹ß", "images/explosion.bmp", 832, 62, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("Æø¹ß1", "images/explosion1.bmp", 4355, 135, true, RGB(255, 0, 255));


	//_effect = new effect;
	//_effect->init(IMAGEMANAGER->findImage("Æø¹ß"), 32, 62, 1, 0.5f);


	//_effect1 = new effect;
	//_effect1->init(IMAGEMANAGER->findImage("Æø¹ß1"), 335, 135, 1, 0.4f);

	EFFECTMANAGER->addEffect("Æø¹ß", "images/explosion.bmp", 832, 62, 32, 62, 1, 0.5f, 100);
	EFFECTMANAGER->addEffect("Æø¹ß1", "images/explosion1.bmp", 4355, 135, 335, 135, 1, 0.3f, 100);
	count = 0;
	return S_OK;
}

void effectTest::release()
{
	/*SAFE_DELETE(_effect);
	SAFE_DELETE(_effect1);*/
}

void effectTest::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//_effect->startEffect(m_ptMouse.x, m_ptMouse.y);
		EFFECTMANAGER->play("Æø¹ß", m_ptMouse.x, m_ptMouse.y);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//_effect1->startEffect(m_ptMouse.x, m_ptMouse.y);
		EFFECTMANAGER->play("Æø¹ß1", m_ptMouse.x, m_ptMouse.y);
	}

	//_effect->update();
	//_effect1->update();

	count++;

	if (count % 10 == 0)
	{
		EFFECTMANAGER->play("Æø¹ß", RND->getFromIntTo(100, 300), RND->getFromIntTo(100, 300));
	}

}

void effectTest::render()
{
	IMAGEMANAGER->render("¹è°æ", getMemDC());
	//_effect->render();
	//_effect1->render();
}
