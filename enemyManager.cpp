#include "stdafx.h"
#include "enemyManager.h"


enemyManager::enemyManager()
{

}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{		
	enemyNum = 1;
	randnumX = 0;
	randnumY = 0;
	setMinion();

	return S_OK;
}

void enemyManager::release()
{
	
}

void enemyManager::update()
{
	_viEnemy = _vEnemy.begin();
	for (_viEnemy; _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->update();
	}
}


void enemyManager::render()
{
	_viEnemy = _vEnemy.begin();
	for (_viEnemy; _viEnemy != _vEnemy.end(); ++_viEnemy)
	{
		(*_viEnemy)->render();
	}

	
}

void enemyManager::setMinion()
{
	for (int j = 0; j < enemyNum; j++)
	{
		enemy* Enemy;
		Enemy = new enemy;
		/*randnumY = RND->getFromIntTo(100, WINSIZEY - 100);
		randnumX = RND->getFromIntTo(100, WINSIZEX - 100);*/
		Enemy->init(PointMake(WINSIZEX/2 + 200, 200));
		/*if (j == 0) {
			Enemy->init(PointMake(300,150));
		}		
		else {
			Enemy->init(PointMake(0, 0));
		}*/

		_vEnemy.push_back(Enemy);
	}
}
