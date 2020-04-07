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

	virtual HRESULT init();	//초기화
	virtual void release();//해제
	virtual void update();//연산하는곳
	virtual void render(/*HDC hdc*/);//그리는곳

};

