#pragma once
#include "gameNode.h"

class Unit : public gameNode
{
private:
	//범위 관련 변수 
	int leng; //길이
	float angle; //각도
	POINT firstEnd; // 오른쪽 끝 좌표
	POINT secondEnd; //왼쪽 끝 좌표
	POINT pointPos; //시작 위치 좌표
	//장애물 좌표
	POINT objectPos;
	//내적 관련 변수

	float a, b;
	POINT vec[3];
	POINT nVec;

	RECT rcCol;//장애물
	RECT rc; //유닛

	int x;
	int y;
	int px;
	int py;
	int cx;
	int cy;

	int hp;
	int def;
	int att;

	int sx;	//거리 비교 변수
	int sy; //거리 비교 변수

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

