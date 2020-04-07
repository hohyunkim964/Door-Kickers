#include "stdafx.h"
#include "manager.h"




manager::manager()
{
}


manager::~manager()
{
}

HRESULT manager::init()
{
	player = new unitSelect;
	enemyPlayer = new enemyManager;
	player->init();
	enemyPlayer->init();
	countNum = 0;
	isDead = false;
	isFinish = false;
	SOUNDMANAGER->addSound("AK1", "sound/AK47_FIRE.mp3", false, false);
	SOUNDMANAGER->addSound("AK2", "sound/AK47_FIRE.mp3", false, false);
	SOUNDMANAGER->addSound("AK3", "sound/AK47_FIRE.mp3", false, false);
	SOUNDMANAGER->addSound("AK4", "sound/AK47_FIRE.mp3", false, false);
	SOUNDMANAGER->addSound("AK5", "sound/AK47_FIRE.mp3", false, false);
	SOUNDMANAGER->addSound("pistol", "sound/pistol.mp3", false, false);
	SOUNDMANAGER->addSound("rifle", "sound/rifle.mp3", false, false);
	SOUNDMANAGER->addSound("shield", "sound/shield.mp3", false, false);
	sound = 1.0f;
	
	return S_OK;
}

void manager::release()
{
	SAFE_DELETE(enemyPlayer);
	SAFE_DELETE(player);
}

void manager::update()
{	
	if (enemyPlayer->getEnemyVector().size() > 0) {
		enemyPlayer->update();
		player->update();
		enemyFind();
		playerFind();
	}
	if (enemyPlayer->getEnemyVector().size() <= 0 && player->getHp() > 0) {
		isFinish = true;
	}
}

void manager::render()
{
	//PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	player->render();
	enemyPlayer->render();
	
}

void manager::find()
{

}

void manager::enemyFind()
{	
		for (int i = 0; i < enemyPlayer->getEnemyVector().size(); i++) {
			if (isCrash(enemyPlayer->getEnemyVector().at(i)->getCenter(), enemyPlayer->getEnemyVector().at(i)->getLeft(), enemyPlayer->getEnemyVector().at(i)->getRight(), player->getCenter())) {
				enemyPlayer->getEnemyVector().at(i)->setWait(false);
				enemyPlayer->getEnemyVector().at(i)->setAtt(true);
				enemyPlayer->getEnemyVector().at(i)->setIsCollsion(true);
				playerCollsion = enemyPlayer->getEnemyVector().at(i)->getIsCollsion();
				enemyCountNum++; //초당으로 변경
				if (enemyCountNum % 5 == 0) {
					if (enemyPlayer->getEnemyVector().at(i)->getReload() == false && player->getHp() >0 && enemyPlayer->getEnemyVector().at(i)->getHp() > 0) {
						switch (i)
						{
						case 0:
							SOUNDMANAGER->play("AK1", sound);
							break;
						case 1:
							SOUNDMANAGER->play("AK2", sound);
							break;
						case 2:
							SOUNDMANAGER->play("AK3", sound);
							break;
						case 3:
							SOUNDMANAGER->play("AK4", sound);
							break;
						case 4:
							SOUNDMANAGER->play("AK5", sound);
							break;
						}						
						playerHP = player->getHp() - enemyPlayer->getEnemyVector().at(i)->getAtt();
						player->setHp(playerHP);
					}
					else {
						switch (i)
						{
						case 0:
							SOUNDMANAGER->stop("AK1");
							break;
						case 1:
							SOUNDMANAGER->stop("AK2");
							break;
						case 2:
							SOUNDMANAGER->stop("AK3");
							break;
						case 3:
							SOUNDMANAGER->stop("AK4");
							break;
						case 4:
							SOUNDMANAGER->stop("AK5");
							break;
						}
					}
					if (player->getHp() <= 0) {
						isDead = true;
					}
					enemyCountNum = 0;
				}
				
			}
			else {
				enemyPlayer->getEnemyVector().at(i)->setWait(true);
				enemyPlayer->getEnemyVector().at(i)->setAtt(false);
				enemyPlayer->getEnemyVector().at(i)->setIsCollsion(false);
				playerCollsion = enemyPlayer->getEnemyVector().at(i)->getIsCollsion();
			}
		}
	
}

void manager::playerFind()
{
	for (int i = 0; i < enemyPlayer->getEnemyVector().size(); i++) {
		
		if (isCrash(player->getCenter(), player->getRight(), player->getLeft(), enemyPlayer->getEnemyVector().at(i)->getCenter())) {
			if (player->getIsMove() == true) {
				player->setIsMove(false);
				if (enemyPlayer->getEnemyVector().at(i)->getHp() <= 0) {
					player->setIsMove(true);
				}
			}
			player->setIsAttack(true);
			player->setIsWait(false);
			countNum++;
			if (player->getPistol() == true) {
				if (countNum % 10 == 0) {
					if (player->getReload() == false && enemyPlayer->getEnemyVector().at(i)->getHp() > 0) {
						SOUNDMANAGER->play("pistol", sound);
						enemyHP = enemyPlayer->getEnemyVector().at(i)->getHp() - player->getAtt();
						enemyPlayer->getEnemyVector().at(i)->setHp(enemyHP);						
					}
					countNum = 0;
				}
			}
			if (player->getRifle() == true) {
				if (countNum % 5 == 0) {
					if (player->getReload() == false && enemyPlayer->getEnemyVector().at(i)->getHp() > 0) {
						SOUNDMANAGER->play("rifle", sound);
						enemyHP = enemyPlayer->getEnemyVector().at(i)->getHp() - player->getAtt();
						enemyPlayer->getEnemyVector().at(i)->setHp(enemyHP);
					}
					countNum = 0;
				}
			}
			if (player->getShield() == true) {
				if (countNum % 10 == 0) {
					if (player->getReload() == false && enemyPlayer->getEnemyVector().at(i)->getHp() > 0) {
						SOUNDMANAGER->play("shield", sound);
						enemyHP = enemyPlayer->getEnemyVector().at(i)->getHp() - player->getAtt();
						enemyPlayer->getEnemyVector().at(i)->setHp(enemyHP);
					}
					countNum = 0;
				}
			}
			
			
		}
		else {
			if (player->getIsMove() == true) {
				player->setIsAttack(false);
				player->setIsWait(false);
			}
			else {
				player->setIsMove(false);
				player->setIsAttack(false);
				player->setIsWait(true);
			}

		}
		
		if (enemyPlayer->getEnemyVector().at(i)->getHp() <= 0) {
			enemyPlayer->getEnemyVector().at(i)->setDead(true);
			count++;
			if (count > 165) {
				vector<enemy*> _temp = enemyPlayer->getEnemyVector();
				_temp.erase(_temp.begin() + i);
				enemyPlayer->setEnemyVector(_temp);
				count = 0;
			}
		}
		
	}

}

int manager::vectorDot(POINT & vec1, POINT vec2)
{
	return vec1.x*vec2.x + vec1.y*vec2.y;
}

void manager::vecCross(POINT & outvec, POINT & invec)
{
	outvec.x = -invec.y;
	outvec.y = invec.x;
}

bool manager::isCrash(POINT & x, POINT & y, POINT & z, POINT & objectPos)
{
	vec[0].x = z.x - x.x;
	vec[0].y = z.y - x.y;
	vec[1].x = y.x - x.x;
	vec[1].y = y.y - x.y;
	vec[2].x = objectPos.x - x.x;
	vec[2].y = objectPos.y - x.y;
	vecCross(nVec, vec[0]);
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