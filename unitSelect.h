#pragma once
#include "scene.h"
#include "inventory.h"

enum direction
{
	isLeft, isRight, isTop, isBottom, isNone
};

class unitSelect : public scene
{
private:	
	
	POINT straight;	//직선으로 끝점의 거리
	int unitHp;		//유닛 체력
	int unitAtt;	//유닛 공격력
	int unitDef;	//유닛 방어력
	image* startPoint;	//유닛 시작 위치 이미지
	image* pistolImg;	//권총병 이미지
	image* rifleImg;	//소총수 이미지
	image* shieldImg;	//방패병 이미지
	
	image* unit;		//선택된 이미지

	int destinationX;	//도착지점 X축
	int destinationY;	//도착지점 Y축
	
	RECT unitRc;		//유닛 렉트
	RECT startPositionRect;

	float angle;		//각도
	POINT center;		//유닛 중점 좌표
	POINT right;		//유닛 오른쪽 시야 끝 좌표
	POINT left;			//유닛 왼쪽 시야 끝 좌표
	int range;			//사거리
	POINT enemy;		//적 위치(좌표)

	direction dir;		//보는 방향

	bool pistol;		//권총인가
	bool rifle;			//소총인가
	bool shield;		//방패인가
	

	POINT vec[3];	//내적 관련
	POINT nVec;		//내적 관련
	float a;		//내적 관련
	float b;		//내적 관련

	bool isDead;	//생존 유무
	bool isAttack;	//공격
	bool isReload;	//재장전
	bool isMove;	//이동
	bool isWait;	//대기

	int count;		//애니메이션 관련
	int index;		//애니매이션 관련
	int yIndex;
	bool isLoop;	//애니매이션 반복 관련

	bool isCollsion;	//적과 맞주쳤을 때
		
	int tileX, tileY, tileX1, tileY1, tileX2, tileY2, tileX3, tileY3, tileX4, tileY4;
	float _x, _y;
	RECT rcCollision;
	int loop;
	RECT collisionRangeRc;
	
public:
	unitSelect();
	~unitSelect();
	HRESULT init();
	void release();
	void update();
	void render();

	void selectUnit();			//유닛 선택(인벤토리의 값을 불러와서 체크)
	void selectUnitRange();		//선택된 유닛 별로 시야각 범위
	
	void viewRightRange();		//우측 시야 끝 점
	void viewLeftRange();		//좌측 시야 끝점
	void move();				//이동 관련
	
	void unitLifeAnimation();	//유닛 생존시 이미지 애니메이션	

	void setIsWait(bool a) { isWait = a; }		//유닛 대기 설정
	void setIsAttack(bool a) { isAttack = a; }	//유닛 공격 설정
	void setIsDead(bool a) { isDead = a; }	//유닛 사망 설정
	bool getIsDead() { return isDead; }		//유닛 사망 여부
	void setDir(direction a) { dir = a; }  //충돌시 유닛 보는 방향 변경
	bool getIsMove() { return isMove; }		//유닛 이동 여부
	void setIsMove(bool a) { isMove = a; }	//유닛 이동 설정

	direction getdir() { return dir; }
	int getHp() { return unitHp; }		//유닛 체력
	int getAtt() { return unitAtt; }	//유닛 공격력
	int getDef() { return unitDef; }	//유닛 방어력
	POINT getCenter() { return center; }	//유닛 중점
	POINT getRight() { return right; }		//유닛 오른쪽 끝점
	POINT getLeft() { return left; }		//유닛 좌측 끝점

	void setHp(int a) { unitHp = a; }		//유닛 체력 설정

	bool getPistol() { return pistol; }
	bool getShield() { return shield; }
	bool getRifle() { return rifle; }
	bool getReload() { return isReload; }

	void collisionRange();

};

