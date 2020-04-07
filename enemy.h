#pragma once
#include"gameNode.h"

enum dir
{
	Left, Right, Top, Bottom
};

class enemy : public gameNode
{
private:

	image * lifeImg;	//적 일반 이미지
	image * deadImg;	//적 사망 이미지
	RECT enemyRc;		//적 RECT
	POINT left;			//시야각 왼쪽 끝의 좌표
	POINT right;		//시야각 오른쪽 끝에 좌표
	int tileIndex[8];
	dir direction;		//enum 변수
	float angle;		//각도
	int leng;			//길이

	int hp;				//체력
	int att;			//공격력
	POINT centerPoint;	//적의 중점 좌표

	float time;		//시간 변수
	int randNum;	//난수

	
	bool isWait; //초기 이미지 여부
	bool isAtt; //공격 여부
	bool isReload; //재장전 여부
	bool isDead; //죽었는지 여부
	bool isCollsion; //적과 맞주쳤을 때

	int loop;	//장전 애니메이션 출력 조건
	int index;	//frameX 변수
	int count;	//초당 frame 관련

	RECT collisionRc;
	int tileX, tileY, tileX1, tileY1, tileX2, tileY2, tileX3, tileY3, tileX4, tileY4;
public:
	enemy();
	~enemy();

	HRESULT init(POINT center);
	void release();
	void update();
	void render();

	void lifeAnimation();
	void deadAnimation();

	void settingRightPoint();
	void settingLeftPoint();

	int getAtt() { return att; }	
	int getdir() { return direction; }
	bool getWait() { return isWait; }
	bool getisAtt() { return isAtt; }
	bool getReload() { return isReload; }
	bool getDead() { return isDead; }
	int getHp() { return hp; }
	bool getIsCollsion() { return isCollsion; }
	
	POINT getRight() { return right; }
	POINT getLeft() { return left; }
	POINT getCenter() { return centerPoint; }

	void setdir(dir a) { direction = a; }
	void setWait(bool a) { isWait = a; }
	void setAtt(bool a) { isAtt = a; }
	void setReload(bool a) { isReload = a; }
	void setDead(bool a) { isDead = a; }
	void setIsCollsion(bool a) { isCollsion = a; }
	void setHp(int a) { hp = a; }
	
	void settingView();

	void load();
};

