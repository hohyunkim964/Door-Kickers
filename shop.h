#pragma once
#include "scene.h"
#include "item.h"


class shop : public scene
{
private:
	int money; //������ ��� �ݾ�
	
	item* _item;
	image* back;

	RECT pistolRc;
	RECT rifleRc;
	RECT armorRc;
	RECT shieldRc;
	RECT shopRc;
	RECT npcRc;
	RECT rifleKindRc;
	RECT pistolKindRc;
	RECT armorKindRc;
	RECT shieldKindRc;
	RECT descriptionRc;
	RECT npcTalkRc;
	
	bool isPistol;  //���� ����
	bool isRifle;	//������ ����
	bool isShield;	//���� ����
	bool isArmor;	//�� ����
	bool isBuy;		//�����Ϸ��� Ŭ����
	bool isSell;	//�����Ͽ�����
	
	string _description;	//������ ����

	int descriptionX;	//������ ���� ��ġ X��
	int descriptionY;	//������ ���� ��ġ Y��
	float count;	//����â ���� �ð� �Լ�
	float time;		//����â ���� �ð� �Լ�

	vector<TAGITEMINFO> _tempRifle;
public:
	shop();
	~shop();

	HRESULT init();
	void release();
	void update();
	void render();

	void position(); //���� ��ġ
	void buyMotion(); //����
	void buy(int i);	//���Ž� ���Ϳ���
	void itemDescription(); //������ ���� ��� ����
};

