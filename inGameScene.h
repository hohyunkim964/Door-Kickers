#pragma once
#include "scene.h"
#include "manager.h" 
class inGameScene : public scene
{
private:
	manager* game;

	float time;	//���� �ð�
	float play;	//�ʱ� �ð�
	float i;	//�ð� ���� ��

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

