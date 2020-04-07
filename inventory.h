#pragma once
#include "gameNode.h"
#include "item.h"



class inventory : public gameNode
{
private:

	int playerMoney;		//�÷��̾� �ʱ� �ڱ�

	inventory* inven;
	int selectPistolWeaponNum;	//������ ���� ���� ������ ��ġ
	int selectRifleWeaponNum;	//������ ���� ���� ������ ��ġ
	int selectShieldWeaponNum;	//������ ���� ���� ������ ��ġ
	int selectArmorNum;		//������ �� ���� ������ ��ġ
	int onWeaponNum;		//���콺�� ������ ���� ���� ������ ��ġ
	int onDefNum;			//���콺�� ������ �� ���� ������ ��ġ

	char str[256];		//���� ��� ���� ����
	RECT viewRc;
	RECT charcterRc;	//ĳ���� ���� �ִϸ��̼� ����

	item* _item;	
	RECT invenRc;		//�κ��丮 ���� ��Ʈ

	RECT weaponRc;		//���� â
	RECT defRc;			//�� â

	bool isWeapon;		//���� ���� ����
	bool isArmor;		//�� ���ÿ���

	RECT pistolRc;		//���� �� â
	RECT rifleRc;		//���� �� â
	RECT shieldRc;		//���� �� â
	RECT armorRc;		//�� �� â

	RECT attRc;			//���ݷ� 
	RECT defenceRc;			//����
	RECT onAttRc;
	RECT onDefRc;

	RECT selectWeaponRc;	//���� ���� â
	RECT selectArmorRc;		//�� ����â

	bool isPistolOn;	//���� �� ��� ����
	bool isRifleOn;		//���� �� ��� ����
	bool isShieldOn;	//���� �� ��� ����
	bool isArmorOn;		//�� �� ��� ����
	
	bool isClick;		//���� ���콺�� ������ �� ����

	bool isSelectPistol;	//���� ���� ����
	bool isSelectRifle;		//���� ���� ����
	bool isSelectShield;	//���� ���� ����
	bool isSelectArmor;		//�� ���� ����

	int pistolAtt;		//���� �����۰� ���� ���� ���ݷ�
	int rifleAtt;		//���� �����۰� ���� ���� ���ݷ�
	int shieldAtt;		//���� �����۰� ���� ���� ���ݷ�
	int armorAtt;		//�� �����۰� ���� ���� ���ݷ�
	int unitAtt;		//���� ������ �����۰� ���� ���� ���ݷ�

	int pistolDef;		//���� �����۰� ���� ���� ����
	int rifleDef;		//���� �����۰� ���� ���� ����
	int armorDef;		//���� �����۰� ���� ���� ����
	int shieldDef;		//�� �����۰� ���� ���� ����
	int unitDef;		//���� ������ �����۰� ���� ���� ����

	int unitHp;			//���� ü��

	int count;			//����� �÷��̾� �ִϸ��̼� ����
	int index;			//����� �÷��̾� �ִϸ��̼� ����
	//4���� ���� ����
	vector <TAGITEMINFO> _uRifle;
	vector<TAGITEMINFO> _uPistol;
	vector<TAGITEMINFO> _uShield;
	vector<TAGITEMINFO> _uArmor;
	float sound;
public:
	inventory();
	~inventory();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void uiPosition();		//UI ��ġ

	void setShield(TAGITEMINFO vItem) { _uShield.push_back(vItem); }
	void setPistol(TAGITEMINFO vItem) { _uPistol.push_back(vItem); }
	void setRifle(TAGITEMINFO vItem) { _uRifle.push_back(vItem); }
	void setArmor(TAGITEMINFO vItem) { _uArmor.push_back(vItem); }	
	
	void selectItem();		//������ ����

	void unitTotalHp();		//���� ü��
	void unitTotalAtt();	//���� ���ݷ�
	void unitTotalDef();	//���� ����

	void unitAnimation();

	bool isPistol() { return isPistolOn; }
	bool isRifle() { return isRifleOn; }
	bool isShield() { return isShieldOn; }
	bool isDEF() { return isArmorOn; }

	bool selectPistol() { return isSelectPistol; }
	bool selectRifle() { return isSelectRifle; }
	bool selectShiled() { return isSelectShield; }
	bool selectArmor() { return isSelectArmor; }
	int getMoney() { return playerMoney; }
	void setMoney(int a) { playerMoney = a; }
	inventory* test() { return inven; }
};

