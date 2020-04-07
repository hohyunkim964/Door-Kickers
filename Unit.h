#pragma once
#include "gameNode.h"

class Unit : public gameNode
{
private:
	//���� ���� ���� 
	int leng; //����
	float angle; //����
	POINT firstEnd; // ������ �� ��ǥ
	POINT secondEnd; //���� �� ��ǥ
	POINT pointPos; //���� ��ġ ��ǥ
	//��ֹ� ��ǥ
	POINT objectPos;
	//���� ���� ����

	float a, b;
	POINT vec[3];
	POINT nVec;

	RECT rcCol;//��ֹ�
	RECT rc; //����

	int x;
	int y;
	int px;
	int py;
	int cx;
	int cy;

	int hp;
	int def;
	int att;

	int sx;	//�Ÿ� �� ����
	int sy; //�Ÿ� �� ����

	bool isMove;

	bool isYUP;
	bool isYDOWN;
	bool isXRight;
	bool isXLeft;

	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
	bool isLoop;
	bool isFirst;

	int count;	
	int index;

	int time;
	bool isDead;
public:
	Unit();
	~Unit();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void animation();

	int vectorDot(POINT &vec1, POINT vec2);
	
	void vecCross(POINT &outvec, POINT &invec);
	bool isCrash(POINT &x,POINT &y,POINT &z, POINT &objectPos);

	RECT getRect() { return rc; }
	int getRectX() { return cx; }
	int getRectY() { return cy; }
	int getAtt() { return att; }
	bool unitLeft() { return isLeft; }
	bool unitRight() { return isRight; }
	bool unitTop() { return isUp; }
	bool unitBottom() { return isDown; }
	POINT getunit() { return pointPos; }
	void hpLost();
};

