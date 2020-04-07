#include "stdafx.h"
#include "unitSelect.h"



unitSelect::unitSelect()
{
}


unitSelect::~unitSelect()
{
}

HRESULT unitSelect::init()
{

	map = new gameMap;
	map->init();


	unitAtt = 10;
	unitDef = 10;
	unitHp = 50;

	unitRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY, 50, 50);

	pistolImg = IMAGEMANAGER->addFrameImage("pistolUnit", "images/unit/swat_pistol.bmp", 1536, 1528, 16, 12, true, RGB(255, 0, 255));
	rifleImg = IMAGEMANAGER->addFrameImage("rifleUnit", "images/unit/swat_rifle.bmp", 1536, 1528, 16, 12, true, RGB(255, 0, 255));
	shieldImg = IMAGEMANAGER->addFrameImage("shieldUnit", "images/unit/swat_shield.bmp", 1536, 1528, 16, 12, true, RGB(255, 0, 255));
	startPoint = IMAGEMANAGER->addImage("position", "images/UI/postion.bmp", 76, 76, true, RGB(255, 0, 255));

	angle = PI / 4;
	shield = false;
	rifle = false;

	pistol = false;

	center.x = 48;
	center.y = WINSIZEY / 2;
	dir = isRight;
	selectUnit();
	selectUnitRange();
	startPositionRect = RectMakeCenter(center.x, center.y, startPoint->getWidth(), startPoint->getHeight());

	left = center;
	right = center;
	destinationX = center.x;
	destinationY = center.y;
	index = 0;
	count = 0;

	isAttack = false;
	isMove = false;
	isWait = true;
	isReload = false;
	isDead = false;
	isLoop = false;
	isCollsion = false;

	

	return S_OK;
}

void unitSelect::release()
{
	
}

void unitSelect::update()
{
	
	
	if (isDead == false) {	
		
			move();
			
			
			collisionRange();
			unitLifeAnimation();		

	}
	
}

void unitSelect::render()
{
	map->render();
	//Rectangle(getMemDC(), unitRc.left, unitRc.top, unitRc.right, unitRc.bottom);
	startPoint->render(getMemDC(), startPositionRect.left, startPositionRect.top);
	if (isDead == false) {
		if (pistol == true) {
			pistolImg->frameRender(getMemDC(), unitRc.left, unitRc.top, pistolImg->getFrameX(), pistolImg->getFrameY());
		}
		if (rifle == true) {
			rifleImg->frameRender(getMemDC(), unitRc.left, unitRc.top, rifleImg->getFrameX(), rifleImg->getFrameY());
		}
		if (shield == true) {
			shieldImg->frameRender(getMemDC(), unitRc.left, unitRc.top, shieldImg->getFrameX(), shieldImg->getFrameY());
		}

	}
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
	//	Rectangle(getMemDC(), collisionRangeRc.left, collisionRangeRc.top, collisionRangeRc.right, collisionRangeRc.bottom);

		LineMake(getMemDC(), center.x, center.y, right.x, right.y);
		LineMake(getMemDC(), center.x, center.y, left.x, left.y);
	}
}

void unitSelect::selectUnit()
{
	

	if (inven->selectPistol() == true) {
		pistol = true;
		rifle = false;
		shield = false;

		unitRc = RectMakeCenter(center.x, center.y, 96, 84);

		unit = IMAGEMANAGER->findImage("pistolUnit");
	}
	if (inven->selectRifle() == true) {
		pistol = false;
		rifle = true;
		shield = false;

		unitRc = RectMakeCenter(center.x, center.y, 96, 84);

		unit = IMAGEMANAGER->findImage("rifleUnit");
	}
	if (inven->selectShiled() == true) {
		pistol = false;
		rifle = false;
		shield = true;

		unitRc = RectMakeCenter(center.x, center.y, 96, 84);

		unit = IMAGEMANAGER->findImage("shieldUnit");
	}


}

void unitSelect::selectUnitRange()
{
	if (pistol == true) {
		range = 150;		
	}else if (shield == true) {
		range = 200;
	}
	else if (rifle == true) {
		range = 250;
	}
}

void unitSelect::viewRightRange()
{	
	if (dir == isLeft) {
		right.x = -cosf(angle)*range + center.x;
		right.y = sinf(angle)*range + center.y;
	}
	if (dir == isRight) {
		right.x = cosf(angle)*range + center.x;
		right.y = sinf(angle)*range + center.y;
	}
	if (dir == isTop) {
		right.x = cosf(angle)*range + center.x;
		right.y = -sinf(angle)*range + center.y;
	}
	if (dir == isBottom) {
		right.x = cosf(angle)*range + center.x;
		right.y = sinf(angle)*range + center.y;
	}
}

void unitSelect::viewLeftRange()
{
	if (dir == isLeft) {
		left.x = -cosf(angle)*range + center.x;
		left.y = -sinf(angle)*range + center.y;
	}
	if (dir == isRight) {
		left.x = cosf(angle)*range + center.x;
		left.y = -sinf(angle)*range + center.y;
	}
	if (dir == isTop) {
		left.x = -cosf(angle)*range + center.x;
		left.y = -sinf(angle)*range + center.y;
	}
	if (dir == isBottom) {
		left.x = -cosf(angle)*range + center.x;
		left.y = sinf(angle)*range + center.y;
	}
}

void unitSelect::move()		
{
	int tileIndex[8];
	rcCollision = unitRc;

	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
		destinationX = m_ptMouse.x;
		destinationY = m_ptMouse.y;
		isMove = true;
	}
	if (isMove == true) {
		
		if (destinationX > center.x) {
			isMove = true;
			isWait = false;
			dir = isRight;
			center.x = center.x + 1;
			unitRc = RectMakeCenter(center.x, center.y, unit->getFrameWidth(), unit->getFrameHeight());
		}
		else if (destinationX < center.x) {
			isMove = true;
			isWait = false;
			dir = isLeft;
			center.x = center.x - 1;
			unitRc = RectMakeCenter(center.x, center.y, unit->getFrameWidth(), unit->getFrameHeight());
		}
		else if (destinationY < center.y) {
			isMove = true;
			isWait = false;
			dir = isTop;
			center.y = center.y - 1;
			unitRc = RectMakeCenter(center.x, center.y, unit->getFrameWidth(), unit->getFrameHeight());
		}
		else if (destinationY > center.y) {
			isMove = true;
			isWait = false;
			dir = isBottom;
			center.y = center.y + 1;
			unitRc = RectMakeCenter(center.x, center.y, unit->getFrameWidth(), unit->getFrameHeight());
		}
		else if(destinationX == center.x && destinationY == center.y) {
			isMove = false;
			isWait = true;
		}
	}
	

	tileX = (rcCollision.left / TILESIZE);  //타일 넘버 지정
	tileY = (rcCollision.top / TILESIZE);   //타일 넘버
	tileX1 = tileX + 1;
	tileY1 = tileY + 1;
	tileX2 = tileX1 + 1;
	tileY2 = tileY1 + 1;
	tileX3 = tileX2 + 1;
	tileY3 = tileY3 + 1;
	switch (dir)
	{
	case isLeft:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)* TILEX;

		tileIndex[2] = tileX + tileY1 * TILEX;
		tileIndex[3] = tileX + (tileY1 + 1)* TILEX;

		tileIndex[4] = tileX + tileY2 * TILEX;
		tileIndex[5] = tileX + (tileY2 + 1)* TILEX;

		tileIndex[6] = tileX + tileY3 * TILEX;
		tileIndex[7] = tileX + (tileY3 + 1)* TILEX;

		break;
	case isRight:
		tileIndex[0] = (tileX + tileY * TILEX) + 3;
		tileIndex[1] = (tileX + (tileY + 1)*TILEX) + 3;

		tileIndex[2] = (tileX + tileY1 * TILEX) + 3;
		tileIndex[3] = (tileX + (tileY1 + 1)*TILEX) + 3;

		tileIndex[4] = (tileX + tileY2 * TILEX) + 3;
		tileIndex[5] = (tileX + (tileY2 + 1)*TILEX) + 3;

		tileIndex[6] = (tileX + tileY3 * TILEX) + 3;
		tileIndex[7] = (tileX + (tileY3 + 1)*TILEX) + 3;

		break;
	case isTop:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + 1 + tileY * TILEX;

		tileIndex[2] = tileX1 + tileY * TILEX;
		tileIndex[3] = tileX1 + (tileY + 1)* TILEX;

		tileIndex[4] = tileX2 + tileY * TILEX;
		tileIndex[5] = tileX2 + (tileY + 1)* TILEX;

		tileIndex[6] = tileX3 + tileY * TILEX;
		tileIndex[7] = tileX3 + (tileY + 1)* TILEX;

		break;
	case isBottom:
		tileIndex[0] = (tileX + tileY * TILEX) + 3 * TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[2] = (tileX1 + tileY * TILEX) + 3 * TILEX;
		tileIndex[3] = (tileX1 + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[4] = (tileX2 + tileY * TILEX) + 3 * TILEX;
		tileIndex[5] = (tileX2 + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[6] = (tileX3 + tileY * TILEX) + 3 * TILEX;
		tileIndex[7] = (tileX3 + 1 + tileY * TILEX) + 3 * TILEX;

		break;

	}


	RECT rc;

	for (int i = 0; i < 6; i++) {
		if (((map->getAttribute()[tileIndex[i]] & ATTR_UNMOVABLE) == ATTR_UNMOVABLE) &&
			IntersectRect(&rc, &map->getMap()[tileIndex[i]].rc, &rcCollision))
		{
			switch (dir)
			{
			case isLeft:
				unitRc.left = map->getMap()[tileIndex[i]].rc.right;
				unitRc.right = unitRc.left + 96;
				center.x = unitRc.left + (unitRc.right - unitRc.left) / 2;
				destinationX = center.x;
				
				isMove = false;
				isWait = true;
				dir = isLeft;
				break;
			case isRight:
				unitRc.right = map->getMap()[tileIndex[i]].rc.left;
				unitRc.left = unitRc.right - 96;
				center.x = unitRc.left + (unitRc.right - unitRc.left) / 2;
				destinationX = center.x;
				destinationY = center.y;
			
				isMove = false;
				isWait = true;
				dir = isRight;
				break;
			case isTop:
				unitRc.top = map->getMap()[tileIndex[i]].rc.bottom;
				unitRc.bottom = unitRc.top + 84;
				center.y = unitRc.top + (unitRc.bottom - unitRc.top) / 2;
				destinationX = center.x;
				destinationY = center.y;
				
				isMove = false;
				isWait = true;
				dir = isTop;
				break;
			case isBottom:
				unitRc.bottom = map->getMap()[tileIndex[i]].rc.top;
				unitRc.top = unitRc.bottom - 84;
				center.y = unitRc.top + (unitRc.bottom - unitRc.top) / 2;
				destinationX = center.x;
				destinationY = center.y;
				
				isMove = false;
				isWait = true;
				dir = isBottom;
				break;
			}
		}
	}




	rcCollision = RectMakeCenter(center.x, center.y, 96, 96);
	unitRc = rcCollision;

}

void unitSelect::unitLifeAnimation()
{
	count++;
	if (pistol == true) {
		if (dir == isLeft) {
			if (isAttack == true) {
				pistolImg->setFrameY(5);
				if (count % 15 == 0)
				{
					index--;
					if (index < 1)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				pistolImg->setFrameY(5);
				if (count % 15 == 0)
				{
					index--;
					if (index < 1)
					{
						index = 15;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				pistolImg->setFrameY(4);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isWait == true) {
				pistolImg->setFrameY(3);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
		if (dir == isRight) {
			if (isAttack == true) {
				pistolImg->setFrameY(2);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				pistolImg->setFrameY(2);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				pistolImg->setFrameY(2);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isWait == true) {
				pistolImg->setFrameY(0);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
		if (dir == isTop) {
			if (isAttack == true) {
				pistolImg->setFrameY(6);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				pistolImg->setFrameY(6);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				pistolImg->setFrameY(7);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isWait == true) {
				pistolImg->setFrameY(8);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
		if (dir == isBottom) {
			if (isAttack == true) {
				pistolImg->setFrameY(11);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				pistolImg->setFrameY(11);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				pistolImg->setFrameY(4);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isWait == true) {
				pistolImg->setFrameY(9);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
	}
	if (rifle == true) {
		if (dir == isLeft) {
			if (isAttack == true) {
				rifleImg->setFrameY(5);
				if (count % 15 == 0)
				{
					index--;
					if (index < 1)
					{
						isReload = true;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isMove == true) {
				rifleImg->setFrameY(5);
				if (count % 15 == 0)
				{
					index--;
					if (index < 1)
					{
						index = 15;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isReload == true) {
				rifleImg->setFrameY(4);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isWait == true) {
				rifleImg->setFrameY(3);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
					}
				}
				rifleImg->setFrameX(index);
			}
		}
		if (dir == isRight) {
			if (isAttack == true) {
				rifleImg->setFrameY(2);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						isReload = true;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isMove == true) {
				rifleImg->setFrameY(2);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isReload == true) {
				rifleImg->setFrameY(1);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
					rifleImg->setFrameX(index);
				}
				if (isWait == true) {
					rifleImg->setFrameY(0);
					if (count % 15 == 0)
					{
						index++;
						if (index > 15)
						{
							index = 0;
						}
					}
					rifleImg->setFrameX(index);
				}
			}
		}
		if (dir == isTop) {
			if (isAttack == true) {
				rifleImg->setFrameY(9);
				rifleImg->setFrameX(1);
			}
			if (isMove == true) {
				rifleImg->setFrameY(9);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isReload == true) {
				rifleImg->setFrameY(10);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isWait == true) {
				rifleImg->setFrameY(11);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				rifleImg->setFrameX(index);
			}
		}
		if (dir == isBottom) {
			if (isAttack == true) {
				rifleImg->setFrameY(8);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						isReload = true;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isMove == true) {
				rifleImg->setFrameY(8);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isReload == true) {
				rifleImg->setFrameY(7);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						isReload = false;
					}
				}
				rifleImg->setFrameX(index);
			}
			if (isWait == true) {
				rifleImg->setFrameY(6);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				rifleImg->setFrameX(index);
			}
		}
	}

	if (shield == true) {
		if (dir == isLeft) {
			if (isAttack == true) {
				shieldImg->setFrameY(3);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				shieldImg->setFrameY(4);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				shieldImg->setFrameY(5);
				if (count % 15 == 0) {
					index--;
					if (index < 1) {
						index = 15;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
			}
			if (isWait == true) {
				shieldImg->setFrameY(3);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
		if (dir == isRight) {
			if (isAttack == true) {
				shieldImg->setFrameY(0);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				shieldImg->setFrameY(0);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				shieldImg->setFrameY(2);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isWait == true) {
				shieldImg->setFrameY(1);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
		if (dir == isTop) {
			if (isAttack == true) {
				shieldImg->setFrameY(9);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				shieldImg->setFrameY(9);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				shieldImg->setFrameY(11);
				if (count % 15 == 0)
				{
					index--;
					if (index < 1)
					{
						index = 15;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isWait == true) {
				shieldImg->setFrameY(10);
				if (count % 15 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 15;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
		if (dir == isBottom) {
			if (isAttack == true) {
				shieldImg->setFrameY(6);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						isReload = true;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isMove == true) {
				shieldImg->setFrameY(6);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isReload == true) {
				shieldImg->setFrameY(8);
				if (count % 15 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
						loop += 1;
						if (loop == 2) {
							isReload = false;
						}
					}
				}
				pistolImg->setFrameX(index);
			}
			if (isWait == true) {
				shieldImg->setFrameY(7);
				if (count % 15 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 0;
					}
				}
				pistolImg->setFrameX(index);
			}
		}
	}

}

void unitSelect::collisionRange()
{
	RECT temp;

	viewRightRange();
	viewLeftRange();

	if (pistol == true) {
		switch (dir)
		{
		case isLeft:
			straight.x = center.x - 106;
			straight.y = center.y;
			collisionRangeRc = RectMake(left.x, left.y, 106, 213);
			break;
		case isRight:
			straight.x = center.x + 106;
			straight.y = center.y;
			collisionRangeRc = RectMake(center.x, left.y, 106, 213);
			break;
		case isTop:
			straight.x = center.x;
			straight.y = center.y - 106;
			collisionRangeRc = RectMake(left.x, left.y, 213, 106);
			break;
		case isBottom:
			straight.x = center.x;
			straight.y = center.y + 106;
			collisionRangeRc = RectMake(left.x, center.y, 213, 106);
			break;
		}
	}
	if (rifle == true) {
		switch (dir)
		{
		case isLeft:
			straight.x = center.x - 176;
			straight.y = center.y;
			collisionRangeRc = RectMake(left.x, left.y, 176, 353);
			break;
		case isRight:
			straight.x = center.x + 176;
			straight.y = center.y;
			collisionRangeRc = RectMake(center.x, left.y, 176, 353);
			break;
		case isTop:
			straight.x = center.x;
			straight.y = center.y - 176;
			collisionRangeRc = RectMake(left.x, left.y, 353, 176);
			break;
		case isBottom:
			straight.x = center.x;
			straight.y = center.y + 176;
			collisionRangeRc = RectMake(left.x, center.y, 353, 176);
			break;		
		}
	}
	if (shield == true) {
		switch (dir)
		{
		case isLeft:
			straight.x = center.x - 141;
			straight.y = center.y;
			collisionRangeRc = RectMake(left.x, left.y, 141,283);
			break;
		case isRight:
			straight.x = center.x + 141;
			straight.y = center.y;
			collisionRangeRc = RectMake(center.x, left.y, 141, 283);
			break;
		case isTop:
			straight.x = center.x;
			straight.y = center.y - 141;
			collisionRangeRc = RectMake(left.x, left.y, 283, 141);
			break;
		case isBottom:
			straight.x = center.x;
			straight.y = center.y + 141;
			collisionRangeRc = RectMake(left.x, center.y, 283, 141);
			break;		
		}
	}

	

	int tileIndex[8];


	tileX = (collisionRangeRc.left / TILESIZE);  //타일 넘버 지정
	tileY = (collisionRangeRc.top / TILESIZE);   //타일 넘버
	tileX1 = tileX + 1;
	tileY1 = tileY + 1;
	tileX2 = tileX1 + 1;
	tileY2 = tileY1 + 1;
	tileX3 = tileX2 + 1;
	tileY3 = tileY3 + 1;
	switch (dir)
	{
	case isLeft:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + (tileY + 1)* TILEX;

		tileIndex[2] = tileX + tileY1 * TILEX;
		tileIndex[3] = tileX + (tileY1 + 1)* TILEX;

		tileIndex[4] = tileX + tileY2 * TILEX;
		tileIndex[5] = tileX + (tileY2 + 1)* TILEX;

		tileIndex[6] = tileX + tileY3 * TILEX;
		tileIndex[7] = tileX + (tileY3 + 1)* TILEX;

		break;
	case isRight:
		tileIndex[0] = (tileX + tileY * TILEX) + 3;
		tileIndex[1] = (tileX + (tileY + 1)*TILEX) + 3;

		tileIndex[2] = (tileX + tileY1 * TILEX) + 3;
		tileIndex[3] = (tileX + (tileY1 + 1)*TILEX) + 3;

		tileIndex[4] = (tileX + tileY2 * TILEX) + 3;
		tileIndex[5] = (tileX + (tileY2 + 1)*TILEX) + 3;

		tileIndex[6] = (tileX + tileY3 * TILEX) + 3;
		tileIndex[7] = (tileX + (tileY3 + 1)*TILEX) + 3;

		break;
	case isTop:
		tileIndex[0] = tileX + tileY * TILEX;
		tileIndex[1] = tileX + 1 + tileY * TILEX;

		tileIndex[2] = tileX1 + tileY * TILEX;
		tileIndex[3] = tileX1 + (tileY + 1)* TILEX;

		tileIndex[4] = tileX2 + tileY * TILEX;
		tileIndex[5] = tileX2 + (tileY + 1)* TILEX;

		tileIndex[6] = tileX3 + tileY * TILEX;
		tileIndex[7] = tileX3 + (tileY + 1)* TILEX;

		break;
	case isBottom:
		tileIndex[0] = (tileX + tileY * TILEX) + 3 * TILEX;
		tileIndex[1] = (tileX + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[2] = (tileX1 + tileY * TILEX) + 3 * TILEX;
		tileIndex[3] = (tileX1 + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[4] = (tileX2 + tileY * TILEX) + 3 * TILEX;
		tileIndex[5] = (tileX2 + 1 + tileY * TILEX) + 3 * TILEX;

		tileIndex[6] = (tileX3 + tileY * TILEX) + 3 * TILEX;
		tileIndex[7] = (tileX3 + 1 + tileY * TILEX) + 3 * TILEX;

		break;

	}
	for (int i = 0; i < 6; i++) {
		if (((map->getMap()[tileIndex[i]].terrain) == TR_WALL) &&
			IntersectRect(&temp, &map->getMap()[tileIndex[i]].rc, &collisionRangeRc))
		{
			switch (dir)
			{
			case isLeft:
				collisionRangeRc.left = map->getMap()[tileIndex[i]].rc.right;
				right.x = collisionRangeRc.left;
				left.x = collisionRangeRc.left;
				break;
			case isRight:
				collisionRangeRc.right = map->getMap()[tileIndex[i]].rc.left;
				right.x = collisionRangeRc.right;
				left.x = collisionRangeRc.right;
				break;
			case isTop:
				collisionRangeRc.top = map->getMap()[tileIndex[i]].rc.bottom;
				right.y = collisionRangeRc.top;
				left.y = collisionRangeRc.top;
				break;
			case isBottom:
				collisionRangeRc.bottom = map->getMap()[tileIndex[i]].rc.top;
				right.y = collisionRangeRc.bottom;
				left.y = collisionRangeRc.bottom;
				break;
			}
		}
	}

}

