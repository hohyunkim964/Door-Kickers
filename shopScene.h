#pragma once
#include "scene.h"
#include "shop.h"

class shopScene : public scene
{
private:
	shop *_shop;
	RECT backRc;
	RECT falseRc;
	RECT trueRc;
	bool isExit;
	bool isMenu;
	float sound;
public:
	shopScene();
	~shopScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

