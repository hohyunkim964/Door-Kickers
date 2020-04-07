#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}
HRESULT mainGame::init()
{
	gameNode::init(true);
	SCENEMANAGER->addScene("main", new mainScene);
	SCENEMANAGER->addScene("sound", new soundoption);
	SCENEMANAGER->addScene("maptool", new maptoolScene);
	SCENEMANAGER->addScene("inGame", new inGameScene);
	SCENEMANAGER->addScene("inven", new invenScene);
	SCENEMANAGER->addScene("shop", new shopScene);
	SCENEMANAGER->addScene("gameScene", new gameScene);	
	SCENEMANAGER->addScene("dead", new deadScene);
	SCENEMANAGER->addScene("finish", new finishScene);
	SCENEMANAGER->changeScene("main");
	
	
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();

}
void mainGame::update()
{
	gameNode::update();
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}

void mainGame::render(/*HDC hdc*/)
{
	
	//��� ��Ʈ��
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================
	SCENEMANAGER->render();

	//TIMEMANAGER->render(getMemDC());
	//=================================================
	//������� ������ HDC�� �׸���.(�ǵ帮������.)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}
