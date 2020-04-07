#pragma once
#include "scene.h"
#include "unitSelect.h"
#include "enemyManager.h"



class manager : public scene
{
private:
	unitSelect* player;
	enemyManager* enemyPlayer;

	POINT vec[3];	//���� ����
	POINT nVec;		//���� ����
	float a, b;		//���� ����
	int enemyHP;	//�� ü�� ����
	int playerHP;	//���� ü�� ����
	int countNum;
	int enemyCountNum;
	float total;
	float time;
	int count;
	bool isDead;
	bool isFinish;
	
	float sound;

	bool enemyCollsion;
	bool playerCollsion;



public:
	manager();
	~manager();

	HRESULT init();
	void release();
	void update();
	void render();

	void find();
	void enemyFind();	//�� Ž��
	void playerFind();	//���� ����

	int vectorDot(POINT &vec1, POINT vec2);  //���� ����
	void vecCross(POINT &outvec, POINT &invec); //���� ����
	bool isCrash(POINT &x, POINT &y, POINT &z, POINT &objectPos); //���� ����
	bool getFinsih() { return isFinish; }
	bool getDead() { return isDead; }
	bool getEnemyCollsion() { return enemyCollsion; }
	bool getPlayerCollsion() { return playerCollsion; }
};

