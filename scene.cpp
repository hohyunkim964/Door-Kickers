#include "stdafx.h"
#include "scene.h"

inventory * scene::inven = new inventory;
int scene::score = 0;				//전역 변수 선언
float scene::startTime = 0;			//전역 변수 선언
float scene::finishTime = 0;		//전역 변수 선언
gameMap * scene::map = new gameMap;
scene::scene()
{
}


scene::~scene()
{
}
