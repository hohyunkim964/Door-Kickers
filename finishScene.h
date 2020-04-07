#pragma once

#include "scene.h"


class finishScene : public scene
{
private:
	
	RECT backRc;
	RECT scoreRc;
	char str[256];
	float i;
	float sound;
public:
	finishScene();
	~finishScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

