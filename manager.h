#pragma once
#include "scene.h"
#include "unitSelect.h"
#include "enemyManager.h"



class manager : public scene
{
private:
	unitSelect* player;
	enemyManager* enemyPlayer;

	POINT vec[3];	//내적 관련
	POINT nVec;		//내적 관련
	float a, b;		//내적 관련
	int enemyHP;	//적 체력 변수
	int playerHP;	//유닛 체력 변수
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
	void enemyFind();	//적 탐색
	void playerFind();	//유닛 참색

	int vectorDot(POINT &vec1, POINT vec2);  //내적 관련
	void vecCross(POINT &outvec, POINT &invec); //내적 관련
	bool isCrash(POINT &x, POINT &y, POINT &z, POINT &objectPos); //내적 관련
	bool getFinsih() { return isFinish; }
	bool getDead() { return isDead; }
	bool getEnemyCollsion() { return enemyCollsion; }
	bool getPlayerCollsion() { return playerCollsion; }
};

