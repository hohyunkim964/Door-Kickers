#include "stdafx.h"
#include "shop.h"


shop::shop()
{
}


shop::~shop()
{
}

HRESULT shop::init()
{	
	inven->init();
	_item = new item;
	_item->init();
	
	IMAGEMANAGER->addImage("desbutton", "images/shop/설명창.bmp", 350, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shopback", "images/shop/back.bmp", WINSIZEX / 2, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("NPC", "images/shop/NPC.bmp",92*5, 99*5, true, RGB(255, 0, 0));
	IMAGEMANAGER->addImage("pistol","images/UI/권총.bmp" ,64 ,64 , true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rifle","images/UI/무기.bmp" , 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shield", "images/UI/쉴드.bmp",64,64,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("armor", "images/UI/방어구.bmp",64,64,true,RGB(255,0,255));

	pistolRc = RectMakeCenter(WINSIZEX/2+((IMAGEMANAGER->findImage("pistol")->getWidth())/2), (IMAGEMANAGER->findImage("pistol")->getHeight())/2,IMAGEMANAGER->findImage("pistol")->getWidth(), IMAGEMANAGER->findImage("pistol")->getHeight());
	rifleRc = RectMakeCenter(WINSIZEX / 2 + ((IMAGEMANAGER->findImage("rifle")->getWidth()) / 2 + IMAGEMANAGER->findImage("rifle")->getWidth()), (IMAGEMANAGER->findImage("rifle")->getHeight()) / 2, IMAGEMANAGER->findImage("rifle")->getWidth(), IMAGEMANAGER->findImage("rifle")->getHeight());
	shieldRc = RectMakeCenter(WINSIZEX / 2 + ((IMAGEMANAGER->findImage("shield")->getWidth()) / 2 + 3*(IMAGEMANAGER->findImage("shield")->getWidth())), (IMAGEMANAGER->findImage("shield")->getHeight()) / 2, IMAGEMANAGER->findImage("shield")->getWidth(), IMAGEMANAGER->findImage("shield")->getHeight());
	armorRc = RectMakeCenter(WINSIZEX / 2 + ((IMAGEMANAGER->findImage("armor")->getWidth()) / 2 + 2*(IMAGEMANAGER->findImage("armor")->getWidth())), (IMAGEMANAGER->findImage("armor")->getHeight()) / 2, IMAGEMANAGER->findImage("armor")->getWidth(), IMAGEMANAGER->findImage("armor")->getHeight());
	shopRc = RectMakeCenter(3*(WINSIZEX / 4 ), WINSIZEY / 2, WINSIZEX / 2, WINSIZEY);
	npcRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY - IMAGEMANAGER->findImage("NPC")->getHeight()/2,IMAGEMANAGER->findImage("NPC")->getWidth(), IMAGEMANAGER->findImage("NPC")->getHeight());
	isPistol = false;
	isRifle = false;
	isShield = false;
	isArmor = false;
	isBuy = false;
	isSell = false;
	time = TIMEMANAGER->getWorldTime();
	return S_OK;
}

void shop::release()
{
	SAFE_DELETE(_item);
	SAFE_DELETE(inven);
}

void shop::update()
{
	if (PtInRect(&pistolRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isPistol = true;
		isRifle = false;
		isShield = false;
		isArmor = false;
		position();
	}
	else if (PtInRect(&rifleRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isPistol = false;
		isRifle = true;
		isShield = false;
		isArmor = false;
		position();
	}
	else if (PtInRect(&shieldRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isPistol = false;
		isRifle = false;
		isShield = true;
		isArmor = false;
		position();
	}
	else if (PtInRect(&armorRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isPistol = false;
		isRifle = false;
		isShield = false;
		isArmor = true;
		position();
	}

	itemDescription();
	buyMotion();
}

void shop::render()
{
	char str[256];
	IMAGEMANAGER->render("shopback", getMemDC());
	IMAGEMANAGER->render("NPC", getMemDC(),npcRc.left, npcRc.top);
	//Rectangle(getMemDC(), shopRc.left, shopRc.top, shopRc.right, shopRc.bottom);
	IMAGEMANAGER->render("back", getMemDC(),shopRc.left,shopRc.top);
	IMAGEMANAGER->render("pistol", getMemDC(), pistolRc.left, pistolRc.top);

	IMAGEMANAGER->render("rifle", getMemDC(), rifleRc.left, rifleRc.top);

	IMAGEMANAGER->render("shield", getMemDC(), shieldRc.left, shieldRc.top);
	
	IMAGEMANAGER->render("armor", getMemDC(), armorRc.left, armorRc.top);
	
	if (isPistol == true) {
		for (int i = 0; i < _item->getPistolInfo().size(); i++) {			
			_item->getPistolInfo().at(i).image->render(getMemDC(), _item->getPistolRC(i).left, _item->getPistolRC(i).top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			if (isBuy == false) {
				wsprintf(str, "이름 : ");
				TextOut(getMemDC(), _item->getPistolRC(i).right + 50, _item->getPistolRC(i).top, str, strlen(str));
				wsprintf(str, "%s", _item->getPistolInfo().at(i).name);
				TextOut(getMemDC(), _item->getPistolRC(i).right + 100, _item->getPistolRC(i).top, str, strlen(str));
				wsprintf(str, "%d", _item->getPistolInfo().at(i).price);
				TextOut(getMemDC(), shopRc.right - 50, _item->getPistolRC(i).top, str, strlen(str));
				wsprintf(str, "금액 : ");
				TextOut(getMemDC(), shopRc.right - 100, _item->getPistolRC(i).top, str, strlen(str));
				wsprintf(str, "공격력 : ");
				TextOut(getMemDC(), _item->getPistolRC(i).right + 50, _item->getPistolRC(i).top + 25, str, strlen(str));
				wsprintf(str, "%d", _item->getPistolInfo().at(i).att);
				TextOut(getMemDC(), _item->getPistolRC(i).right + 110, _item->getPistolRC(i).top + 25, str, strlen(str));
				if (PtInRect(&_item->getPistolRC(i), m_ptMouse)) {
					IMAGEMANAGER->findImage("desbutton")->render(getMemDC(), descriptionRc.left, descriptionRc.top);
					wsprintf(str, "%s", _description.c_str());
					TextOut(getMemDC(), descriptionX, descriptionY, str, strlen(str));
				}
			}			
		}
	}
	if (isRifle == true) {
		for (int i = 0; i < _item->getRifleInfo().size(); i++) {
			if (_item->getRifleInfo().at(i).itemKind == item_Rifle || _item->getRifleInfo().at(i).itemKind == item_SubMachineGun) {
				_item->getRifleInfo().at(i).image->render(getMemDC(), _item->getRifleRC(i).left, _item->getRifleRC(i).top);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(255, 255,255));
				if (isBuy == false) {
					wsprintf(str, "이름 : ");
					TextOut(getMemDC(), _item->getRifleRC(i).right + 50, _item->getRifleRC(i).top, str, strlen(str));
					wsprintf(str, "%s", _item->getRifleInfo().at(i).name);
					TextOut(getMemDC(), _item->getRifleRC(i).right + 100, _item->getRifleRC(i).top, str, strlen(str));
					wsprintf(str, "%d", _item->getRifleInfo().at(i).price);
					TextOut(getMemDC(), shopRc.right - 50, _item->getRifleRC(i).top, str, strlen(str));
					wsprintf(str, "금액 : ");
					TextOut(getMemDC(), shopRc.right - 100, _item->getRifleRC(i).top, str, strlen(str));
					wsprintf(str, "공격력 : ");
					TextOut(getMemDC(), _item->getRifleRC(i).right + 50, _item->getRifleRC(i).top + 25, str, strlen(str));
					wsprintf(str, "%d", _item->getRifleInfo().at(i).att);
					TextOut(getMemDC(), _item->getRifleRC(i).right + 110, _item->getRifleRC(i).top + 25, str, strlen(str));
					if (PtInRect(&_item->getRifleRC(i), m_ptMouse)) {
						IMAGEMANAGER->findImage("desbutton")->render(getMemDC(),descriptionRc.left, descriptionRc.top);
						wsprintf(str, "%s", _description.c_str());
						TextOut(getMemDC(), descriptionX, descriptionY, str, strlen(str));
					}
				}
			}
		}
	}
	if (isArmor == true) {
		for (int i = 0; i < _item->getDefInfo().size(); i++) {
			_item->getDefInfo().at(i).image->render(getMemDC(), _item->getDefRC(i).left, _item->getDefRC(i).top);
			
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			if (isBuy == false) {
				wsprintf(str, "이름 : ");
				TextOut(getMemDC(), _item->getDefRC(i).right + 50, _item->getDefRC(i).top, str, strlen(str));
				wsprintf(str, "%s", _item->getDefInfo().at(i).name);
				TextOut(getMemDC(), _item->getDefRC(i).right + 100, _item->getDefRC(i).top, str, strlen(str));
				wsprintf(str, "%d", _item->getDefInfo().at(i).price);
				TextOut(getMemDC(), shopRc.right - 50, _item->getDefRC(i).top, str, strlen(str));
				wsprintf(str, "금액");
				TextOut(getMemDC(), shopRc.right - 100, _item->getDefRC(i).top, str, strlen(str));
				wsprintf(str, "방어력 : ");
				TextOut(getMemDC(), _item->getDefRC(i).right + 50, _item->getDefRC(i).top + 25, str, strlen(str));
				wsprintf(str, "%d", _item->getDefInfo().at(i).def);
				TextOut(getMemDC(), _item->getDefRC(i).right + 110, _item->getDefRC(i).top + 25, str, strlen(str));

				if (PtInRect(&_item->getDefInfo().at(i).itemRc, m_ptMouse)) {
					IMAGEMANAGER->findImage("desbutton")->render(getMemDC(), descriptionRc.left, descriptionRc.top);
					wsprintf(str, "%s", _description.c_str());
					TextOut(getMemDC(), descriptionX, descriptionY, str, strlen(str));
				}
			}
		}
	}
	if (isShield == true) {
		for (int i = 0; i < _item->getShieldInfo().size(); i++) {
			//Rectangle(getMemDC(), _item->getShieldRC(i).left, _item->getShieldRC(i).top, _item->getShieldRC(i).right, _item->getShieldRC(i).bottom);
			_item->getShieldInfo().at(i).image->render(getMemDC(), _item->getShieldRC(i).left, _item->getShieldRC(i).top);
			SetBkMode(getMemDC(), TRANSPARENT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			if (isBuy == false) {
				wsprintf(str, "이름 : ");
				TextOut(getMemDC(), _item->getShieldRC(i).right + 50, _item->getShieldRC(i).top, str, strlen(str));
				wsprintf(str, "%s", _item->getShieldInfo().at(i).name);
				TextOut(getMemDC(), _item->getShieldRC(i).right + 100, _item->getShieldRC(i).top, str, strlen(str));
				wsprintf(str, "%d", _item->getShieldInfo().at(i).price);
				TextOut(getMemDC(), shopRc.right - 50, _item->getShieldRC(i).top, str, strlen(str));
				wsprintf(str, "금액");
				TextOut(getMemDC(), shopRc.right - 100, _item->getShieldRC(i).top, str, strlen(str));
				wsprintf(str, "방어력 : ");
				TextOut(getMemDC(), _item->getShieldRC(i).right + 50, _item->getShieldRC(i).top + 25, str, strlen(str));
				wsprintf(str, "%d", _item->getShieldInfo().at(i).def);
				TextOut(getMemDC(), _item->getShieldRC(i).right + 110, _item->getShieldRC(i).top + 25, str, strlen(str));
				wsprintf(str, "공격력 : ");
				TextOut(getMemDC(), _item->getShieldRC(i).right + 160, _item->getShieldRC(i).top + 25, str, strlen(str));
				wsprintf(str, "%d", _item->getShieldInfo().at(i).att);
				TextOut(getMemDC(), _item->getShieldRC(i).right + 220, _item->getShieldRC(i).top + 25, str, strlen(str));
				if (PtInRect(&_item->getShieldInfo().at(i).itemRc, m_ptMouse)) {
					IMAGEMANAGER->findImage("desbutton")->render(getMemDC(), descriptionRc.left, descriptionRc.top);
					wsprintf(str, "%s", _description.c_str());
					TextOut(getMemDC(), descriptionX, descriptionY, str, strlen(str));
				}
			}
		}
	}
	if (isSell == true) {
		//Rectangle(getMemDC(), npcTalkRc.left, npcTalkRc.top, npcTalkRc.right, npcTalkRc.bottom);
		FrameRect(getMemDC(), &npcTalkRc, CreateSolidBrush(RGB(0, 0, 0)));
		wsprintf(str, "조심히 사용하시게나", _description.c_str());
		TextOut(getMemDC(), WINSIZEX/4 - 100,WINSIZEY - 100, str, strlen(str));
	}

	wsprintf(str, "소지금 : ");
	TextOut(getMemDC(),WINSIZEX - 120, 50, str, strlen(str));
	wsprintf(str, "%d", inven->getMoney());
	TextOut(getMemDC(),WINSIZEX - 50, 50, str, strlen(str));
}

void shop::position()
{	
		for (int x = 0; x < _item->getRifleInfo().size() ; x++) {
			if (isRifle == true) {
				_item->getRifleRC(x);
				rifleKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getRifleInfo().at(x).image->getWidth() / 2), 150 + (x * _item->getRifleInfo().at(x).image->getHeight()), _item->getRifleInfo().at(x).image->getWidth(), _item->getRifleInfo().at(x).image->getHeight());
				_item->setRifleRC(x, rifleKindRc);
			}
			else {
				rifleKindRc = RectMakeCenter(WINSIZEX + (_item->getRifleInfo().at(x).image->getWidth() / 2), 150 + (x * _item->getRifleInfo().at(x).image->getHeight()), _item->getRifleInfo().at(x).image->getWidth(), _item->getRifleInfo().at(x).image->getHeight());
				_item->setRifleRC(x, rifleKindRc);
			}
		}
		for (int y = 0; y < _item->getPistolInfo().size(); y++) {
			if (isPistol == true) {
				_item->getPistolRC(y);
				pistolKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getPistolInfo().at(y).image->getWidth() / 2), shopRc.left + _item->getPistolInfo().at(y).image->getWidth()/2, _item->getPistolInfo().at(y).image->getWidth(), _item->getPistolInfo().at(y).image->getHeight());
				_item->setPistolRC(y, pistolKindRc);
			}
			else {
				pistolKindRc = RectMakeCenter(WINSIZEX + (_item->getPistolInfo().at(y).image->getWidth() / 2), 150 + (y * _item->getPistolInfo().at(y).image->getHeight()), _item->getPistolInfo().at(y).image->getWidth(), _item->getPistolInfo().at(y).image->getHeight());
				_item->setPistolRC(y, pistolKindRc);
			}
		}
		for (int z = 0; z < _item->getDefInfo().size(); z++) {
			if (isArmor == true) {
				_item->getDefRC(z);
				armorKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getDefInfo().at(z).image->getWidth() / 2), 150 + (z * _item->getDefInfo().at(z).image->getHeight()), _item->getDefInfo().at(z).image->getWidth(), _item->getDefInfo().at(z).image->getHeight());
				_item->setDefRC(z, armorKindRc);

			}
			else {
				armorKindRc = RectMakeCenter(WINSIZEX + (_item->getDefInfo().at(z).image->getWidth() / 2), 150 + (z * _item->getDefInfo().at(z).image->getHeight()), _item->getDefInfo().at(z).image->getWidth(), _item->getDefInfo().at(z).image->getHeight());
				_item->setDefRC(z, armorKindRc);
			}
		}
		for (int a = 0; a < _item->getShieldInfo().size(); a++) {
			if (isShield == true) {
				_item->getShieldRC(a);
				shieldKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getShieldInfo().at(a).image->getWidth() / 2), 150 + (a * _item->getShieldInfo().at(a).image->getHeight()), _item->getShieldInfo().at(a).image->getWidth(), _item->getShieldInfo().at(a).image->getHeight());
				_item->setShieldRC(a, shieldKindRc);
			}
			else {
				shieldKindRc = RectMakeCenter(WINSIZEX + (_item->getShieldInfo().at(a).image->getWidth() / 2), 150 + (a * _item->getShieldInfo().at(a).image->getHeight()), _item->getShieldInfo().at(a).image->getWidth(), _item->getShieldInfo().at(a).image->getHeight());
				_item->setShieldRC(a, shieldKindRc);
			}
		}
}

void shop::buyMotion()
{

	RECT temp;
	
	if (isRifle == true) {		
		for (int i = 0; i < _item->getRifleInfo().size(); i++) {
			
			
				if (PtInRect(&_item->getRifleRC(i), m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
					isBuy = true;
					rifleKindRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _item->getRifleInfo().at(i).image->getWidth(), _item->getRifleInfo().at(i).image->getHeight());
					_item->setRifleRC(i, rifleKindRc);
					break;
				}
				else { 
					isBuy = false;
					if ((_item->getRifleRC(i).right < npcRc.right) && (inven->getMoney() > _item->getRifleInfo().at(i).price)) {						
						money = (inven->getMoney()) - (_item->getRifleInfo().at(i).price);
						buy(i);
						isSell = true;
						
						npcTalkRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY - 100, WINSIZEX / 2, 100);
						inven->setMoney(money);	
						if (TIMEMANAGER->getWorldTime() - time > 2)
						{
							time = TIMEMANAGER->getWorldTime();
							isSell = false;
							npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
						}
					}
					else {
						rifleKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getRifleInfo().at(i).image->getWidth() / 2), 150 + (i * _item->getRifleInfo().at(i).image->getHeight()), _item->getRifleInfo().at(i).image->getWidth(), _item->getRifleInfo().at(i).image->getHeight());
						_item->setRifleRC(i, rifleKindRc);
						
						if (TIMEMANAGER->getWorldTime() - time > 2)
						{
							time = TIMEMANAGER->getWorldTime();
							isSell = false;
							npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
						}
					}
				}
					
		}
	}
	if (isPistol == true) {
		for (int i = 0 ; i < _item->getPistolInfo().size(); i++) {
			if (PtInRect(&_item->getPistolRC(i), m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				isBuy = true;
				pistolKindRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _item->getPistolInfo().at(i).image->getWidth(), _item->getPistolInfo().at(i).image->getHeight());
				_item->setPistolRC(i, pistolKindRc);
				break;
			}
			else {
				isBuy = false;
				if ((_item->getPistolRC(i).right < npcRc.right)&& (inven->getMoney() > _item->getPistolInfo().at(i).price)) {				
					money = (inven->getMoney()) - (_item->getPistolInfo().at(i).price);
					buy(i);
					isSell = true;
					
					npcTalkRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY - 100, WINSIZEX / 2, 100);
					inven->setMoney(money);
					if (TIMEMANAGER->getWorldTime() - time > 2)
					{
						time = TIMEMANAGER->getWorldTime();
						isSell = false;
						npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
					}
				}
				else {
					
					pistolKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getPistolInfo().at(i).image->getWidth() / 2), 150 + (i * _item->getPistolInfo().at(i).image->getHeight()), _item->getPistolInfo().at(i).image->getWidth(), _item->getPistolInfo().at(i).image->getHeight());
					_item->setPistolRC(i, pistolKindRc);
					if (TIMEMANAGER->getWorldTime() - time > 2)
					{
						time = TIMEMANAGER->getWorldTime();
						isSell = false;
						npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
					}
				}
			}
		}
	}
	if (isArmor == true) {
		for (int i = 0; i < _item->getDefInfo().size(); i++) {
			if (PtInRect(&_item->getDefRC(i), m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				isBuy = true;
				armorKindRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _item->getDefInfo().at(i).image->getWidth(), _item->getDefInfo().at(i).image->getHeight());
				_item->setDefRC(i, armorKindRc);
				break;
			}
			else {
				isBuy = false;
				if ((_item->getDefRC(i).right < npcRc.right)&& (inven->getMoney() > _item->getDefInfo().at(i).price)) {
					money = (inven->getMoney()) - (_item->getDefInfo().at(i).price);
					buy(i);
					isSell = true;
					
					npcTalkRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY - 100, WINSIZEX / 2, 100);
					inven->setMoney(money);
					if (TIMEMANAGER->getWorldTime() - time > 2)
					{
						time = TIMEMANAGER->getWorldTime();
						isSell = false;
						npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
					}
				}
				else {
					
					armorKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getDefInfo().at(i).image->getWidth() / 2), 150 + (i * _item->getDefInfo().at(i).image->getHeight()), _item->getDefInfo().at(i).image->getWidth(), _item->getDefInfo().at(i).image->getHeight());
					_item->setDefRC(i, armorKindRc);
					if (TIMEMANAGER->getWorldTime() - time > 2)
					{
						time = TIMEMANAGER->getWorldTime();
						isSell = false;
						npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
					}
				}
			}
		}
	}
	if (isShield == true) {
		for (int i = 0; i < _item->getShieldInfo().size(); i++) {
			if (PtInRect(&_item->getShieldRC(i), m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				isBuy = true;
				shieldKindRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _item->getShieldInfo().at(i).image->getWidth(), _item->getShieldInfo().at(i).image->getHeight());
				_item->setShieldRC(i, shieldKindRc);
				break;
			}
			else {
				isBuy = false;
				if ((_item->getShieldRC(i).right < npcRc.right ) && (inven->getMoney() > _item->getShieldInfo().at(i).price)){
					money = (inven->getMoney()) - (_item->getShieldInfo().at(i).price);
					buy(i);
					isSell = true;
					
					npcTalkRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY - 100, WINSIZEX / 2, 100);
					inven->setMoney(money);
					if (TIMEMANAGER->getWorldTime() - time > 2)
					{
						time = TIMEMANAGER->getWorldTime();
						isSell = false;
						npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
					}
				}
				else {
					
					shieldKindRc = RectMakeCenter(WINSIZEX / 2 + (_item->getShieldInfo().at(i).image->getWidth() / 2), 150 + (i * _item->getShieldInfo().at(i).image->getHeight()), _item->getShieldInfo().at(i).image->getWidth(), _item->getShieldInfo().at(i).image->getHeight());
					_item->setShieldRC(i, shieldKindRc);
					if (TIMEMANAGER->getWorldTime() - time > 2)
					{						
						time = TIMEMANAGER->getWorldTime();
						isSell = false;
						npcTalkRc = RectMakeCenter(WINSIZEX + 1000, WINSIZEY - 100, WINSIZEX / 2, 100);
					}					
				}
			}			
		}
	}
}

void shop::buy(int i)
{	
	if (isPistol == true) {
		vector<TAGITEMINFO> _tempPistol = _item->getPistolInfo();
		_tempPistol.at(i).itemRc = RectMakeCenter(0, 0, _tempPistol.at(i).image->getWidth(), _tempPistol.at(i).image->getHeight());
		inven->setPistol(_tempPistol.at(i));
		_tempPistol.erase(_tempPistol.begin() + i);
		_item->setPistolInfo(_tempPistol);
	}
	if (isRifle == true) {
		_tempRifle = _item->getRifleInfo();
		_tempRifle.at(i).itemRc = RectMakeCenter(0, 0, _tempRifle.at(i).image->getWidth(), _tempRifle.at(i).image->getHeight());
		inven->setRifle(_tempRifle.at(i));
		_tempRifle.erase(_tempRifle.begin() + i);
		_item->setRifleInfo(_tempRifle);
	}
	if (isArmor == true) {
		vector<TAGITEMINFO> _tempDef = _item->getDefInfo();
		_tempDef.at(i).itemRc = RectMakeCenter(0, 0, _tempDef.at(i).image->getWidth(), _tempDef.at(i).image->getHeight());
		inven->setArmor(_tempDef.at(i));
		_tempDef.erase(_tempDef.begin() + i);
		_item->setDefInfo(_tempDef);
	}
	if (isShield == true) {
		vector<TAGITEMINFO> _tempShield = _item->getShieldInfo();
		_tempShield.at(i).itemRc = RectMakeCenter(0, 0, _tempShield.at(i).image->getWidth(), _tempShield.at(i).image->getHeight());
		inven->setShield(_tempShield.at(i));
		_tempShield.erase(_tempShield.begin() + i);
		_item->setShieldInfo(_tempShield);
	}
}

void shop::itemDescription()
{
	if (isPistol == true) {
		for (int i = 0; i < _item->getPistolInfo().size(); i++) {
			if (PtInRect(&_item->getPistolRC(i), m_ptMouse)) {
				_description = _item->getPistolInfo().at(i).description;				
				descriptionRc = RectMakeCenter((npcRc.right - npcRc.left) / 2 + npcRc.left, npcRc.top - 50, 350, 100);
				descriptionX = descriptionRc.left + 25;
				descriptionY = (descriptionRc.bottom - descriptionRc.top) / 2 + descriptionRc.top;
			}
			
		}
	}	
	else if (isRifle == true) {
		for (int i = 0; i < _item->getRifleInfo().size(); i++) {
			if (PtInRect(&_item->getRifleRC(i), m_ptMouse)) {
				_description = _item->getRifleInfo().at(i).description;				
				descriptionRc = RectMakeCenter((npcRc.right - npcRc.left) / 2 + npcRc.left, npcRc.top - 50, 350, 100);
				descriptionX = descriptionRc.left + 25;
				descriptionY = (descriptionRc.bottom - descriptionRc.top) / 2 + descriptionRc.top;
			}
			
		}
	}	
	else if (isArmor == true) {
		for (int i = 0; i < _item->getDefInfo().size(); i++) {
			if (PtInRect(&_item->getDefRC(i), m_ptMouse)) {
				_description = _item->getDefInfo().at(i).description;				
				descriptionRc = RectMakeCenter((npcRc.right - npcRc.left)/2 + npcRc.left, npcRc.top - 50, 350, 100);
				descriptionX = descriptionRc.left + 25;
				descriptionY = (descriptionRc.bottom - descriptionRc.top) / 2 + descriptionRc.top;
			}
		}
	}	
	else if (isShield == true) {
		for (int i = 0; i < _item->getShieldInfo().size(); i++) {
			if (PtInRect(&_item->getShieldRC(i), m_ptMouse)) {
				_description = _item->getShieldInfo().at(i).description;				
				descriptionRc = RectMakeCenter((npcRc.right - npcRc.left) / 2 + npcRc.left, npcRc.top - 50, 350, 100);
				descriptionX = descriptionRc.left + 25;
				descriptionY = (descriptionRc.bottom - descriptionRc.top) / 2 + descriptionRc.top;
			}
			
		}
	}	
	else {
		descriptionRc = RectMakeCenter(WINSIZEX - 500, WINSIZEY, 100, 100);
	}
}
