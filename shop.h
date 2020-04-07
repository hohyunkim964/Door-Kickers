#pragma once
#include "scene.h"
#include "item.h"


class shop : public scene
{
private:
	int money; //구매후 계산 금액
	
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
	
	bool isPistol;  //권총 선택
	bool isRifle;	//라이플 선택
	bool isShield;	//방패 선택
	bool isArmor;	//방어구 선택
	bool isBuy;		//구매하려고 클릭시
	bool isSell;	//구매하였을때
	
	string _description;	//아이템 설명

	int descriptionX;	//아이템 설명 위치 X축
	int descriptionY;	//아이템 설명 위치 Y축
	float count;	//구매창 관련 시간 함수
	float time;		//구매창 관련 시간 함수

	vector<TAGITEMINFO> _tempRifle;
public:
	shop();
	~shop();

	HRESULT init();
	void release();
	void update();
	void render();

	void position(); //물건 위치
	void buyMotion(); //구매
	void buy(int i);	//구매시 벡터연산
	void itemDescription(); //아이템 설명 출력 관련
};

