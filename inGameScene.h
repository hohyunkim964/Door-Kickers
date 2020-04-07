#pragma once
#include "scene.h"
#include "manager.h" 
class inGameScene : public scene
{
private:
	manager* game;

	float time;	//현재 시간
	float play;	//초기 시간
	float i;	//시간 연산 값

	RECT uiRc;
	
	char str[256];

	bool isExit;
	bool isMenu;

	float sound;
	
public:
	inGameScene();
	~inGameScene();

	HRESULT init();
	void release();
	void update();
	void render();
	
};

