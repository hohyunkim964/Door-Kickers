#include "stdafx.h"
#include "item.h"


HRESULT item::init()
{
	TAGITEMINFO mp5;
	mp5.itemKind = item_SubMachineGun;
	mp5.image = IMAGEMANAGER->addImage("mp5", "images/item/SMG/mp5.bmp",131, 79, true, RGB(0, 0, 0));
	mp5.name = "MP5";
	mp5.description = "9mm탄을 사용하는 H&K MP5이다.";
	mp5.att = 10;
	mp5.def = 0;
	mp5.price = 10;
	mp5.itemRc = RectMakeCenter(0, 0, mp5.image->getWidth(), mp5.image->getHeight());

	_vRifle.push_back(mp5);

	TAGITEMINFO mp7;
	mp7.itemKind = item_SubMachineGun;
	mp7.image = IMAGEMANAGER->addImage("mp7", "images/item/SMG/mp7.bmp", 131, 79, true, RGB(0, 0, 0));
	mp7.name = "mp7";
	mp7.description = "4.6mm 탄을 사용하는 H&K MP7이다.";
	mp7.att = 13;
	mp7.def = 0;
	mp7.price = 30;
	mp7.itemRc = RectMakeCenter(0, 0, mp7.image->getWidth(), mp7.image->getHeight());

	_vRifle.push_back(mp7);

	TAGITEMINFO mpx;
	mpx.itemKind = item_SubMachineGun;
	mpx.image = IMAGEMANAGER->addImage("mpx", "images/item/SMG/mpx.bmp", 131, 79, true, RGB(0, 0, 0));
	mpx.name = "mpx";
	mpx.description = "9mm 탄을 사용하는 SIG MPX이다.";
	mpx.att = 15;
	mpx.def = 0;
	mpx.price = 40;
	mpx.itemRc = RectMakeCenter(0, 0, mpx.image->getWidth(), mpx.image->getHeight());
	_vRifle.push_back(mpx);
	

	TAGITEMINFO ump45;
	ump45.itemKind = item_SubMachineGun;
	ump45.image = IMAGEMANAGER->addImage("ump45", "images/item/SMG/ump45.bmp", 131, 79, true, RGB(0, 0, 0));
	ump45.name = "ump45";
	ump45.description = "45구경 탄을 사용하는 H&K UMP45이다.";
	ump45.att = 25;
	ump45.def = 0;
	ump45.price = 100;
	ump45.itemRc = RectMakeCenter(0, 0, ump45.image->getWidth(), ump45.image->getHeight());
	_vRifle.push_back(ump45);

	TAGITEMINFO kriss;
	kriss.itemKind = item_SubMachineGun;
	kriss.image = IMAGEMANAGER->addImage("vector", "images/item/SMG/vector.bmp", 131, 79, true, RGB(0, 0, 0));
	kriss.name = "vector";
	kriss.description = "45구경 탄을 사용하는 KRISS VECTOR이다.";
	kriss.att = 20;
	kriss.def = 0;
	kriss.price = 50;
	kriss.itemRc = RectMakeCenter(0, 0, kriss.image->getWidth(), kriss.image->getHeight());
	_vRifle.push_back(kriss);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	TAGITEMINFO g36c;
	g36c.itemKind = item_Rifle;
	g36c.image = IMAGEMANAGER->addImage("g36c", "images/item/rifle/g36c.bmp", 131, 79, true, RGB(0, 0, 0));
	g36c.name = "g36c";
	g36c.description = "5.56mm 탄을 사용하는 H&K G36C이다.";
	g36c.att = 18;
	g36c.def = 0;
	g36c.price = 45;
	g36c.itemRc = RectMakeCenter(0, 0, g36c.image->getWidth(), g36c.image->getHeight());

	_vRifle.push_back(g36c);

	TAGITEMINFO m4;
	m4.itemKind = item_Rifle;
	m4.image = IMAGEMANAGER->addImage("m4", "images/item/rifle/m4.bmp", 131, 79, true, RGB(0, 0, 0));
	m4.name = "m4";
	m4.description = "5.56mm 탄을 사용하는 M4 카빈이다.";
	m4.att = 28;
	m4.def = 0;
	m4.price = 100;
	m4.itemRc = RectMakeCenter(0, 0, m4.image->getWidth(), m4.image->getHeight());

	_vRifle.push_back(m4);

	TAGITEMINFO scar;
	scar.itemKind = item_Rifle;
	scar.image = IMAGEMANAGER->addImage("scar", "images/item/rifle/scar_h.bmp", 131, 79, true, RGB(0, 0, 0));
	scar.name = "scar";
	scar.description = "5.56mm 탄을 사용하는 FN SCAR이다.";
	scar.att = 50;
	scar.def = 0;
	scar.price = 200;
	scar.itemRc = RectMakeCenter(0, 0, scar.image->getWidth(), scar.image->getHeight());
	_vRifle.push_back(scar);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TAGITEMINFO fs_ap;
	fs_ap.itemKind = item_Pistol;
	fs_ap.image = IMAGEMANAGER->addImage("fs_ap", "images/item/pistol/fs_ap.bmp", 131, 79, true, RGB(0, 0, 0));
	fs_ap.name = "fs_ap";
	fs_ap.description = "5.7mm탄을 사용하는 FN Five-seveN이다.";
	fs_ap.att = 1;
	fs_ap.def = 0;
	fs_ap.price = 1;
	fs_ap.itemRc = RectMakeCenter(0, 0, fs_ap.image->getWidth(), fs_ap.image->getHeight());
	_vPistol.push_back(fs_ap);

	TAGITEMINFO g17;
	g17.itemKind = item_Pistol;
	g17.image = IMAGEMANAGER->addImage("g17", "images/item/pistol/g17.bmp", 131, 79, true, RGB(0, 0, 0));
	g17.name = "g17";
	g17.description = "9mm탄을 사용하는 GLOCK 17이다.";
	g17.att = 2;
	g17.def = 0;
	g17.price = 2;
	g17.itemRc = RectMakeCenter(0, 0, g17.image->getWidth(), g17.image->getHeight());
	_vPistol.push_back(g17);

	TAGITEMINFO hk45;
	hk45.itemKind = item_Pistol;
	hk45.image = IMAGEMANAGER->addImage("hk45", "images/item/pistol/hk45.bmp", 131, 79, true, RGB(0, 0, 0));
	hk45.name = "hk45";
	hk45.description = "45구경을 사용하는 H&K HK45이다.";
	hk45.att = 5;
	hk45.def = 0;
	hk45.price = 5;
	hk45.itemRc = RectMakeCenter(0, 0, hk45.image->getWidth(), hk45.image->getHeight());
	_vPistol.push_back(hk45);

	TAGITEMINFO sp01;
	sp01.itemKind = item_Pistol;
	sp01.image = IMAGEMANAGER->addImage("sp01", "images/item/pistol/sp01.bmp", 131, 79, true, RGB(0, 0, 0));
	sp01.name = "sp01";
	sp01.description = "9mm탄을 사용하는 CZ 75이다.";
	sp01.att = 3;
	sp01.def = 0;
	sp01.price = 3;
	sp01.itemRc = RectMakeCenter(0, 0, sp01.image->getWidth(), sp01.image->getHeight());
	_vPistol.push_back(sp01);

	TAGITEMINFO vp9;
	vp9.itemKind = item_Pistol;
	vp9.image = IMAGEMANAGER->addImage("hk45", "images/item/pistol/hk45.bmp", 131, 79, true, RGB(0, 0, 0));
	vp9.name = "vp9";
	vp9.description = "9mm탄을 사용하는 VP9이다.";
	vp9.att = 4;
	vp9.def = 0;
	vp9.price = 4;
	vp9.itemRc = RectMakeCenter(0, 0, vp9.image->getWidth(), vp9.image->getHeight());
	_vPistol.push_back(vp9);

	TAGITEMINFO magnum;
	magnum.itemKind = item_Pistol;
	magnum.image = IMAGEMANAGER->addImage("magnum44", "images/item/pistol/magnum44.bmp", 131, 79, true, RGB(0, 0, 0));
	magnum.name = "magnum44";
	magnum.description = "44구경을 사용하는 레이징 불 리볼버이다.";
	magnum.att = 10;
	magnum.def = 0;
	magnum.price = 10;
	magnum.itemRc = RectMakeCenter(0, 0, magnum.image->getWidth(), magnum.image->getHeight());
	_vPistol.push_back(magnum);
	////////////////////////////////////////////////// 방어구 ////////////////////////////////////////////////////////
	TAGITEMINFO armor1;
	armor1.itemKind = item_Armor;
	armor1.image = IMAGEMANAGER->addImage("armor1", "images/item/armor/armor1.bmp", 80, 79,  true, RGB(0, 0, 0));
	armor1.name = "기본 방어구";
	armor1.description = "기본적으로 지급 되는 방어구이다.";
	armor1.att = 0;
	armor1.def = 1;
	armor1.price = 10;
	armor1.itemRc = RectMakeCenter(0, 0, armor1.image->getWidth(), armor1.image->getHeight());
	_vDef.push_back(armor1);


	TAGITEMINFO armor2;
	armor2.itemKind = item_Armor;
	armor2.image = IMAGEMANAGER->addImage("armor2", "images/item/armor/armor2.bmp", 80, 79, true, RGB(0, 0, 0));
	armor2.name = "강화 방어구";
	armor2.description = "살짝 성능이 더 좋은 방어구이다.";
	armor2.att = 0;
	armor2.def = 2;
	armor2.price = 20;
	armor2.itemRc = RectMakeCenter(0, 0, armor2.image->getWidth(), armor2.image->getHeight());
	_vDef.push_back(armor2);

	TAGITEMINFO armor3;
	armor3.itemKind = item_Armor;
	armor3.image = IMAGEMANAGER->addImage("armor3", "images/item/armor/armor3.bmp", 80, 79, true, RGB(0, 0, 0));
	armor3.name = "완전무장 방어구";
	armor3.description = "매우 무거우며 전신방어구이다.";
	armor3.att = 0;
	armor3.def = 3;
	armor3.price = 40;
	armor3.itemRc = RectMakeCenter(0, 0, armor3.image->getWidth(), armor3.image->getHeight());
	_vDef.push_back(armor3);

	TAGITEMINFO armor4;
	armor4.itemKind = item_Armor;
	armor4.image = IMAGEMANAGER->addImage("armor4", "images/item/armor/armor4.bmp", 80, 79, true, RGB(0, 0, 0));
	armor4.name = "숙련자 방어구";
	armor4.description = "숙달된 사람들이 많이 쓰는 방어구이다.";
	armor4.att = 0;
	armor4.def = 5;
	armor4.price = 50;
	armor4.itemRc = RectMakeCenter(0, 0, armor4.image->getWidth(), armor4.image->getHeight());
	_vDef.push_back(armor4);

	TAGITEMINFO armor5;
	armor5.itemKind = item_Armor;
	armor5.image = IMAGEMANAGER->addImage("armor5", "images/item/armor/armor5.bmp", 80, 79, true, RGB(0, 0, 0));
	armor5.name = "FBI 방어구";
	armor5.description = " FBI에서 주는 방어구이다.";
	armor5.att = 0;
	armor5.def = 6;
	armor5.price = 60;
	armor5.itemRc = RectMakeCenter(0, 0, armor5.image->getWidth(), armor5.image->getHeight());
	_vDef.push_back(armor5);
	//////////////////////////////
	TAGITEMINFO shield1;
	shield1.itemKind = item_Shield;
	shield1.image = IMAGEMANAGER->addImage("shield1", "images/item/shield/shield1.bmp", 100, 79, true, RGB(0, 0, 0));
	shield1.name = "방패";
	shield1.description = "기본 방패";
	shield1.att = 1;
	shield1.def = 2;
	shield1.price = 15;
	shield1.itemRc = RectMakeCenter(0, 0, shield1.image->getWidth(), shield1.image->getHeight());
	_vShield.push_back(shield1);

	TAGITEMINFO shield2;
	shield2.itemKind = item_Shield;
	shield2.image = IMAGEMANAGER->addImage("shield2", "images/item/shield/shield2.bmp", 100, 79, true, RGB(0, 0, 0));
	shield2.name = "소형 방패";
	shield2.description = "진압용 방패";
	shield2.att = 2;
	shield2.def = 3;
	shield2.price = 25;
	shield2.itemRc = RectMakeCenter(0, 0, shield2.image->getWidth(), shield2.image->getHeight());
	_vShield.push_back(shield2);
	
	TAGITEMINFO shield3;
	shield3.itemKind = item_Shield;
	shield3.image = IMAGEMANAGER->addImage("shield3", "images/item/shield/shield3.bmp", 100, 79, true, RGB(0, 0, 0));
	shield3.name = "중급자용 방패";
	shield3.description = "경찰 특공대용 방패";
	shield3.att = 3;
	shield3.def = 4;
	shield3.price = 35;
	shield3.itemRc = RectMakeCenter(0, 0, shield3.image->getWidth(), shield3.image->getHeight());
	_vShield.push_back(shield3);

	TAGITEMINFO shield4;
	shield4.itemKind = item_Shield;
	shield4.image = IMAGEMANAGER->addImage("shield4", "images/item/shield/shield4.bmp", 100, 79, true, RGB(0, 0, 0));
	shield4.name = "SWAT 기본용 방패";
	shield4.description = "SWAT에서 보급해주는 방패";
	shield4.att = 4;
	shield4.def = 5;
	shield4.price = 45;
	shield4.itemRc = RectMakeCenter(0, 0, shield4.image->getWidth(), shield4.image->getHeight());
	_vShield.push_back(shield4);

	TAGITEMINFO shield5;
	shield5.itemKind = item_Shield;
	shield5.image = IMAGEMANAGER->addImage("shield5", "images/item/shield/shield5.bmp", 100, 79, true, RGB(0, 0, 0));
	shield5.name = "전문가용 방패";
	shield5.description = "전문가용 방패로 사용하기 어렵다";
	shield5.att = 5;
	shield5.def = 10;
	shield5.price = 150;
	shield5.itemRc = RectMakeCenter(0, 0, shield1.image->getWidth(), shield1.image->getHeight());
	_vShield.push_back(shield5);

	return S_OK;
}
