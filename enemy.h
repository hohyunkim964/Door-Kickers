#pragma once
#include"gameNode.h"

enum dir
{
	Left, Right, Top, Bottom
};

class enemy : public gameNode
{
private:

	image * lifeImg;	//�� �Ϲ� �̹���
	image * deadImg;	//�� ��� �̹���
	RECT enemyRc;		//�� RECT
	POINT left;			//�þ߰� ���� ���� ��ǥ
	POINT right;		//�þ߰� ������ ���� ��ǥ
	int tileIndex[8];
	dir direction;		//enum ����
	float angle;		//����
	int leng;			//����

	int hp;				//ü��
	int att;			//���ݷ�
	POINT centerPoint;	//���� ���� ��ǥ

	float time;		//�ð� ����
	int randNum;	//����

	
	bool isWait; //�ʱ� �̹��� ����
	bool isAtt; //���� ����
	bool isReload; //������ ����
	bool isDead; //�׾����� ����
	bool isCollsion; //���� �������� ��

	int loop;	//���� �ִϸ��̼� ��� ����
	int index;	//frameX ����
	int count;	//�ʴ� frame ����

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

