#include "stdafx.h"
#include "inventory.h"


inventory::inventory()
{
}


inventory::~inventory()
{

}

HRESULT inventory::init()
{	
	playerMoney = 1000;
	_item = new item;
	_item->init();
	IMAGEMANAGER->addImage("select", "images/shop/설명창.bmp", 350, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("weapon", "images/UI/무기UI.bmp", 202, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("def", "images/UI/방어.bmp",202, 68, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pistol", "images/UI/권총.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("rifle", "images/UI/무기.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shield", "images/UI/쉴드.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("armor", "images/UI/armor.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("back", "images/shop/shopBack.bmp", WINSIZEX / 2, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Unit", "images/shop/sample.bmp", 89*2, 66*2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("pistolUnit", "images/unit/swat_pistol.bmp",1920,1528,16,12,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("rifleUnit", "images/unit/swat_rifle.bmp",2048 ,1536 ,16,12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("shieldUnit", "images/unit/swat_shield.bmp", 2048,1536 ,16,12, true, RGB(255, 0, 255));

	

	viewRc = RectMake(0, 0, WINSIZEX / 2, WINSIZEY);
	isWeapon = false;
	isArmor = false;

	isPistolOn = false;
	isRifleOn = false;
	isArmorOn = false;
	isShieldOn = false;
	
	isClick = false;

	isSelectPistol = false;
	isSelectRifle = false;
	isSelectShield = false;
	isSelectArmor = false;

	invenRc = RectMakeCenter(3 * (WINSIZEX / 4), WINSIZEY / 2, WINSIZEX / 2, WINSIZEY);
	
	selectWeaponRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY / 2 - 100, IMAGEMANAGER->findImage("select")->getWidth(), IMAGEMANAGER->findImage("select")->getHeight());
	selectArmorRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY / 2 + 100, IMAGEMANAGER->findImage("select")->getWidth(), IMAGEMANAGER->findImage("select")->getHeight());
	charcterRc = RectMakeCenter(WINSIZEX / 4, 100, IMAGEMANAGER->findImage("Unit")->getWidth(), IMAGEMANAGER->findImage("Unit")->getHeight());
	onWeaponNum = 0;
	selectRifleWeaponNum = 0;
	selectPistolWeaponNum = 0;
	selectShieldWeaponNum = 0;
	selectArmorNum = 0;
	sound = 1.0f;
	return S_OK;
}

void inventory::release()
{
	
	SAFE_DELETE(_item);
}

void inventory::update()
{
	uiPosition();
	selectItem();

	unitAnimation();
	
}

void inventory::render()
{
	
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	Rectangle(getMemDC(), viewRc.left, viewRc.top, viewRc.right, viewRc.bottom);
	IMAGEMANAGER->findImage("back")->render(getMemDC(), viewRc.left, viewRc.top);
	Rectangle(getMemDC(), selectWeaponRc.left, selectWeaponRc.top, selectWeaponRc.right, selectWeaponRc.bottom);
	IMAGEMANAGER->findImage("select")->render(getMemDC(), selectWeaponRc.left, selectWeaponRc.top);
	Rectangle(getMemDC(), selectArmorRc.left, selectArmorRc.top, selectArmorRc.right, selectArmorRc.bottom);
	IMAGEMANAGER->findImage("select")->render(getMemDC(), selectArmorRc.left, selectArmorRc.top);

	Rectangle(getMemDC(), invenRc.left, invenRc.top, invenRc.right, invenRc.bottom);
	IMAGEMANAGER->findImage("back")->render(getMemDC(), invenRc.left, invenRc.top);
	//Rectangle(getMemDC(), weaponRc.left, weaponRc.top,weaponRc.right,weaponRc.bottom);
	IMAGEMANAGER->findImage("weapon")->render(getMemDC(), weaponRc.left, weaponRc.top);
	//Rectangle(getMemDC(), defRc.left, defRc.top, defRc.right, defRc.bottom);
	IMAGEMANAGER->findImage("def")->render(getMemDC(), defRc.left, defRc.top);

	if (isWeapon == true) {
		//Rectangle(getMemDC(), pistolRc.left, pistolRc.top, pistolRc.right, pistolRc.bottom);
		IMAGEMANAGER->findImage("pistol")->render(getMemDC(), pistolRc.left, pistolRc.top);
		//Rectangle(getMemDC(), rifleRc.left, rifleRc.top, rifleRc.right, rifleRc.bottom);
		IMAGEMANAGER->findImage("rifle")->render(getMemDC(), rifleRc.left, rifleRc.top);
		//Rectangle(getMemDC(), shieldRc.left, shieldRc.top, shieldRc.right, shieldRc.bottom);
		IMAGEMANAGER->findImage("shield")->render(getMemDC(), shieldRc.left, shieldRc.top);
	}
	if (isArmor == true) {
		//Rectangle(getMemDC(), armorRc.left, armorRc.top, armorRc.right, armorRc.bottom);
		IMAGEMANAGER->findImage("armor")->render(getMemDC(), armorRc.left, armorRc.top);
	}

	if (isPistolOn == true) {
		if (_uPistol.size() < 1) {
			TextOut(getMemDC(), 3*(WINSIZEX / 4) - 200, WINSIZEY / 2, "권총이 없습니다.", 16);
		}
		for (int i = 0; i < _uPistol.size(); i++) {
			//Rectangle(getMemDC(), _uPistol.at(i).itemRc.left, _uPistol.at(i).itemRc.top, _uPistol.at(i).itemRc.right, _uPistol.at(i).itemRc.bottom);
			_uPistol.at(i).image->render(getMemDC(), _uPistol.at(i).itemRc.left, _uPistol.at(i).itemRc.top);
		}
	}
	if (isRifleOn == true) {
		if (_uRifle.size() < 1) {
			TextOut(getMemDC(), 3 * (WINSIZEX / 4) - 200, WINSIZEY / 2, "소총이 없습니다.", 16);
		}
		for (int i = 0; i < _uRifle.size(); i++) {
			_uRifle.at(i).image->render(getMemDC(), _uRifle.at(i).itemRc.left, _uRifle.at(i).itemRc.top);
		}
	}
	if (isArmorOn == true) {
		if (_uArmor.size() < 1) {
			TextOut(getMemDC(), 3 * (WINSIZEX / 4) - 200, WINSIZEY / 2, "방어구가 없습니다.", 18);
		}
		for (int i = 0; i < _uArmor.size(); i++) {
			_uArmor.at(i).image->render(getMemDC(), _uArmor.at(i).itemRc.left, _uArmor.at(i).itemRc.top);
		}
	}
	if (isShieldOn == true) {
		if (_uShield.size() < 1) {
			TextOut(getMemDC(), 3 * (WINSIZEX / 4) - 200, WINSIZEY / 2, "방패가 없습니다.", 16);
		}
		for (int i = 0; i < _uShield.size(); i++) {
			_uShield.at(i).image->render(getMemDC(), _uShield.at(i).itemRc.left, _uShield.at(i).itemRc.top);
		}
	}
	Rectangle(getMemDC(), charcterRc.left, charcterRc.top, charcterRc.right, charcterRc.bottom);
	if (isSelectArmor == true) {
		_uArmor.at(selectArmorNum).image->render(getMemDC(), _uArmor.at(selectArmorNum).itemRc.left, _uArmor.at(selectArmorNum).itemRc.top);

	}
	if (isSelectPistol == true) {
		_uPistol.at(selectPistolWeaponNum).image->render(getMemDC(), _uPistol.at(selectPistolWeaponNum).itemRc.left, _uPistol.at(selectPistolWeaponNum).itemRc.top);
		IMAGEMANAGER->findImage("pistolUnit")->frameRender(getMemDC(), charcterRc.left, charcterRc.top, IMAGEMANAGER->findImage("pistolUnit")->getFrameX(), IMAGEMANAGER->findImage("pistolUnit")->getFrameY());
	}
	if (isSelectRifle == true) {
		_uRifle.at(selectRifleWeaponNum).image->render(getMemDC(), _uRifle.at(selectRifleWeaponNum).itemRc.left, _uRifle.at(selectRifleWeaponNum).itemRc.top);
		IMAGEMANAGER->findImage("rifleUnit")->frameRender(getMemDC(), charcterRc.left, charcterRc.top, IMAGEMANAGER->findImage("rifleUnit")->getFrameX(), IMAGEMANAGER->findImage("rifleUnit")->getFrameY());
	}
	if (isSelectShield == true) {
		_uShield.at(selectShieldWeaponNum).image->render(getMemDC(), _uShield.at(selectShieldWeaponNum).itemRc.left, _uShield.at(selectShieldWeaponNum).itemRc.top);
		IMAGEMANAGER->findImage("shieldUnit")->frameRender(getMemDC(), charcterRc.left, charcterRc.top, IMAGEMANAGER->findImage("shieldUnit")->getFrameX(), IMAGEMANAGER->findImage("shieldUnit")->getFrameY());
	}
	if (isSelectPistol == false && isSelectRifle == false && isSelectShield == false) {
		IMAGEMANAGER->findImage("Unit")->render(getMemDC(), charcterRc.left, charcterRc.top);
	}

	
	
	TextOut(getMemDC(), WINSIZEX / 4-200, WINSIZEY / 2 + 200, "공격력", 6);	
	wsprintf(str, "%d", unitAtt);
	TextOut(getMemDC(), WINSIZEX / 4 - 100, WINSIZEY / 2 + 200, str, strlen(str));
	

	
	TextOut(getMemDC(), WINSIZEX / 4 - 200, WINSIZEY / 2 + 270, "방어력", 6);	
	wsprintf(str, "%d", unitDef);
	TextOut(getMemDC(), WINSIZEX / 4 - 100, WINSIZEY / 2 + 270, str, strlen(str));


}


void inventory::uiPosition()
{
	weaponRc = RectMakeCenter(WINSIZEX / 2 + (IMAGEMANAGER->findImage("weapon")->getWidth())/2, IMAGEMANAGER->findImage("weapon")->getHeight() / 2, IMAGEMANAGER->findImage("weapon")->getWidth(), IMAGEMANAGER->findImage("weapon")->getHeight());
	defRc = RectMakeCenter(weaponRc.right + (IMAGEMANAGER->findImage("def")->getWidth()) / 2, IMAGEMANAGER->findImage("def")->getHeight() / 2, IMAGEMANAGER->findImage("def")->getWidth(), IMAGEMANAGER->findImage("def")->getHeight());
	if (PtInRect(&weaponRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isWeapon = true;		
		isArmor = false;
		isRifleOn = false;
		isPistolOn = false;
		isArmorOn = false;
		isShieldOn = false;
	}
	
	if (PtInRect(&defRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isWeapon = false;
		isArmor = true;
		isRifleOn = false;
		isPistolOn = false;
		isArmorOn = false;
		isShieldOn = false;
	}
	
	if (isWeapon == true) {
		pistolRc = RectMakeCenter(WINSIZEX / 2 + (IMAGEMANAGER->findImage("pistol")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("pistol")->getHeight() / 2), IMAGEMANAGER->findImage("pistol")->getWidth(), IMAGEMANAGER->findImage("pistol")->getHeight());
		rifleRc = RectMakeCenter(pistolRc.right + (IMAGEMANAGER->findImage("rifle")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("rifle")->getHeight() / 2), IMAGEMANAGER->findImage("rifle")->getWidth(), IMAGEMANAGER->findImage("rifle")->getHeight());
		shieldRc = RectMakeCenter(rifleRc.right + (IMAGEMANAGER->findImage("shield")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("shield")->getHeight() / 2), IMAGEMANAGER->findImage("shield")->getWidth(), IMAGEMANAGER->findImage("shield")->getHeight());
		if (PtInRect(&pistolRc, m_ptMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			isArmorOn = false;
			isPistolOn = true;
			isRifleOn = false;
			isShieldOn = false;
		}
		if (PtInRect(&shieldRc, m_ptMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			isArmorOn = false;
			isPistolOn = false;
			isRifleOn = false;
			isShieldOn = true;
		}
		if (PtInRect(&rifleRc, m_ptMouse) && KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
			isArmorOn = false;
			isPistolOn = false;
			isRifleOn = true;
			isShieldOn = false;
		}
	}
	else {
		pistolRc = RectMakeCenter(WINSIZEX + (IMAGEMANAGER->findImage("pistol")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("pistol")->getHeight() / 2), IMAGEMANAGER->findImage("pistol")->getWidth(), IMAGEMANAGER->findImage("pistol")->getHeight());
		rifleRc = RectMakeCenter(WINSIZEX + (IMAGEMANAGER->findImage("rifle")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("rifle")->getHeight() / 2), IMAGEMANAGER->findImage("rifle")->getWidth(), IMAGEMANAGER->findImage("rifle")->getHeight());
		shieldRc = RectMakeCenter(WINSIZEX + (IMAGEMANAGER->findImage("shield")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("shield")->getHeight() / 2), IMAGEMANAGER->findImage("shield")->getWidth(), IMAGEMANAGER->findImage("shield")->getHeight());
	}

	if (isArmor == true) {
		armorRc = RectMakeCenter(WINSIZEX / 2 + (IMAGEMANAGER->findImage("armor")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("armor")->getHeight() / 2), IMAGEMANAGER->findImage("armor")->getWidth(), IMAGEMANAGER->findImage("armor")->getHeight());
		if (PtInRect(&armorRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
			isArmorOn = true;
			isPistolOn = false;
			isRifleOn = false;
			isShieldOn = false;
		}
	}
	else {
		armorRc = RectMakeCenter(WINSIZEX + (IMAGEMANAGER->findImage("armor")->getWidth() / 2), weaponRc.bottom + (IMAGEMANAGER->findImage("armor")->getHeight() / 2), IMAGEMANAGER->findImage("armor")->getWidth(), IMAGEMANAGER->findImage("armor")->getHeight());
	}
	
}

void inventory::selectItem()
{
	RECT temp;
	if (isPistolOn == true) {
		for (int i = 0; i < _uPistol.size(); i++) {
			if (PtInRect(&_uPistol.at(i).itemRc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				isClick = true;
				_uPistol.at(i).itemRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _uPistol.at(i).image->getWidth(), _uPistol.at(i).image->getHeight());				
				onWeaponNum = i;
				break;
			}
			else {
				if (IntersectRect(&temp, &_uPistol.at(i).itemRc, &selectWeaponRc)) {
					isClick = false;
					if (isSelectPistol == true) {
						_uPistol.at(selectPistolWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uPistol.at(selectPistolWeaponNum).image->getWidth() / 2, 200 + (selectPistolWeaponNum * _uPistol.at(selectPistolWeaponNum).image->getHeight()), _uPistol.at(selectPistolWeaponNum).image->getWidth(), _uPistol.at(selectPistolWeaponNum).image->getHeight());
					}
					if (isSelectRifle == true) {
						_uRifle.at(selectRifleWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uRifle.at(selectRifleWeaponNum).image->getWidth() / 2, 200 + (selectRifleWeaponNum * _uRifle.at(selectRifleWeaponNum).image->getHeight()), _uRifle.at(selectRifleWeaponNum).image->getWidth(), _uRifle.at(selectRifleWeaponNum).image->getHeight());
					}
					if (isSelectShield == true) {
						_uShield.at(selectShieldWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uShield.at(selectShieldWeaponNum).image->getWidth() / 2, 200 + (i * _uShield.at(selectShieldWeaponNum).image->getHeight()), _uShield.at(selectShieldWeaponNum).image->getWidth(), _uShield.at(selectShieldWeaponNum).image->getHeight());
					}
					
					isSelectPistol = true;
					isSelectRifle = false;
					isSelectShield = false;
					
					charcterRc = RectMakeCenter(WINSIZEX / 4, 100, IMAGEMANAGER->findImage("pistolUnit")->getFrameWidth(), IMAGEMANAGER->findImage("pistolUnit")->getFrameHeight());
					_uPistol.at(i).itemRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY / 2 - 100, _uPistol.at(i).image->getWidth(), _uPistol.at(i).image->getHeight());
					selectPistolWeaponNum = i;
					onWeaponNum = 0;

					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
					break;
				}
				else {
					isSelectPistol = false;
					isClick = false;
					_uPistol.at(i).itemRc = RectMakeCenter(WINSIZEX / 2 + _uPistol.at(i).image->getWidth() / 2, 200 + (i * _uPistol.at(i).image->getHeight()), _uPistol.at(i).image->getWidth(), _uPistol.at(i).image->getHeight());
					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
				}
			}
		}
	}

	if (isRifleOn == true) {
		for (int i = 0; i < _uRifle.size(); i++) {
			if (PtInRect(&_uRifle.at(i).itemRc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				isClick = true;
				_uRifle.at(i).itemRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _uRifle.at(i).image->getWidth(), _uRifle.at(i).image->getHeight());
				onWeaponNum = i;
				break;
			}
			else {
				if (IntersectRect(&temp, &_uRifle.at(i).itemRc, &selectWeaponRc)) {
					isClick = false;
					if (isSelectPistol == true) {
						_uPistol.at(selectPistolWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uPistol.at(selectPistolWeaponNum).image->getWidth() / 2, 200 + (selectPistolWeaponNum * _uPistol.at(selectPistolWeaponNum).image->getHeight()), _uPistol.at(selectPistolWeaponNum).image->getWidth(), _uPistol.at(selectPistolWeaponNum).image->getHeight());
					}
					if (isSelectRifle == true) {
						_uRifle.at(selectRifleWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uRifle.at(selectRifleWeaponNum).image->getWidth() / 2, 200 + (selectRifleWeaponNum * _uRifle.at(selectRifleWeaponNum).image->getHeight()), _uRifle.at(selectRifleWeaponNum).image->getWidth(), _uRifle.at(selectRifleWeaponNum).image->getHeight());
					}
					if (isSelectShield == true) {
						_uShield.at(selectShieldWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uShield.at(selectShieldWeaponNum).image->getWidth() / 2, 200 + (i * _uShield.at(selectShieldWeaponNum).image->getHeight()), _uShield.at(selectShieldWeaponNum).image->getWidth(), _uShield.at(selectShieldWeaponNum).image->getHeight());
					}
					
					isSelectRifle = true;
					isSelectPistol = false;
					isSelectShield = false;
					
					charcterRc = RectMakeCenter(WINSIZEX / 4, 100, IMAGEMANAGER->findImage("rifleUnit")->getFrameWidth(), IMAGEMANAGER->findImage("rifleUnit")->getFrameHeight());
					_uRifle.at(i).itemRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY / 2 - 100, _uRifle.at(i).image->getWidth(), _uRifle.at(i).image->getHeight());
					selectRifleWeaponNum = i;
					onWeaponNum = 0;
					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
					break;
				}
				else {
					isSelectRifle = false;
					isClick = false;
					_uRifle.at(i).itemRc = RectMakeCenter(WINSIZEX / 2 + _uRifle.at(i).image->getWidth() / 2, 200 + (i * _uRifle.at(i).image->getHeight()), _uRifle.at(i).image->getWidth(), _uRifle.at(i).image->getHeight());					
					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
				}
			}
		}
	}

	if (isShieldOn == true) {
		for (int i = 0; i < _uShield.size(); i++) {
			if (PtInRect(&_uShield.at(i).itemRc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				isClick = true;
				_uShield.at(i).itemRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _uShield.at(i).image->getWidth(), _uShield.at(i).image->getHeight());
				onWeaponNum = i;
				break;
			}
			else {
				if (IntersectRect(&temp, &_uShield.at(i).itemRc, &selectWeaponRc)) {
					isClick = false;
					if (isSelectPistol == true) {
						_uPistol.at(selectPistolWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uPistol.at(selectPistolWeaponNum).image->getWidth() / 2, 200 + (selectPistolWeaponNum * _uPistol.at(selectPistolWeaponNum).image->getHeight()), _uPistol.at(selectPistolWeaponNum).image->getWidth(), _uPistol.at(selectPistolWeaponNum).image->getHeight());
					}
					if (isSelectRifle == true) {
						_uRifle.at(selectRifleWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uRifle.at(selectRifleWeaponNum).image->getWidth() / 2, 200 + (selectRifleWeaponNum * _uRifle.at(selectRifleWeaponNum).image->getHeight()), _uRifle.at(selectRifleWeaponNum).image->getWidth(), _uRifle.at(selectRifleWeaponNum).image->getHeight());
					}
					if (isSelectShield == true) {
						_uShield.at(selectShieldWeaponNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uShield.at(selectShieldWeaponNum).image->getWidth() / 2, 200 + (i * _uShield.at(selectShieldWeaponNum).image->getHeight()), _uShield.at(selectShieldWeaponNum).image->getWidth(), _uShield.at(selectShieldWeaponNum).image->getHeight());
					}
				
					isSelectShield = true;
					isSelectPistol = false;
					isSelectRifle = false;
					
					charcterRc = RectMakeCenter(WINSIZEX / 4, 100, IMAGEMANAGER->findImage("shieldUnit")->getFrameWidth(), IMAGEMANAGER->findImage("shieldUnit")->getFrameHeight());
					_uShield.at(i).itemRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY / 2 - 100, _uShield.at(i).image->getWidth(), _uShield.at(i).image->getHeight());
					selectShieldWeaponNum = i;
					onWeaponNum = 0;
					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
					break;
				}
				else {
					isSelectShield = false;
					isClick = false;
					_uShield.at(i).itemRc = RectMakeCenter(WINSIZEX / 2 + _uShield.at(i).image->getWidth() / 2, 200 + (i * _uShield.at(i).image->getHeight()), _uShield.at(i).image->getWidth(), _uShield.at(i).image->getHeight());
					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
				}
			}
		}
	}

	if (isArmorOn == true) {
		for (int i = 0; i < _uArmor.size(); i++) {
			if (PtInRect(&_uArmor.at(i).itemRc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON)) {
				isClick = true;
				_uArmor.at(i).itemRc = RectMakeCenter(m_ptMouse.x, m_ptMouse.y, _uArmor.at(i).image->getWidth(), _uArmor.at(i).image->getHeight());
				onDefNum = i;
				break;
			}
			else {
				if (IntersectRect(&temp, &_uArmor.at(i).itemRc, &selectArmorRc)) {
					isClick = false;
					if (isSelectArmor == true) {
						_uArmor.at(selectArmorNum).itemRc = RectMakeCenter(WINSIZEX / 2 + _uArmor.at(selectArmorNum).image->getWidth() / 2, 200 + (selectArmorNum * _uArmor.at(selectArmorNum).image->getHeight()), _uArmor.at(selectArmorNum).image->getWidth(), _uArmor.at(selectArmorNum).image->getHeight());
					}
					
					isSelectArmor = true;
					_uArmor.at(i).itemRc = RectMakeCenter(WINSIZEX / 4, WINSIZEY / 2 + 100, _uArmor.at(i).image->getWidth(), _uArmor.at(i).image->getHeight());
					selectArmorNum = i;
					onDefNum = 0;
					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
					break;
				}
				else {
					isClick = false;
					_uArmor.at(i).itemRc = RectMakeCenter(WINSIZEX / 2 + _uArmor.at(i).image->getWidth() / 2, 200 + (i * _uArmor.at(i).image->getHeight()), _uArmor.at(i).image->getWidth(), _uArmor.at(i).image->getHeight());
					unitTotalAtt();
					unitTotalDef();
					unitTotalHp();
				}
			}
		}
	}
}

void inventory::unitTotalHp()
{
	unitHp = unitDef + 0;//유닛 체력 
}

void inventory::unitTotalAtt()
{
	if (isSelectPistol == true) {
		pistolAtt =_uPistol.at(selectPistolWeaponNum).att;
	}
	else {
		pistolAtt = 0;
	}

	if (isSelectRifle == true) {
		rifleAtt = _uRifle.at(selectRifleWeaponNum).att;
	}
	else {
		rifleAtt = 0;
	}
	
	if (isSelectShield == true) {
		shieldAtt = _uShield.at(selectShieldWeaponNum).att;
	}
	else {
		shieldAtt = 0;
	}
	if (isSelectArmor == true) {
		armorAtt = _uArmor.at(selectArmorNum).att;
	}
	else {
		armorAtt = 0;
	}

	unitAtt = armorAtt + shieldAtt + rifleAtt + pistolAtt + 0;
}

void inventory::unitTotalDef()
{
	if (isSelectPistol == true) {
		pistolDef = _uPistol.at(selectPistolWeaponNum).def;//유닛 공격력
	}
	else {
		pistolDef = 0;
	}
	if (isSelectRifle == true) {
		rifleDef = _uRifle.at(selectRifleWeaponNum).def;
	}
	else {
		rifleDef = 0;
	}
	if (isSelectShield == true) {
		shieldDef = _uShield.at(selectShieldWeaponNum).def;
	}
	else {
		shieldDef = 0;
	}
	if (isSelectArmor == true) {
		armorDef = _uArmor.at(selectArmorNum).def;
	}
	else {
		armorDef = 0; 
	}
	unitDef = armorDef + shieldDef + rifleDef + pistolDef+ 0;

}

void inventory::unitAnimation()
{
	if (isSelectPistol == true) {
		count++;
		//총기 관련 조건
		IMAGEMANAGER->findImage("pistolUnit")->setFrameY(8);
		if (count % 10 == 0)
		{
			index++;
			if (index > 15)
			{
				index = 0;
			}
			IMAGEMANAGER->findImage("pistolUnit")->setFrameX(index);
		}
	}
	if (isSelectRifle == true) { 
		count++;
		//총기 관련 조건
		IMAGEMANAGER->findImage("rifleUnit")->setFrameY(11);
		if (count % 10 == 0)
		{
			index++;
			if (index > 15)
			{
				index = 0;
			}
			IMAGEMANAGER->findImage("rifleUnit")->setFrameX(index);
		}
	}
	if (isSelectShield == true) {
		count++;
		//총기 관련 조건
		IMAGEMANAGER->findImage("shieldUnit")->setFrameY(10);
		if (count % 10 == 0)
		{
			index++;
			if (index > 15)
			{
				index = 0;
			}
			IMAGEMANAGER->findImage("shieldUnit")->setFrameX(index);
		}
	}
	
}  