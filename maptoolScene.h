#pragma once
#include "gameNode.h"
#include "maptool.h"
class maptoolScene :public gameNode
{
private:
	maptool* mapmade;
	RECT backRc;
	RECT falseRc;
	RECT trueRc;

	bool isExit;
	bool isMenu;

	float sound;
public:
	maptoolScene();
	~maptoolScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

