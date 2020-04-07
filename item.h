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
	ITEM itemKind;	//종류
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

	vector<TAGITEMINFO> getRifleInfo() { return _vRifle; } //라이플 벡터 가져오기	        
	void setRifleInfo(vector<TAGITEMINFO> vItem) { _vRifle = vItem; } //라이플 벡터 세팅

	RECT getRifleRC(int num) { return _vRifle.at(num).itemRc; }//라이플 RC 가져오기
	void setRifleRC(int num, RECT rc) { _vRifle.at(num).itemRc = rc; } //라이플 RC 변경
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	vector<TAGITEMINFO> getPistolInfo() { return _vPistol; } //라이플 벡터 가져오기	        
	void setPistolInfo(vector<TAGITEMINFO> vItem) { _vPistol = vItem; } //라이플 벡터 세팅

	RECT getPistolRC(int num) { return _vPistol.at(num).itemRc; }//라이플 RC 가져오기
	void setPistolRC(int num, RECT rc) { _vPistol.at(num).itemRc = rc; } //라이플 RC 변경
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<TAGITEMINFO> getDefInfo() { return _vDef; } //방어구 가져오기	        
	void setDefInfo(vector<TAGITEMINFO> vItem) { _vDef = vItem; } //방어구 벡터 세팅

	RECT getDefRC(int num) { return _vDef.at(num).itemRc; }//방어구 RC 가져오기
	void setDefRC(int num, RECT rc) { _vDef.at(num).itemRc = rc; } //방어구 RC 변경

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	vector<TAGITEMINFO> getShieldInfo() { return _vShield; } //방패 벡터 가져오기	        
	void setShieldInfo(vector<TAGITEMINFO> vItem) { _vShield = vItem; } //방패 벡터 세팅

	RECT getShieldRC(int num) { return _vShield.at(num).itemRc; }//아이템 RC 가져오기
	void setShieldRC(int num, RECT rc) { _vShield.at(num).itemRc = rc; } //아이템 RC 변경
};

