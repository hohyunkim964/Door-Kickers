#pragma once
#include "gameNode.h"

class gameScene : public gameNode
{
private:
	image* shopImage;
	image* gameImage;
	image* invenImage;
	image* back;
	RECT invenRc;
	RECT shopRc;
	RECT gameRc;
	int transparency1;
	int transparency2;
	int transparency3;
	float sound;

public:
	gameScene();
	~gameScene();
	HRESULT init();
	void release();
	void update();
	void render();
};

