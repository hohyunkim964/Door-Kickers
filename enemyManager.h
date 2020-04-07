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

	int randnumY;	//y�� ����
	int randnumX;	//x�� ����

	POINT vec[3];	//���� ����
	POINT nVec;		//���� ����
	float a, b;		//���� ����

	POINT first;	//8���� �ִϸ��̼� ����
	POINT second;	//8���� �ִϸ��̼� ����
	int count;		//�ִϸ��̼� ����
	int index;		//�ִϸ��̼� ����
	int enemyNum;	
	
public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void setMinion(); //��ġ����

	vector<enemy*> getEnemyVector() { return _vEnemy; }
	void setEnemyVector(vector<enemy*> vEnemy) { _vEnemy = vEnemy; }
	int getEnemyNum() { return enemyNum; }
};

