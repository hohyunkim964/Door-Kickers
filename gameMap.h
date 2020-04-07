#pragma once
#include "gameNode.h"
#include "maptool.h"
class gameMap : public gameNode
{
private:
	maptool* _map;
	DWORD _attribute[TILEX* TILEY];
	tagTile _tiles[TILEX* TILEY];

	HANDLE file;
	DWORD read;
	RECT _rc;
	int _pos[2];
public:
	gameMap();
	~gameMap();
	HRESULT init();
	void release();
	void update();
	void load();
	void render();
	DWORD* getAttribute() { return _attribute; }
	tagTile* getMap() { return _tiles; }
	int getPosFirst() { return _pos[0]; }
	int getPosSecond() { return _pos[1]; }
	
};

