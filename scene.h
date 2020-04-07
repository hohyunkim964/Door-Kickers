#pragma once
#include "gameNode.h"
#include "inventory.h"
#include "gameMap.h"
class scene : public gameNode
{
protected:
	static inventory* inven;
	static 	gameMap* map;
	static int score;
	static float startTime;
	static float finishTime;
public:
	scene();
	~scene();
};

