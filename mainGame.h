#pragma once
#include"gameNode.h"
#include "mainScene.h"
#include "soundoption.h"
#include "maptoolScene.h"
#include "gameScene.h"
#include "shopScene.h"
#include "invenScene.h"
#include "inGameScene.h"
#include "deadScene.h"
#include "finishScene.h"

class mainGame :  public gameNode
{
private:
	

public:
	mainGame();
	~mainGame();

	virtual HRESULT init();	//�ʱ�ȭ
	virtual void release();//����
	virtual void update();//�����ϴ°�
	virtual void render(/*HDC hdc*/);//�׸��°�

};

