#pragma once
#include "gameNode.h"
#include "maptiles.h"

enum randNum {
	one,two,four,six
};

enum bedNum
{
	small,middle, big
};

enum CTRL
{
	CTRL_DRAW,
	CTRL_ERASER,
	CTRL_INIT,
	CTRL_SAVE,
	CTRL_LOAD,
	CTRL_TERRAINDRAW,
	CTRL_OBJDRAW,
	CTRL_NUM1,
	CTRL_NUM2,
	CTRL_NUM3,
	CTRL_END
};

class maptool :public gameNode
{
private:

	

	HANDLE file;
	DWORD write;
	DWORD read;
	int pos[2];
	tagCurrentTile _currentTile;
	tagTile _tiles[TILEX * TILEY];
	tagSampleTile _sampleTerrainTiles[SAMPLETERTILEX * SAMPLETERTILEY];
	tagSampleTile _sampleOBJTiles[SAMPLEOBJTILEX * SAMPLEOBJTILEY];
	int _ctrlSelect;
	int _viewTile; //�����ʿ� ���� �� Ÿ��
	int _viewTerNum; //���� �ٴ� ����
	int _viewObjNum; //���� �ٴ� ����


	RECT menuRc; //�޴�
	
	bedNum bed;
	randNum random;

	RECT loadRc;
	RECT saveRc;
	RECT initRc;
	RECT objRc;
	RECT terrainRc;
	RECT eraserRc;
	//terrain ����
	RECT floorRc;
	RECT wallRc;
	//object����
	RECT shopRc;
	RECT carRc;
	RECT bedRc;
	RECT randRc;
	RECT flightRc;

	bool isMenu;
	bool isFirst;
	bool isSelect;

	bool isShop;
	bool isBike;

	bool isSetting;

	int frameX;
	int frameY;
	int y;
	int num;
	RECT windowsRc;
public:
	maptool();
	~maptool();

	HRESULT init();
	void release();
	void update();
	void render();

	void maptoolSetup();
	void sampleBook();
	void setMap();
	void setRectMap();

	void save();
	void load();

	TERRAIN terrainSelect(int frameX, int frameY);
	OBJECT objSelect(int frameX, int frameY);

	void hideObj();
	void hideTerrain();
	void UI();
	void hideTerrainUI();
	void hideOBJUI();
	void hideUi();

	

	void isTF();
	
};

