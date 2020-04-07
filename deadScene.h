#pragma once

#include "scene.h"
class deadScene : public scene
{
private:
	image* pistolDeadImg;
	image* rifleDeadImg;
	image* shieldDeadImg;
	image* menuImg;
	image* returnImg;
	bool pistol;
	bool rifle;
	bool shield;
	bool animationEnd;

	int count;
	int index;

	RECT charcter;
	RECT menuRc;
	RECT returnRc;
	float sound;
	char str[256];
public:
	deadScene();
	~deadScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void selectUnit();			//유닛 선택(인벤토리의 값을 불러와서 체크)

	void deadImage();
};

