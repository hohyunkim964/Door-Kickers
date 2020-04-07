#include "stdafx.h"
#include "Unit.h"


Unit::Unit ()
{
}


Unit::~Unit()
{
}

HRESULT Unit::init()
{

	rcCol = RectMakeCenter(WINSIZEX / 2 , WINSIZEY/2, 100, 100); //장애물 렉트(맵툴 화면에서의 충돌 관련 비트연산자 비교-> 맵툴에서의 위치 이동)
	cx = WINSIZEX/2-200; //캐릭터 위치 좌표(x축)
	cy = WINSIZEY/2 ; //캐릭터 위치 좌표(y축)
	IMAGEMANAGER->addFrameImage("unit", "images/unit/swat_pistol.bmp", 1920, 1528, 16, 12, true, RGB(255, 0, 255));
	//라이플 이미지 추가
	rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
	
	isMove = false;
	isXLeft = false;
	isXRight = false;
	isYUP = false;
	isYDOWN = false;

	isUp = false;
	isDown = false;
	isLeft = false;
	isRight = true;
	isFirst = true;
	isLoop = false;
	px = 1;
	py = 1;
	angle = PI / 4;
	leng = 300;	
	pointPos.x = cx;
	pointPos.y = cy;
	firstEnd.x = cx;
	secondEnd.x = cx;
	firstEnd.y = cy;
	secondEnd.y = cy;
	
	objectPos.x = WINSIZEX / 2; //장애물 x축 중점 좌표
	objectPos.y = WINSIZEY / 2; //장애물 y축 중점 좌표
	
	
	att = 20;
	return S_OK;
}

void Unit::release()
{
}

void Unit::update()
{
	
	RECT temp;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isMove = true;
		isFirst = false;
		x = m_ptMouse.x;
		y = m_ptMouse.y;
		if (x > cx) {
			sx = x - cx;
		}
		else {
			sx = cx - x;
		}
		if (y > cy) {
			sy = y - cy;
		}
		else {
			sy = cy - y;
		}

		if (y > cy) {
			isYUP = true;
			isYDOWN = false;
		}
		if (y < cy) {
			isYUP = false;
			isYDOWN = true;
		}
		if (x > cx) {
			isXLeft = false;
			isXRight = true;
		}
		if (x < cx) {
			isXLeft = true;
			isXRight = false;
		}

	}
	if (isMove == true) {
		if (sx >= sy) {
			if (x > cx + 1) {
				if (IntersectRect(&temp, &rc, &rcCol)) { //장애물 충돌시
					cx -= px;

					if (isYUP == true) {
						if (y + 100 > cy) {
							cy -= py;
							isUp = true;
							isDown = false;
							isLeft = false;
							isRight = false;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = -cosf(angle)*leng + pointPos.x;
							firstEnd.y = -sinf(angle)*leng + pointPos.y;
							secondEnd.x = cosf(angle)*leng + pointPos.x;
							secondEnd.y = -sinf(angle)*leng + pointPos.y;

						}

					}
					if (isYDOWN == true) {
						if (y - 100 < cy) {
							cy += py;
							isUp = false;
							isDown = true;
							isLeft = false;
							isRight = false;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = -cosf(angle)*leng + pointPos.x;
							firstEnd.y = sinf(angle)*leng + pointPos.y;
							secondEnd.x = cosf(angle)*leng + pointPos.x;
							secondEnd.y = sinf(angle)*leng + pointPos.y;
						}
					}
				}
				else {
					isUp = false;
					isDown = false;
					isLeft = false;
					isRight = true;
					pointPos.x = cx;
					pointPos.y = cy;
					firstEnd.x = cosf(angle)*leng + pointPos.x;
					firstEnd.y = sinf(angle)*leng + pointPos.y;
					secondEnd.x = cosf(angle)*leng + pointPos.x;
					secondEnd.y = -sinf(angle)*leng + pointPos.y;
				}
					cx += px;
					rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
			}
			else if (x < cx - 1) {
				if (IntersectRect(&temp, &rc, &rcCol)) { //장애물 충돌시
					cx += px;
					if (isYUP == true) {
						if (y + (rcCol.bottom - rcCol.top) > cy) {
							cy += py;
							isUp = false;
							isDown = true;
							isLeft = false;
							isRight = false;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = -cosf(angle)*leng + pointPos.x;
							firstEnd.y = sinf(angle)*leng + pointPos.y;
							secondEnd.x = cosf(angle)*leng + pointPos.x;
							secondEnd.y = sinf(angle)*leng + pointPos.y;
						}
					}
					if (isYDOWN == true) {
						if (y - (rcCol.bottom - rcCol.top) < cy) {
							cy -= py;
							isUp = true;
							isDown = false;
							isLeft = false;
							isRight = false;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = -cosf(angle)*leng + pointPos.x;
							firstEnd.y = -sinf(angle)*leng + pointPos.y;
							secondEnd.x = cosf(angle)*leng + pointPos.x;
							secondEnd.y = -sinf(angle)*leng + pointPos.y;
						}
					}
				}
				else {
					isUp = false;
					isDown = false;
					isLeft = true;
					isRight = false;
					pointPos.x = cx;
					pointPos.y = cy;
					firstEnd.x = -cosf(angle)*leng + pointPos.x;
					firstEnd.y = sinf(angle)*leng + pointPos.y;
					secondEnd.x = -cosf(angle)*leng + pointPos.x;
					secondEnd.y = -sinf(angle)*leng + pointPos.y;
				}
					cx -= px;
					rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
				}
			else {
				x = cx;
				rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight()); //내릴때 충돌 처리 관련
				if (y > cy + 1) {
					if (IntersectRect(&temp, &rc, &rcCol)) {
						cy -= py;
						if (isXLeft == true) {
							if (x - (rcCol.right - rcCol.left) < cx) {
								cx -= px;
								isUp = false;
								isDown = false;
								isLeft = true;
								isRight = false;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = -cosf(angle)*leng + pointPos.x;
								firstEnd.y = sinf(angle)*leng + pointPos.y;
								secondEnd.x = -cosf(angle)*leng + pointPos.x;
								secondEnd.y = -sinf(angle)*leng + pointPos.y;
							}
						}
						if (isXRight == true) {
							if (x + (rcCol.right - rcCol.left) > cx) {
								cx += px;
								isUp = false;
								isDown = false;
								isLeft = false;
								isRight = true;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = cosf(angle)*leng + pointPos.x;
								firstEnd.y = sinf(angle)*leng + pointPos.y;
								secondEnd.x = cosf(angle)*leng + pointPos.x;
								secondEnd.y = -sinf(angle)*leng + pointPos.y;
							}
						}
					}
					else {
						isUp = false;
						isDown = true;
						isLeft = false;
						isRight = false;
						pointPos.x = cx;
						pointPos.y = cy;
						firstEnd.x = -cosf(angle)*leng + pointPos.x;
						firstEnd.y = sinf(angle)*leng + pointPos.y;
						secondEnd.x = cosf(angle)*leng + pointPos.x;
						secondEnd.y = sinf(angle)*leng + pointPos.y;
					}
						cy += py;
						rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());						
				}
				else if (y < cy - 1) {
					if (IntersectRect(&temp, &rc, &rcCol)) {
						cy += py;
						if (isXLeft == true) {
							if (x - (rcCol.right - rcCol.left) < cx) {
								cx -= px;
								isUp = false;
								isDown = false;
								isLeft = true;
								isRight = false;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = -cosf(angle)*leng + pointPos.x;
								firstEnd.y = sinf(angle)*leng + pointPos.y;
								secondEnd.x = -cosf(angle)*leng + pointPos.x;
								secondEnd.y = -sinf(angle)*leng + pointPos.y;
							}
						}
						if (isXRight == true) {
							if (x + (rcCol.right - rcCol.left) > cx) {
								cx += px;
								isUp = false;
								isDown = false;
								isLeft = false;
								isRight = true;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = cosf(angle)*leng + pointPos.x;
								firstEnd.y = sinf(angle)*leng + pointPos.y;
								secondEnd.x = cosf(angle)*leng + pointPos.x;
								secondEnd.y = -sinf(angle)*leng + pointPos.y;
							}
						}
					}
					else {
						isUp = true;
						isDown = false;
						isLeft = false;
						isRight = false;
						pointPos.x = cx;
						pointPos.y = cy;
						firstEnd.x = -cosf(angle)*leng + pointPos.x;
						firstEnd.y = -sinf(angle)*leng + pointPos.y;
						secondEnd.x = cosf(angle)*leng + pointPos.x;
						secondEnd.y = -sinf(angle)*leng + pointPos.y;
					}
						cy -= py;
						rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
						
				}
				else {
					cy = y;
					rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
					
				}
					

					isMove = false;
				
			}
		}

		if (sy > sx) {
			if (y > cy + 1) {
				if (IntersectRect(&temp, &rc, &rcCol)) {
					cy -= py;
					if (isXLeft == true) {
						if (x - (rcCol.right - rcCol.left) < cx) {
							cx -= px;
							isUp = false;
							isDown = false;
							isLeft = true;
							isRight = false;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = -cosf(angle)*leng + pointPos.x;
							firstEnd.y = sinf(angle)*leng + pointPos.y;
							secondEnd.x = -cosf(angle)*leng + pointPos.x;
							secondEnd.y = -sinf(angle)*leng + pointPos.y;
						}
					}
					if (isXRight == true) {
						if (x + (rcCol.right - rcCol.left) > cx) {
							cx += px;
							isUp = false;
							isDown = false;
							isLeft = false;
							isRight = true;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = cosf(angle)*leng + pointPos.x;
							firstEnd.y = sinf(angle)*leng + pointPos.y;
							secondEnd.x = cosf(angle)*leng + pointPos.x;
							secondEnd.y = -sinf(angle)*leng + pointPos.y;
						}
					}
				}
				else {
					isUp = false;
					isDown = true;
					isLeft = false;
					isRight = false;
					pointPos.x = cx;
					pointPos.y = cy;
					firstEnd.x = -cosf(angle)*leng + pointPos.x;
					firstEnd.y = sinf(angle)*leng + pointPos.y;
					secondEnd.x = cosf(angle)*leng + pointPos.x;
					secondEnd.y = sinf(angle)*leng + pointPos.y;
				}
				cy += py;
				rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
				
			}
			else if (y < cy - 1) {
				if (IntersectRect(&temp, &rc, &rcCol)) {
					cy += py;
					if (isXLeft == true) {
						if (x - (rcCol.right - rcCol.left) < cx) {
							cx -= px;
							isUp = false;
							isDown = false;
							isLeft = true;
							isRight = false;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = -cosf(angle)*leng + pointPos.x;
							firstEnd.y = sinf(angle)*leng + pointPos.y;
							secondEnd.x = -cosf(angle)*leng + pointPos.x;
							secondEnd.y = -sinf(angle)*leng + pointPos.y;
						}
					}
					if (isXRight == true) {
						if (x + (rcCol.right - rcCol.left) > cx) {
							cx += px;
							isUp = false;
							isDown = false;
							isLeft = false;
							isRight = true;
							pointPos.x = cx;
							pointPos.y = cy;
							firstEnd.x = cosf(angle)*leng + pointPos.x;
							firstEnd.y = sinf(angle)*leng + pointPos.y;
							secondEnd.x = cosf(angle)*leng + pointPos.x;
							secondEnd.y = -sinf(angle)*leng + pointPos.y;
						}
					}
				}
				else {
					isUp = true;
					isDown = false;
					isLeft = false;
					isRight = false;
					pointPos.x = cx;
					pointPos.y = cy;
					firstEnd.x = -cosf(angle)*leng + pointPos.x;
					firstEnd.y = -sinf(angle)*leng + pointPos.y;
					secondEnd.x = cosf(angle)*leng + pointPos.x;
					secondEnd.y = -sinf(angle)*leng + pointPos.y;
				}
				cy -= py;
				rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
				
			}
			else {
				y = cy;
				rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight()); //내릴때 충돌 처리 관련
				if (x > cx + 1) {
					if (IntersectRect(&temp, &rc, &rcCol)) {
						cx -= px;
						if (isYDOWN == true) {
							if (y - (rcCol.bottom - rcCol.top) < cy) {
								cy -= py;

								isUp = true;
								isDown = false;
								isLeft = false;
								isRight = false;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = -cosf(angle)*leng + pointPos.x;
								firstEnd.y = -sinf(angle)*leng + pointPos.y;
								secondEnd.x = cosf(angle)*leng + pointPos.x;
								secondEnd.y = -sinf(angle)*leng + pointPos.y;
							}
						}
						if (isYUP == true) {
							if (y + (rcCol.bottom - rcCol.top) > cx) {
								cy += py;

								isUp = false;
								isDown = true;
								isLeft = false;
								isRight = false;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = -cosf(angle)*leng + pointPos.x;
								firstEnd.y = sinf(angle)*leng + pointPos.y;
								secondEnd.x = cosf(angle)*leng + pointPos.x;
								secondEnd.y = sinf(angle)*leng + pointPos.y;
							}
						}
					}
					else {
						isUp = false;
						isDown = false;
						isLeft = false;
						isRight = true;
						pointPos.x = cx;
						pointPos.y = cy;
						firstEnd.x = cosf(angle)*leng + pointPos.x;
						firstEnd.y = sinf(angle)*leng + pointPos.y;
						secondEnd.x = cosf(angle)*leng + pointPos.x;
						secondEnd.y = -sinf(angle)*leng + pointPos.y;
					}
					cx += px;
					rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
				
				}
				else if (x < cx - 1) {
					if (IntersectRect(&temp, &rc, &rcCol)) {
						cx += px;
						if (isYDOWN == true) {
							if (y - (rcCol.bottom - rcCol.top) < cy) {
								cy -= py;
								isUp = true;
								isDown = false;
								isLeft = false;
								isRight = false;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = -cosf(angle)*leng + pointPos.x;
								firstEnd.y = -sinf(angle)*leng + pointPos.y;
								secondEnd.x = cosf(angle)*leng + pointPos.x;
								secondEnd.y = -sinf(angle)*leng + pointPos.y;
							}
						}
						if (isYUP == true) {
							if (y + (rcCol.bottom - rcCol.top) > cy) {
								cy += py;
								isUp = false;
								isDown = true;
								isLeft = false;
								isRight = false;
								pointPos.x = cx;
								pointPos.y = cy;
								firstEnd.x = -cosf(angle)*leng + pointPos.x;
								firstEnd.y = sinf(angle)*leng + pointPos.y;
								secondEnd.x = cosf(angle)*leng + pointPos.x;
								secondEnd.y = sinf(angle)*leng + pointPos.y;
							}
						}
					}
					else {
						isUp = false;
						isDown = false;
						isLeft = true;
						isRight = false;
						pointPos.x = cx;
						pointPos.y = cy;
						firstEnd.x = -cosf(angle)*leng + pointPos.x;
						firstEnd.y = sinf(angle)*leng + pointPos.y;
						secondEnd.x = -cosf(angle)*leng + pointPos.x;
						secondEnd.y = -sinf(angle)*leng + pointPos.y;
					}
					cx -= px;
					rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
			
				}
				else {
					cx = x;
					rc = RectMakeCenter(cx, cy, IMAGEMANAGER->findImage("unit")->getFrameWidth(), IMAGEMANAGER->findImage("unit")->getFrameHeight());
				
					isMove = false;
				}
			}
		}
	}
	
	animation();

	//충돌시 모션
	if (isCrash(pointPos,firstEnd,secondEnd,objectPos)) {
		//에너미 클래스의 x와 y좌표
		objectPos.x = 1024;
		objectPos.y = 1024;
	}	
	
}

void Unit::render()
{
	Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	//총기 관련 조건 랜더
	IMAGEMANAGER->findImage("unit")->frameRender(getMemDC(), rc.left, rc.top, IMAGEMANAGER->findImage("unit")->getFrameX(), IMAGEMANAGER->findImage("unit")->getFrameY());
	Rectangle(getMemDC(), rcCol.left, rcCol.top, rcCol.right, rcCol.bottom); //장애물
	LineMake(getMemDC(), pointPos.x, pointPos.y, firstEnd.x, firstEnd.y); //오른쪽 
	LineMake(getMemDC(), pointPos.x, pointPos.y, secondEnd.x, secondEnd.y); //왼쪽
	LineMake(getMemDC(), firstEnd.x, firstEnd.y, secondEnd.x, secondEnd.y);//삼각형 윗단 즉 경계선
	LineMake(getMemDC(), pointPos.x, pointPos.y, objectPos.x, objectPos.y);
}

void Unit::animation()
{
	if (isMove == true) {
		if (isLoop == false) {
			if (isLeft == true) {
				count++;
				//총기 관련 조건
				IMAGEMANAGER->findImage("unit")->setFrameY(4);
				if (count % 5 == 0)
				{
					index--;
					if (index < 0)
					{
						index = 0;
						isLoop = true;

					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
			if (isRight == true) {
				count++;
				IMAGEMANAGER->findImage("unit")->setFrameY(1);
				if (count % 5 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 15;
						isLoop = true;
					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
			if (isUp == true) {
				count++;
				IMAGEMANAGER->findImage("unit")->setFrameY(7);
				if (count % 5 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 15;
						isLoop = true;
					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
			if (isDown == true) {
				count++;
				IMAGEMANAGER->findImage("unit")->setFrameY(10);
				if (count % 5 == 0)
				{
					index++;
					if (index > 15)
					{
						index = 15;
						isLoop = true;
					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
		}
		if (isLoop == true) {
			if (isLeft == true) {
				count++;
				IMAGEMANAGER->findImage("unit")->setFrameY(5);
				if (count % 5 == 0)
				{
					index--;
					if (index < 1)
					{
						index = 15;
					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
			if (isRight == true) {
				count++;
				IMAGEMANAGER->findImage("unit")->setFrameY(2);
				if (count % 5 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;

					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
			if (isUp == true) {
				count++;
				IMAGEMANAGER->findImage("unit")->setFrameY(6);
				if (count % 5 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;

					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
			if (isDown == true) {
				count++;
				IMAGEMANAGER->findImage("unit")->setFrameY(11);
				if (count % 5 == 0)
				{
					index++;
					if (index > 14)
					{
						index = 0;
					}
					IMAGEMANAGER->findImage("unit")->setFrameX(index);
				}
			}
		}

	}
	else {
		isLoop = false;
		if (isLeft == true) {
			IMAGEMANAGER->findImage("unit")->setFrameY(4);
			IMAGEMANAGER->findImage("unit")->setFrameX(15);

		}
		if (isRight == true) {
			IMAGEMANAGER->findImage("unit")->setFrameY(1);
			IMAGEMANAGER->findImage("unit")->setFrameX(0);

		}
		if (isDown == true) {
			IMAGEMANAGER->findImage("unit")->setFrameY(10);
			IMAGEMANAGER->findImage("unit")->setFrameX(0);

		}
		if (isUp == true) {
			IMAGEMANAGER->findImage("unit")->setFrameY(7);
			IMAGEMANAGER->findImage("unit")->setFrameX(0);

		}
	}
}

int Unit::vectorDot(POINT & vec1, POINT vec2)
{
	return vec1.x*vec2.x + vec1.y*vec2.y;
}

void Unit::vecCross(POINT & outvec, POINT & invec)
{
	outvec.x = -invec.y;
	outvec.y = invec.x;
}

bool Unit::isCrash(POINT &x,POINT &y ,POINT &z, POINT &objectPos)
{
	vec[0].x = z.x - x.x;
	vec[0].y = z.y - x.y;
	vec[1].x = y.x - x.x;
	vec[1].y = y.y - x.y;
	vec[2].x = objectPos.x - x.x;
	vec[2].y = objectPos.y - x.y;
	vecCross(nVec,vec[0]);
	a = vectorDot(nVec, vec[1]);
	b = vectorDot(nVec, vec[2]);
	if (a*b <= 0) 
		return false; 

	vec[0].x = x.x - y.x;
	vec[0].y = x.y - y.y;
	vec[1].x = z.x - y.x;
	vec[1].y = z.y - y.y;
	vec[2].x = objectPos.x - y.x;
	vec[2].y = objectPos.y - y.y;
	vecCross(nVec, vec[0]);
	a = vectorDot(nVec, vec[1]);
	b = vectorDot(nVec, vec[2]);
	if (a*b <= 0) 
		return false;
	   
	vec[0].x = y.x - z.x;
	vec[0].y = y.y - z.y;
	vec[1].x = x.x - z.x;
	vec[1].y = x.y - z.y;
	vec[2].x = objectPos.x - z.x;
	vec[2].y = objectPos.y - z.y;
	vecCross(nVec, vec[0]);
	a = vectorDot(nVec, vec[1]);
	b = vectorDot(nVec, vec[2]);
	if (a*b <= 0)
		return false;

	return true;
}

void Unit::hpLost()
{
	time++;
	if (hp <= 0) {
		isDead = true;
	}
	else {
		isDead = false;
		if (time % 120 == 0) { //40배수
			hp = hp - 10; //enemy클래스에서 공격력 가져오기
		}
	}
}