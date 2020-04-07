#pragma once
#include "gameNode.h"
#include "item.h"



class inventory : public gameNode
{
private:

	int playerMoney;		//플레이어 초기 자금

	inventory* inven;
	int selectPistolWeaponNum;	//장착된 무기 벡터 내부의 위치
	int selectRifleWeaponNum;	//장착된 무기 벡터 내부의 위치
	int selectShieldWeaponNum;	//장착된 무기 벡터 내부의 위치
	int selectArmorNum;		//장착된 방어구 벡터 내부의 위치
	int onWeaponNum;		//마우스로 선택한 무기 벡터 내부의 위치
	int onDefNum;			//마우스로 선택한 방어구 벡터 내부의 위치

	char str[256];		//글자 출력 관련 변수
	RECT viewRc;
	RECT charcterRc;	//캐릭터 장착 애니매이션 변경

	item* _item;	
	RECT invenRc;		//인벤토리 관련 렉트

	RECT weaponRc;		//무기 창
	RECT defRc;			//방어구 창

	bool isWeapon;		//무기 선택 여부
	bool isArmor;		//방어구 선택여부

	RECT pistolRc;		//무기 상세 창
	RECT rifleRc;		//무기 상세 창
	RECT shieldRc;		//무기 상세 창
	RECT armorRc;		//방어구 상세 창

	RECT attRc;			//공격력 
	RECT defenceRc;			//방어력
	RECT onAttRc;
	RECT onDefRc;

	RECT selectWeaponRc;	//무기 장착 창
	RECT selectArmorRc;		//방어구 장착창

	bool isPistolOn;	//무기 상세 목록 여부
	bool isRifleOn;		//무기 상세 목록 여부
	bool isShieldOn;	//무기 상세 목록 여부
	bool isArmorOn;		//방어구 상세 목록 여부
	
	bool isClick;		//현재 마우스로 눌렀는 지 여부

	bool isSelectPistol;	//권총 장착 여부
	bool isSelectRifle;		//소총 장착 여부
	bool isSelectShield;	//방패 장착 여부
	bool isSelectArmor;		//방어구 장착 여부

	int pistolAtt;		//권총 아이템과 유닛 합의 공격력
	int rifleAtt;		//소총 아이템과 유닛 합의 공격력
	int shieldAtt;		//방패 아이템과 유닛 합의 공격력
	int armorAtt;		//방어구 아이템과 유닛 합의 공격력
	int unitAtt;		//현재 장착한 아이템과 유닛 합의 공격력

	int pistolDef;		//권총 아이템과 유닛 합의 방어력
	int rifleDef;		//소총 아이템과 유닛 합의 방어력
	int armorDef;		//방패 아이템과 유닛 합의 방어력
	int shieldDef;		//방어구 아이템과 유닛 합의 방어력
	int unitDef;		//현재 장착한 아이템과 유닛 합의 방어력

	int unitHp;			//유닛 체력

	int count;			//착용시 플레이어 애니메이션 변수
	int index;			//착용시 플레이어 애니메이션 변수
	//4개의 백터 생성
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
	
	void uiPosition();		//UI 위치

	void setShield(TAGITEMINFO vItem) { _uShield.push_back(vItem); }
	void setPistol(TAGITEMINFO vItem) { _uPistol.push_back(vItem); }
	void setRifle(TAGITEMINFO vItem) { _uRifle.push_back(vItem); }
	void setArmor(TAGITEMINFO vItem) { _uArmor.push_back(vItem); }	
	
	void selectItem();		//아이템 장착

	void unitTotalHp();		//유닛 체력
	void unitTotalAtt();	//유닛 공격력
	void unitTotalDef();	//유닛 방어력

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

