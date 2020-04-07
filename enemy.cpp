#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(POINT center)
{
	

	lifeImg = new image;
	lifeImg->init("images/enemy/적이동.bmp", 2185, 2556, 16, 20, true, RGB(255, 0, 255));
	deadImg = new image;
	deadImg->init("images/enemy/적사망.bmp", 1980, 3608, 11, 20, true, RGB(255, 0, 255));
	enemyRc = RectMakeCenter(center.x, center.y, lifeImg->getFrameWidth(), lifeImg->getFrameHeight());
	direction = Left;
	left.x = center.x;
	right.x = center.x;
	left.y = center.y;
	right.y = center.y;
	angle = PI / 4;
	leng = 250;
	
	hp = 50;
	att = 10;
	isWait = true;
	isAtt = false;
	isReload = false;
	isDead = false;
	centerPoint.x = center.x;
	centerPoint.y = center.y;
	count = 0;
	time = TIMEMANAGER->getWorldTime();
	randNum = RND->getFromIntTo(0, 3);
	isCollsion = false;
	return S_OK;
}

void enemy::release()
{
	
}

void enemy::update()
{
	if (TIMEMANAGER->getWorldTime() - time > 2)
	{
		randNum = RND->getFromIntTo(0, 3);
		time = TIMEMANAGER->getWorldTime();
	}
	if (isDead == false && isCollsion == false) {
		switch (randNum)
		{
		case 0:
			direction = Left;
			break;
		case 1:
			direction = Right;
			break;
		case 2:
			direction = Top;
			break;
		case 3:
			direction = Bottom;
			break;
		}
		settingRightPoint();
		settingLeftPoint();
	}

	
	if (isDead == false) {
		lifeAnimation();
	}
	if (isDead == true) {
		deadAnimation();
	}
}

void enemy::render()
{
	
	if (isDead == false) {
		lifeImg->frameRender(getMemDC(), enemyRc.left, enemyRc.top);
		if (KEYMANAGER->isToggleKey(VK_LCONTROL)) {
			Rectangle(getMemDC(), collisionRc.left, collisionRc.top, collisionRc.right, collisionRc.bottom);
		}
		LineMake(getMemDC(), centerPoint.x, centerPoint.y, left.x, left.y);
		LineMake(getMemDC(), centerPoint.x, centerPoint.y, right.x, right.y);		
	}
	if (isDead == true) {
		deadImg->frameRender(getMemDC(), enemyRc.left, enemyRc.top);
	}
}


void enemy::lifeAnimation()
{
	
	count++;
	if (isWait == true) {
		switch (direction)
		{
		case Left:
			
			lifeImg->setFrameY(5);
			if (count % 15 == 0)
			{
				index++;
				if (index > 11)
				{
					index = 0;
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Right:
			lifeImg->setFrameY(2);
			if (count % 15 == 0)
			{
				index++;
				if (index > 11)
				{
					index = 0;
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Top:
			lifeImg->setFrameY(8);
			if (count % 15 == 0)
			{
				index++;
				if (index > 11)
				{
					index = 0;
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Bottom:
			lifeImg->setFrameY(11);
			if (count % 15 == 0)
			{
				index++;
				if (index > 11)
				{
					index = 0;
				}
			}
			lifeImg->setFrameX(index);
			break;
		}
	}
	if (isAtt == true && isReload == false) {
		switch (direction)
		{
		case Left:
			lifeImg->setFrameY(3);
			if (count % 15 == 0)
			{
				index++;
				if (index > 14)
				{
					index = 0;
					loop += 1;
					if (loop == 2) {
						loop = 0;
						isReload = true;
					}
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Right:
			lifeImg->setFrameY(0);
			if (count % 15 == 0)
			{
				index++;
				if (index > 14)
				{
					index = 0;
					loop += 1;
					if (loop == 2) {
						loop = 0;
						isReload = true;
					}
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Top:
			lifeImg->setFrameY(6);
			if (count % 15 == 0)
			{
				index++;
				if (index > 14)
				{
					index = 0;
					loop += 1;
					if (loop == 2) {
						loop = 0;
						isReload = true;
					}
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Bottom:
			lifeImg->setFrameY(9);
			if (count % 15 == 0)
			{
				index++;
				if (index > 14)
				{
					index = 0;
					loop += 1;
					if (loop == 2) {
						loop = 0;
						isReload = true;
					}
				}
			}
			lifeImg->setFrameX(index);
			break;
		}
	}
	if (isAtt == true && isReload == true) {
		switch (direction)
		{
		case Left:
			lifeImg->setFrameY(4);
			if (count % 15 == 0)
			{
				index++;
				if (index > 15)
				{
					index = 0;
					isReload = false;
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Right:
			lifeImg->setFrameY(1);
			if (count % 15 == 0)
			{
				index++;
				if (index > 15)
				{
					index = 0;
					isReload = false;
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Top:
			lifeImg->setFrameY(7);
			if (count % 15 == 0)
			{
				index++;
				if (index > 15)
				{
					index = 0;
					isReload = false;
				}
			}
			lifeImg->setFrameX(index);
			break;
		case Bottom:
			lifeImg->setFrameY(10);
			if (count % 15 == 0)
			{
				index++;
				if (index > 15)
				{
					index = 0;
					isReload = false;
				}
			}
			lifeImg->setFrameX(index);
			break;
		}
	}
}

void enemy::deadAnimation()
{
	count++;
	switch (direction)
	{
	case Left: //index값 세팅?
		deadImg->setFrameY(9);
		if (count % 10 == 0)
		{
			index++;
			if (index > 8)
			{
				index = 8;
			}
		}
		deadImg->setFrameX(index);
		break;
	case Right:
		deadImg->setFrameY(4);
		if (count % 10 == 0)
		{
			index++;
			if (index > 8)
			{
				index = 8;
			}
		}
		deadImg->setFrameX(index);
		break;
	case Top:
		deadImg->setFrameY(14);
		if (count % 10 == 0)
		{
			index++;
			if (index > 8)
			{
				index = 8;
			}
		}
		deadImg->setFrameX(index);
		break;
	case Bottom:
		deadImg->setFrameY(15);
		if (count % 10 == 0)
		{
			index++;
			if (index > 8)
			{
				index = 8;
			}
		}
		deadImg->setFrameX(index);
		break;

	}
}

void enemy::settingRightPoint()
{
	if (direction == Left) {
		right.x = -cosf(angle)*leng + centerPoint.x;
		right.y = sinf(angle)*leng + centerPoint.y;
	}
	if (direction == Right) {
		right.x = cosf(angle)*leng + centerPoint.x;
		right.y = sinf(angle)*leng + centerPoint.y;
	}
	if (direction == Top) {
		right.x = cosf(angle)*leng + centerPoint.x;
		right.y = -sinf(angle)*leng + centerPoint.y;
	}
	if (direction == Bottom) {
		right.x = cosf(angle)*leng + centerPoint.x;
		right.y = sinf(angle)*leng + centerPoint.y;
	}
}

void enemy::settingLeftPoint()
{
	if (direction == Left) {
		left.x = -cosf(angle)*leng + centerPoint.x;
		left.y = -sinf(angle)*leng + centerPoint.y;
	}
	if (direction == Right) {
		left.x = cosf(angle)*leng + centerPoint.x;
		left.y = -sinf(angle)*leng + centerPoint.y;
	}
	if (direction == Top) {
		left.x = -cosf(angle)*leng + centerPoint.x;
		left.y = -sinf(angle)*leng + centerPoint.y;
	}
	if (direction == Bottom) {
		left.x = -cosf(angle)*leng + centerPoint.x;
		left.y = sinf(angle)*leng + centerPoint.y;
	}
}
