#pragma once
enum ITEM
{
	item_Armor,
	item_SubMachineGun,
	item_Rifle,
	item_Pistol,
	item_Shield,	
};

struct TAGITEMINFO
{
	ITEM itemKind;	//����
	image* image;
	const char* name;
	string description;
	int att;
	int def;
	int price;
	RECT itemRc;
};

class item 
{
private:
	vector <TAGITEMINFO> _vRifle;
	vector <TAGITEMINFO>::iterator _viRifle;

	vector <TAGITEMINFO> _vPistol;
	vector <TAGITEMINFO>::iterator _viPistol;

	vector <TAGITEMINFO> _vDef;
	vector <TAGITEMINFO>::iterator _viDef;

	vector <TAGITEMINFO> _vShield;
	vector <TAGITEMINFO>::iterator _viShield;

public:
	HRESULT init();

	vector<TAGITEMINFO> getRifleInfo() { return _vRifle; } //������ ���� ��������	        
	void setRifleInfo(vector<TAGITEMINFO> vItem) { _vRifle = vItem; } //������ ���� ����

	RECT getRifleRC(int num) { return _vRifle.at(num).itemRc; }//������ RC ��������
	void setRifleRC(int num, RECT rc) { _vRifle.at(num).itemRc = rc; } //������ RC ����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<TAGITEMINFO> getPistolInfo() { return _vPistol; } //������ ���� ��������	        
	void setPistolInfo(vector<TAGITEMINFO> vItem) { _vPistol = vItem; } //������ ���� ����

	RECT getPistolRC(int num) { return _vPistol.at(num).itemRc; }//������ RC ��������
	void setPistolRC(int num, RECT rc) { _vPistol.at(num).itemRc = rc; } //������ RC ����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<TAGITEMINFO> getDefInfo() { return _vDef; } //�� ��������	        
	void setDefInfo(vector<TAGITEMINFO> vItem) { _vDef = vItem; } //�� ���� ����

	RECT getDefRC(int num) { return _vDef.at(num).itemRc; }//�� RC ��������
	void setDefRC(int num, RECT rc) { _vDef.at(num).itemRc = rc; } //�� RC ����

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<TAGITEMINFO> getShieldInfo() { return _vShield; } //���� ���� ��������	        
	void setShieldInfo(vector<TAGITEMINFO> vItem) { _vShield = vItem; } //���� ���� ����

	RECT getShieldRC(int num) { return _vShield.at(num).itemRc; }//������ RC ��������
	void setShieldRC(int num, RECT rc) { _vShield.at(num).itemRc = rc; } //������ RC ����
};

