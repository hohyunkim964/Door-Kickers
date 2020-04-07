#pragma once
#include "gameNode.h"



class mainScene : public gameNode
{
private:
	RECT gameButton;
	RECT soundButton;
	RECT mapToolButton;
	RECT exitButton;
	float sound;

public:
	mainScene();
	~mainScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

