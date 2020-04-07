#pragma once
#include "scene.h"

class invenScene : public scene
{
private:
	//inventory* inven;
	RECT backRc;
	RECT falseRc;
	RECT trueRc;

	bool isExit;
	bool isMenu;

	bool currentPistol;
	bool currentRifle;
	bool currentShield;

	float sound;
	int count;
public:
	invenScene();
	~invenScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

