#include "stdafx.h"
#include "gameMap.h"

gameMap::gameMap()
{
}

gameMap::~gameMap()
{
}

HRESULT gameMap::init()
{
	load();
	IMAGEMANAGER->addFrameImage("tilemap", "images/maptool/tile.bmp", 256, 256, SAMPLETERTILEX, SAMPLETERTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("objectmap", "images/maptool/오브젝트.bmp", 512, 960, SAMPLEOBJTILEX, SAMPLEOBJTILEY, true, RGB(255, 0, 255));
	return S_OK;
}

void gameMap::release()
{
}

void gameMap::update()
{
}

void gameMap::load()
{
	file = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _tiles, sizeof(tagTile)*(TILEY*TILEX), &read, NULL);

	memset(_attribute, 0, sizeof(DWORD)*TILEX*TILEY);

	for (int i = 0; i < TILEX*TILEY; i++)
	{
		if (_tiles[i].terrain == TR_WALL)		 //벽
		{
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].terrain == TR_WATER) {	//물
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].terrain == TR_NULL) {		//지형이 없을 때
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_RAND) {		 //기타 오브젝트 (파편 제외)
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_CAR) {			 //차
			_attribute[i] |= ATTR_UNMOVABLE;
		}
		if (_tiles[i].obj == OBJ_BED) {			//침대 
			_attribute[i] |= ATTR_UNMOVABLE;
		}
	}
}

void gameMap::render()
{
	for (int i = 0; i < TILEX * TILEY; i++) {             //초기 타일 렌더
		if (_tiles[i].terrain == TR_NULL)
		{
			//Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);
		}
		else IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);  //타일 관련 이미지 렌더링
	}
	for (int i = 0; i < TILEX * TILEY; i++)              //초기 오브젝트 랜더
	{
		if (_tiles[i].obj == OBJ_NONE)continue;

		IMAGEMANAGER->frameRender("objectmap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);    //오브젝트 관련 이미지 렌더링

	}

}
