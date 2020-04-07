#pragma once
#include "gameNode.h"
#include "enemy.h"


class enemyManager : public gameNode
{
private:	
	typedef vector<enemy*> venemy;
	typedef vector<enemy*>::iterator vienemy;
private:
	venemy _vEnemy;
	vienemy _viEnemy;

	int randnumY;	//y축 난수
	int randnumX;	//x축 난수

	POINT vec[3];	//내적 관련
	POINT nVec;		//내적 관련
	float a, b;		//내적 관련

	POINT first;	//8방향 애니메이션 기준
	POINT second;	//8방향 애니메이션 기준
	int count;		//애니메이션 변수
	int index;		//애니메이션 변수
	int enemyNum;	
	
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion(); //위치설정

	vector<enemy*> getEnemyVector() { return _vEnemy; }
	void setEnemyVector(vector<enemy*> vEnemy) { _vEnemy = vEnemy; }
	int getEnemyNum() { return enemyNum; }
};

