#include "stdafx.h"
#include "scene.h"

inventory * scene::inven = new inventory;
int scene::score = 0;				//���� ���� ����
float scene::startTime = 0;			//���� ���� ����
float scene::finishTime = 0;		//���� ���� ����
gameMap * scene::map = new gameMap;
scene::scene()
{
}


scene::~scene()
{
}
