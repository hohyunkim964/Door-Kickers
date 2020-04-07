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
	
	POINT straight;	//�������� ������ �Ÿ�
	int unitHp;		//���� ü��
	int unitAtt;	//���� ���ݷ�
	int unitDef;	//���� ����
	image* startPoint;	//���� ���� ��ġ �̹���
	image* pistolImg;	//���Ѻ� �̹���
	image* rifleImg;	//���Ѽ� �̹���
	image* shieldImg;	//���к� �̹���
	
	image* unit;		//���õ� �̹���

	int destinationX;	//�������� X��
	int destinationY;	//�������� Y��
	
	RECT unitRc;		//���� ��Ʈ
	RECT startPositionRect;

	float angle;		//����
	POINT center;		//���� ���� ��ǥ
	POINT right;		//���� ������ �þ� �� ��ǥ
	POINT left;			//���� ���� �þ� �� ��ǥ
	int range;			//��Ÿ�
	POINT enemy;		//�� ��ġ(��ǥ)

	direction dir;		//���� ����

	bool pistol;		//�����ΰ�
	bool rifle;			//�����ΰ�
	bool shield;		//�����ΰ�
	

	POINT vec[3];	//���� ����
	POINT nVec;		//���� ����
	float a;		//���� ����
	float b;		//���� ����

	bool isDead;	//���� ����
	bool isAttack;	//����
	bool isReload;	//������
	bool isMove;	//�̵�
	bool isWait;	//���

	int count;		//�ִϸ��̼� ����
	int index;		//�ִϸ��̼� ����
	int yIndex;
	bool isLoop;	//�ִϸ��̼� �ݺ� ����

	bool isCollsion;	//���� �������� ��
		
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

	void selectUnit();			//���� ����(�κ��丮�� ���� �ҷ��ͼ� üũ)
	void selectUnitRange();		//���õ� ���� ���� �þ߰� ����
	
	void viewRightRange();		//���� �þ� �� ��
	void viewLeftRange();		//���� �þ� ����
	void move();				//�̵� ����
	
	void unitLifeAnimation();	//���� ������ �̹��� �ִϸ��̼�	

	void setIsWait(bool a) { isWait = a; }		//���� ��� ����
	void setIsAttack(bool a) { isAttack = a; }	//���� ���� ����
	void setIsDead(bool a) { isDead = a; }	//���� ��� ����
	bool getIsDead() { return isDead; }		//���� ��� ����
	void setDir(direction a) { dir = a; }  //�浹�� ���� ���� ���� ����
	bool getIsMove() { return isMove; }		//���� �̵� ����
	void setIsMove(bool a) { isMove = a; }	//���� �̵� ����

	direction getdir() { return dir; }
	int getHp() { return unitHp; }		//���� ü��
	int getAtt() { return unitAtt; }	//���� ���ݷ�
	int getDef() { return unitDef; }	//���� ����
	POINT getCenter() { return center; }	//���� ����
	POINT getRight() { return right; }		//���� ������ ����
	POINT getLeft() { return left; }		//���� ���� ����

	void setHp(int a) { unitHp = a; }		//���� ü�� ����

	bool getPistol() { return pistol; }
	bool getShield() { return shield; }
	bool getRifle() { return rifle; }
	bool getReload() { return isReload; }

	void collisionRange();

};

