#include "stdafx.h"
#include "maptool.h"


maptool::maptool()
{
}


maptool::~maptool()
{
}

HRESULT maptool::init()
{
	IMAGEMANAGER->addFrameImage("tilemap", "images/maptool/tile.bmp", 256, 256, SAMPLETERTILEX, SAMPLETERTILEY, true, RGB(255,0, 255));
	IMAGEMANAGER->addFrameImage("objectmap", "images/maptool/오브젝트.bmp", 512, 960, SAMPLEOBJTILEX, SAMPLEOBJTILEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("button", "images/UI/button.bmp", 200, 55, true, RGB(255, 0, 255));
	maptoolSetup();
	y = WINSIZEY / 2;
	_currentTile.x = 2;
	_currentTile.y = 0;
	_ctrlSelect = 0;
	_viewTerNum = 0;
	isMenu = false;
	isFirst = false;
	menuRc = RectMakeCenter(WINSIZEX,WINSIZEY/2,100,100);
	windowsRc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);
	_viewTile = 0;
	isSelect = false;
	isSetting = false;
	num = 0;
	return S_OK;
}

void maptool::release()
{

}

void maptool::update()
{
	UI();
	setRectMap();

	sampleBook();
	if (PtInRect(&windowsRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
		isSetting = true;
	}
	setMap();
}

void maptool::render()
{
	Rectangle(getMemDC(), windowsRc.left, windowsRc.top, windowsRc.right, windowsRc.bottom);
	FrameRect(getMemDC(), &windowsRc, CreateSolidBrush(RGB(0, 0, 0)));


	frameX = frameY = 0;
	for (int i = 0; i < TILEX * TILEY; i++)              //초기 타일 공백으로 셋팅(속성값은 NULL로)  
	{
		if (_tiles[i].terrain == TR_NULL)
		{
			Rectangle(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].rc.right, _tiles[i].rc.bottom);

		}
		else IMAGEMANAGER->frameRender("tilemap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].terrainFrameX, _tiles[i].terrainFrameY);  //타일 관련 이미지 렌더링

		if (_tiles[i].obj == OBJ_NONE)continue;

		IMAGEMANAGER->frameRender("objectmap", getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top, _tiles[i].objFrameX, _tiles[i].objFrameY);    //오브젝트 관련 이미지 렌더링
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	

	//Rectangle(getMemDC(), menuRc.left, menuRc.top, menuRc.right, menuRc.bottom);
	FillRect(getMemDC(), &menuRc, CreateSolidBrush(RGB(22, 23, 30)));
	if (isFirst == true && isSelect == false) {
		Rectangle(getMemDC(), initRc.left, initRc.top, initRc.right, initRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), initRc.left, initRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 815, 255, "INIT", 4);

		Rectangle(getMemDC(), saveRc.left, saveRc.top, saveRc.right, saveRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), saveRc.left, saveRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 815, 115, "SAVE", 4);

		Rectangle(getMemDC(), loadRc.left, loadRc.top, loadRc.right, loadRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), loadRc.left, loadRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 815, 185, "LOAD", 4);

		Rectangle(getMemDC(), eraserRc.left, eraserRc.top, eraserRc.right, eraserRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), eraserRc.left, eraserRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 805, 325, "ERASER", 6);

		Rectangle(getMemDC(), terrainRc.left, terrainRc.top, terrainRc.right, terrainRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), terrainRc.left, terrainRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 800, 395, "TERRAIN", 7);

		Rectangle(getMemDC(), objRc.left, objRc.top, objRc.right, objRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), objRc.left, objRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 805,465, "OBJECT", 6);
	}	

	if (_viewTile == 1 && isSelect == false) {

		Rectangle(getMemDC(), wallRc.left, wallRc.top, wallRc.right, wallRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), wallRc.left, wallRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 810, 110, "WALL", 4);

		Rectangle(getMemDC(), floorRc.left, floorRc.top, floorRc.right, floorRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), floorRc.left, floorRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 805, 180, "FLOOR", 5);

		if (_viewTerNum == 1) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 8; j++) {
					IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
					frameX++;
					if (frameX > 7) { 
						frameX = 0;
						frameY++;
					}
				}
			}
		}
		if (_viewTerNum == 2) {
			frameY = 6;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 8; j++) {
					IMAGEMANAGER->frameRender("tilemap", getMemDC(), 650 + (j * 45), 300 + (i * 45), frameX, frameY);
					frameX++;
					if (frameX > 7) { 
						frameX = 0;
						frameY++;
					}
				}
			}
		}
	}
	if (_viewTile == 2 && isSelect == false) {
		
		
		Rectangle(getMemDC(), bedRc.left, bedRc.top, bedRc.right, bedRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), bedRc.left, bedRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 820, 180, "BED", 3);

		Rectangle(getMemDC(), carRc.left, carRc.top, carRc.right, carRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), carRc.left, carRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 820, 110, "CAR", 3);

		Rectangle(getMemDC(), randRc.left, randRc.top, randRc.right, randRc.bottom);
		IMAGEMANAGER->findImage("button")->render(getMemDC(), randRc.left, randRc.top);
		SetBkMode(getMemDC(), TRANSPARENT);
		SetTextColor(getMemDC(), RGB(255, 255, 255));
		TextOut(getMemDC(), 815, 250, "OTHERS", 6);
	
		if (_viewObjNum == 1) { //차량
			frameY = 11;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 12; j++) {
					if ((frameY == 11 || frameY == 12) && (frameX < 3)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 30), 450 + (i * 32), frameX, frameY);
					}
					else if((frameY == 11 || frameY == 12)&& (frameX >=3 && frameX < 6)){
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 670 + (j * 30), 450 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 11 || frameY == 12) && (frameX >= 6 && frameX < 9)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 690 + (j * 30), 450 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 11 || frameY == 12) && (frameX >= 9 && frameX < 12)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 375 + (j * 30), 530 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 13 || frameY == 14) && (frameX < 3)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 760 + (j * 30), 465 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 13 || frameY == 14) && (frameX >= 3 && frameX < 6)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 790 + (j * 30), 465 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 13 || frameY == 14) && (frameX >= 6 && frameX < 9)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 470 + (j * 30), 545 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 15 || frameY == 16) && (frameX < 3)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 760 + (j * 30), 475 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 15 || frameY == 16) && (frameX >= 3 && frameX < 6)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 790 + (j * 30), 475 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 16) && (frameX >= 6 && frameX < 9)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 470 + (j * 30), 545 + (i * 32), frameX, frameY);
					}
					frameX++;
					if (frameX > 11) {
						frameX = 0;
						frameY++;
					}
				}
			}
		}
		if (_viewObjNum == 2) { //침대
			frameY = 17; 
			for (int i = 0; i < 6;i++) {
				for (int j = 0; j < 15; j++) {
					if ((frameY == 17 || frameY == 18 || frameY == 19) && (frameX == 0 || frameX == 1)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 30), 450 + (i * 32), frameX, frameY);
					}
					else if (frameX > 1) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 30), 450 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 21 || frameY == 22 || frameY == 20) && (frameX == 0 || frameX == 1)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 30), 450 + (i * 32), frameX, frameY);
					}
					frameX++;
					if (frameX > 14) {
						frameX = 0;
						frameY++;
					}
				}
			}
		}
		
		if (_viewObjNum == 3) { //기타
			frameY = 23;
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 9; j++) {
					if (frameY == 23 && (frameX == 0 || frameX == 1 ||frameX ==2)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 450 + (i * 45), frameX, frameY);
					}
					else if (frameX == 3 && (frameY == 23 || frameY == 24)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 450 + (i * 32), frameX, frameY);
					}
					else if (frameX > 3 && (frameY == 23 || frameY == 24)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 450 + (i * 45), frameX, frameY);
					}
					else if(frameY == 25){
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 450 + (i * 45), frameX, frameY);
					}
					else if ((frameY == 26 || frameY == 27) && frameX == 0) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 495 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 26 || frameY == 27) && (frameX == 1 || frameX == 2)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 675 + (j * 30), 495 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 26 || frameY == 27) && frameX == 3) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 495 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 26 || frameY == 27) && (frameX == 4 || frameX == 5 || frameX == 6)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 730 + (j * 30), 495 + (i * 32), frameX, frameY);
					}
					else if ((frameY == 26 || frameY == 27) && (frameX == 7)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 450 + (i * 45), frameX, frameY);
					}
					else if ((frameY == 28 || frameY == 29) && (frameX == 0 || frameX == 1)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 30), 510 + (i * 32), frameX, frameY);
					}
					else if (frameX == 2 && (frameY == 28 || frameY == 29)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 650 + (j * 45), 450 + (i * 45), frameX, frameY);
					}
					else if ((frameX == 3 || frameX == 4) && (frameY == 29 || frameY == 28)) {
						IMAGEMANAGER->frameRender("objectmap", getMemDC(), 695 + (j * 30), 515 + (i * 32), frameX, frameY);
					}
					frameX++;
					if (frameX > 8) {
						frameX = 0;
						frameY++;
					}
				}
			}
		}
	}
	
	
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		for (int i = 0; i < 10 * 10; i++)
		{
			Rectangle(getMemDC(), _sampleTerrainTiles[i].rcTile.left, _sampleTerrainTiles[i].rcTile.top, _sampleTerrainTiles[i].rcTile.right, _sampleTerrainTiles[i].rcTile.bottom);
			Rectangle(getMemDC(), _sampleOBJTiles[i].rcTile.left, _sampleOBJTiles[i].rcTile.top, _sampleOBJTiles[i].rcTile.right, _sampleOBJTiles[i].rcTile.bottom);

		}
	}
}

void maptool::maptoolSetup()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			SetRect(&_tiles[i*TILEX + j].rc,   //각 타일의 크기별로 RECT 지정
				j*TILESIZE,
				i*TILESIZE,
				j*TILESIZE + TILESIZE,
				i*TILESIZE + TILESIZE);
		}
	}

	//처음 깔려있는 타일
	for (int i = 0; i < TILEX*TILEY; i++)  //초기 타일 전부 0으로 설정
	{
		_tiles[i].terrainFrameX = 0;
		_tiles[i].terrainFrameY = 0;

		_tiles[i].objFrameX = 0;
		_tiles[i].objFrameY = 3;

		_tiles[i].terrain = TR_NULL;
		_tiles[i].obj = OBJ_NONE;

	}

}

void maptool::sampleBook()
{
	isTF();

	if (isSelect == false && isSetting == false) {
		if (_viewTile == 1) {
			if (_viewTerNum == 1 || _viewTerNum == 2 || _viewTerNum == 3) {

				for (int i = 0; i < SAMPLETERTILEX* SAMPLETERTILEY; i++)
				{
					if (PtInRect(&_sampleTerrainTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
					{

						//렉트 실종 처리 관련(hide,hideTerrainUI 및 setRect관련)
						_currentTile.x = _sampleTerrainTiles[i].terrainFrameX;
						_currentTile.y = _sampleTerrainTiles[i].terrainFrameY;
						
						hideUi();

						break;

					}
				}
			}
		}
		if (_viewTile == 2) {
			if (_viewObjNum == 1) {
				for (int i = 0; i < SAMPLEOBJTILEX* SAMPLEOBJTILEY; i++)
				{
					if (isSelect == false) {
						if (PtInRect(&_sampleOBJTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
						{
							if (isBike == false) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;
								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;
								_currentTile.x2 = _sampleOBJTiles[i].objFrameX2;
								_currentTile.y2 = _sampleOBJTiles[i].objFrameY2;
								_currentTile.x3 = _sampleOBJTiles[i].objFrameX3;
								_currentTile.y3 = _sampleOBJTiles[i].objFrameY3;
								_currentTile.x4 = _sampleOBJTiles[i].objFrameX4;
								_currentTile.y4 = _sampleOBJTiles[i].objFrameY4;
								_currentTile.x5 = _sampleOBJTiles[i].objFrameX5;
								_currentTile.y5 = _sampleOBJTiles[i].objFrameY5;
							}
							if (isBike == true) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;
								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;
								_currentTile.x2 = _sampleOBJTiles[i].objFrameX2;
								_currentTile.y2 = _sampleOBJTiles[i].objFrameY2;
							}

							hideUi();

							break;
						}
					}
				}
			}
			if (_viewObjNum == 2) {
				for (int i = 0; i < SAMPLEOBJTILEX* SAMPLEOBJTILEY; i++)
				{
					if (isSelect == false) {
						if (PtInRect(&_sampleOBJTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
						{
							if (bed == small) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;
								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;
							}
							if (bed == middle) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;

								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;

								_currentTile.x2 = _sampleOBJTiles[i].objFrameX2;
								_currentTile.y2 = _sampleOBJTiles[i].objFrameY2;

								_currentTile.x3 = _sampleOBJTiles[i].objFrameX3;
								_currentTile.y3 = _sampleOBJTiles[i].objFrameY3;
							}
							if (bed == big) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;

								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;

								_currentTile.x2 = _sampleOBJTiles[i].objFrameX2;
								_currentTile.y2 = _sampleOBJTiles[i].objFrameY2;

								_currentTile.x3 = _sampleOBJTiles[i].objFrameX3;
								_currentTile.y3 = _sampleOBJTiles[i].objFrameY3;

								_currentTile.x4 = _sampleOBJTiles[i].objFrameX4;
								_currentTile.y4 = _sampleOBJTiles[i].objFrameY4;

								_currentTile.x5 = _sampleOBJTiles[i].objFrameX5;
								_currentTile.y5 = _sampleOBJTiles[i].objFrameY5;
							}
							hideUi();
							break;
						}
					}

				}
			}
			if (_viewObjNum == 3) {
				for (int i = 0; i < SAMPLEOBJTILEX* SAMPLEOBJTILEY; i++)
				{
					if (isSelect == false) {
						if (PtInRect(&_sampleOBJTiles[i].rcTile, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
						{
							if (random == one) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;
							}
							if (random == two) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;
								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;
							}
							if (random == four) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;

								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;

								_currentTile.x2 = _sampleOBJTiles[i].objFrameX2;
								_currentTile.y2 = _sampleOBJTiles[i].objFrameY2;

								_currentTile.x3 = _sampleOBJTiles[i].objFrameX3;
								_currentTile.y3 = _sampleOBJTiles[i].objFrameY3;
							}
							if (random == six) {
								_currentTile.x = _sampleOBJTiles[i].objFrameX;
								_currentTile.y = _sampleOBJTiles[i].objFrameY;

								_currentTile.x1 = _sampleOBJTiles[i].objFrameX1;
								_currentTile.y1 = _sampleOBJTiles[i].objFrameY1;

								_currentTile.x2 = _sampleOBJTiles[i].objFrameX2;
								_currentTile.y2 = _sampleOBJTiles[i].objFrameY2;

								_currentTile.x3 = _sampleOBJTiles[i].objFrameX3;
								_currentTile.y3 = _sampleOBJTiles[i].objFrameY3;

								_currentTile.x4 = _sampleOBJTiles[i].objFrameX4;
								_currentTile.y4 = _sampleOBJTiles[i].objFrameY4;

								_currentTile.x5 = _sampleOBJTiles[i].objFrameX5;
								_currentTile.y5 = _sampleOBJTiles[i].objFrameY5;
							}
							hideUi();
							break;
						}
					}
				}
			}
		}
	}
}

void maptool::setMap()
{
	isTF();	
	
	if(isSelect == true && isSetting == true){
	
		for (int i = 0; i < TILEX * TILEY; i++) {
			if (PtInRect(&_tiles[i].rc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
			{
				if (_ctrlSelect == CTRL_TERRAINDRAW)
				{
					_tiles[i].terrainFrameX = _currentTile.x;
					_tiles[i].terrainFrameY = _currentTile.y;
					_tiles[i].terrain = terrainSelect(_currentTile.x, _currentTile.y);
				}
				if (_ctrlSelect == CTRL_OBJDRAW) {

					if (_viewObjNum == 1) {
						if (isBike == true) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;
							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;
							_tiles[i + 2].objFrameX = _currentTile.x2;
							_tiles[i + 2].objFrameY = _currentTile.y2;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + 2].obj = objSelect(_currentTile.x2, _currentTile.y2);
							//hideUi();
						}
						if (isBike == false) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;
							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;
							_tiles[i + 2].objFrameX = _currentTile.x2;
							_tiles[i + 2].objFrameY = _currentTile.y2;
							_tiles[i + TILEX].objFrameX = _currentTile.x3;
							_tiles[i + TILEX].objFrameY = _currentTile.y3;
							_tiles[i + 1 + TILEX].objFrameX = _currentTile.x4;
							_tiles[i + 1 + TILEX].objFrameY = _currentTile.y4;
							_tiles[i + 2 + TILEX].objFrameX = _currentTile.x5;
							_tiles[i + 2 + TILEX].objFrameY = _currentTile.y5;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + 2].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x3, _currentTile.y3);
							_tiles[i + 1 + TILEX].obj = objSelect(_currentTile.x4, _currentTile.y4);
							_tiles[i + 2 + TILEX].obj = objSelect(_currentTile.x5, _currentTile.y5);
						}
					}

					if (_viewObjNum == 2) {
						if (bed == small) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;
							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
						}
						if (bed == middle) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + TILEX].objFrameX = _currentTile.x2;
							_tiles[i + TILEX].objFrameY = _currentTile.y2;

							_tiles[i + TILEX + 1].objFrameX = _currentTile.x3;
							_tiles[i + TILEX + 1].objFrameY = _currentTile.y3;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + TILEX + 1].obj = objSelect(_currentTile.x3, _currentTile.y3);
						}
						if (bed == big) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + TILEX].objFrameX = _currentTile.x2;
							_tiles[i + TILEX].objFrameY = _currentTile.y2;

							_tiles[i + TILEX + 1].objFrameX = _currentTile.x3;
							_tiles[i + TILEX + 1].objFrameY = _currentTile.y3;

							_tiles[i + 2 * (TILEX)].objFrameX = _currentTile.x4;
							_tiles[i + 2 * (TILEX)].objFrameY = _currentTile.y4;

							_tiles[i + 2 * (TILEX)+1].objFrameX = _currentTile.x5;
							_tiles[i + 2 * (TILEX)+1].objFrameY = _currentTile.y5;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + TILEX + 1].obj = objSelect(_currentTile.x3, _currentTile.y3);
							_tiles[i + 2 * (TILEX)].obj = objSelect(_currentTile.x4, _currentTile.y4);
							_tiles[i + 2 * (TILEX)+1].obj = objSelect(_currentTile.x5, _currentTile.y5);
						}
					}

					if (_viewObjNum == 3) {
						if (random == one) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
						}
						if (random == two) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;
							_tiles[i + TILEX].objFrameX = _currentTile.x1;
							_tiles[i + TILEX].objFrameY = _currentTile.y1;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x1, _currentTile.y1);
						}
						if (random == four) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + TILEX].objFrameX = _currentTile.x2;
							_tiles[i + TILEX].objFrameY = _currentTile.y2;

							_tiles[i + TILEX + 1].objFrameX = _currentTile.x3;
							_tiles[i + TILEX + 1].objFrameY = _currentTile.y3;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + TILEX + 1].obj = objSelect(_currentTile.x3, _currentTile.y3);
						}
						if (random == six) {
							_tiles[i].objFrameX = _currentTile.x;
							_tiles[i].objFrameY = _currentTile.y;

							_tiles[i + 1].objFrameX = _currentTile.x1;
							_tiles[i + 1].objFrameY = _currentTile.y1;

							_tiles[i + 2].objFrameX = _currentTile.x2;
							_tiles[i + 2].objFrameY = _currentTile.y2;

							_tiles[i + TILEX].objFrameX = _currentTile.x3;
							_tiles[i + TILEX].objFrameY = _currentTile.y3;

							_tiles[i + TILEX + 1].objFrameX = _currentTile.x4;
							_tiles[i + TILEX + 1].objFrameY = _currentTile.y4;

							_tiles[i + TILEX + 2].objFrameX = _currentTile.x5;
							_tiles[i + TILEX + 2].objFrameY = _currentTile.y5;

							_tiles[i].obj = objSelect(_currentTile.x, _currentTile.y);
							_tiles[i + 1].obj = objSelect(_currentTile.x1, _currentTile.y1);
							_tiles[i + 2].obj = objSelect(_currentTile.x2, _currentTile.y2);
							_tiles[i + TILEX].obj = objSelect(_currentTile.x3, _currentTile.y3);
							_tiles[i + TILEX + 1].obj = objSelect(_currentTile.x4, _currentTile.y4);
							_tiles[i + TILEX + 2].obj = objSelect(_currentTile.x5, _currentTile.y5);
						}
					}

				}
				//오브젝트 관련 삽입
				else if (_ctrlSelect == CTRL_ERASER)
				{
					
					_tiles[i].objFrameX = 0;
					_tiles[i].objFrameY = 0;
					_tiles[i].obj = OBJ_NONE;
					/*_tiles[i].terrainFrameX = 0;
					_tiles[i].terrainFrameY = 0;
					_tiles[i].terrain = TR_NULL;*/
					hideUi();
				}
			}
		}
	}
	
}

void maptool::setRectMap()
{
	if (isSelect == false) {
		if (_viewTile == 1) {
			if (_viewTerNum == 1) {
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 8; j++) {
						if (i == 4 && j == 5) {
							break;
						}
						
							_sampleTerrainTiles[i* SAMPLETERTILEX + j].terrainFrameX = j;
							_sampleTerrainTiles[i* SAMPLETERTILEX + j].terrainFrameY = i;
							SetRect(&_sampleTerrainTiles[i* SAMPLETERTILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
								(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
								(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
						
					}
				}
			}
			else if (_viewTerNum == 2) {
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 7; j++) {
						if (i == 1 && j == 3) {
							break;
						}						
						_sampleTerrainTiles[i* SAMPLETERTILEX + j].terrainFrameX = j;
						_sampleTerrainTiles[i* SAMPLETERTILEX + j].terrainFrameY = i + 6;
						SetRect(&_sampleTerrainTiles[i* SAMPLETERTILEX + j].rcTile, (665 + (j * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) - ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))),
							(665 + (j * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameWidth() / 2))),
							(315 + (i * 45) + ((IMAGEMANAGER->findImage("tilemap")->getFrameHeight() / 2))));
						
					}
				}
			}
		}
		else if (_viewTile == 2) {
			if (_viewObjNum == 1) {
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 3; j++) {
						if (i == 3 && j > 0) {
							break;
						}
						if (i == 0) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 11;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 11;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 11;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 12;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = num + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 12;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 12;
							num += 3;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (695 + (j * 110) - (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 65) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(695 + (j * 110) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),
								(485 + (i * 65) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 1 && j < 2) {
							if (j == 0) {
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 9;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 10;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 10;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 10;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 11;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 10;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num + 9;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 11;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = num + 10;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 11;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = num + 11;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 11;

							}
							if (j == 1) {
								num = 0;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 12;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 1;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 12;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 2;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 12;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 13;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = num + 1;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 13;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = num + 2;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 13;
							}
							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (695 + (j * 110) - (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 80) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(695 + (j * 110) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),
								(485 + (i * 80) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 1 && j == 2) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 12;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 4;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 12;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 5;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 12;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = num + 4;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = num + 5;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 13;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (695 + (j * 115) - (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 80) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(695 + (j * 115) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),
								(485 + (i * 80) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 2 && j == 0) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 6;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 11;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 7;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 11;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 8;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 11;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num + 6;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 12;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = num + 7;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 12;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = num + 8;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 12;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (695 + (j * 110) - (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 80) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(695 + (j * 110) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),
								(485 + (i * 80) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 2 && j == 1) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 14;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = num + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 14;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 14;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (695 + (j * 110) - (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 77) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(695 + (j * 110) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),
								(485 + (i * 77) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 2 && j == 2) {

							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 4;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 5;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 14;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = num + 4;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 14;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = num + 5;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 14;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (695 + (j * 115) - (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 77) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(695 + (j * 115) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),
								(485 + (i * 77) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 3 && j == 0) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 6;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 7;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 13;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 8;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 13;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (695 + (j * 115) - (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 80) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
								(695 + (j * 115) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth() + IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2)),
								(485 + (i * 80) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
						}

					}
					num = 0;
				}

			}
			else if (_viewObjNum == 2) { //멈춤 확인
				for (int i = 0; i < 6; i++) {
					for (int j = 0; j < 12; j++) {
						if (i == 0 && j == 0) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 18;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 18;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 19;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 19;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (678 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(678 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),
								(480 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() + IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 0 && j != 0) {
							if (j > 5) {
								break;
							}
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 18;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 18;
							num += 2;
							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (680 + (j * 60) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(680 + (j * 60) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),
								(480 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 2 && (j > 0 && j < 3)) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = num + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 18;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = num + 3;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 18;
							num += 2;
							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (680 + (j * 60) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(455 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(680 + (j * 60) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),
								(455 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if ((i == 2 || i == 3) && j > 2) {
							if (i == 2 && j > 5) {
								break;
							}
							if (i == 3 && j > 4) {
								break;
							}
							if (i == 2) {
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 2;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 17;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 3;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 17;
								num += 2;
								SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (680 + (j * 60) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
									(460 + (i * 35) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
									(680 + (j * 60) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),
									(460 + (i * 35) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
							}
							if (i == 3) {
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = num + 6;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 17;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = num + 7;
								_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 17;
								num += 2;
								SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (680 + (j * 60) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
									(458 + (i * 35) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
									(680 + (j * 60) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),
									(458 + (i * 35) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
							}
						}
						if (i == 3 && j == 0)
						{
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 18;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 18;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 19;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 19;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (678 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 33) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(678 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),
								(480 + (i * 33) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() + IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 4 && j == 1) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 17;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 18;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = j + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 18;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (680 + (j * 60) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(430 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(680 + (j * 60) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() - 3))),
								(430 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}

					}
					num = 0;
				}
			}
			else if (_viewObjNum == 3) {
				for (int i = 0; i < 7; i++) {
					for (int j = 0; j < 8; j++) {
						if (i == 0 && j != 3) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (666 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(466 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
								(666 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(466 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
						}
						if (i == 0 && j == 3) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 24;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (666 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(482 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(666 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(482 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 1 && j > 3) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (666 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(466 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
								(666 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(466 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
						}
						if (i == 2) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (666 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(466 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
								(666 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(466 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
						}
						if (i == 3 && j == 0) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 24;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (666 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(488 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(666 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(488 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 3 && j == 1) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 24;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 24;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (690 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(488 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(690 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),
								(488 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 3 && j == 3) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 24;
							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (666 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(488 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(666 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(488 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if (i == 3 && j == 4) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = j + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 24;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX4 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY4 = i + 24;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX5 = j + 2;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY5 = i + 24;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (700 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(488 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(700 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()) + (IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),
								(488 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if ((i == 3 || i == 4) && j == 7) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (666 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(466 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
								(666 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(466 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));

						}
						if (i == 5 && j == 0) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 24;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = j + 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 24;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (680 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(477 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(680 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),
								(477 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
						if ((i == 5 || i == 6) && j == 3) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j - 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;

							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (620 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(466 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))),
								(620 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth() / 2))),
								(466 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight() / 2))));
						}
						if (i == 5 && j == 4) {
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX = j - 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX1 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY1 = i + 23;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX2 = j - 1;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY2 = i + 24;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameX3 = j;
							_sampleOBJTiles[i* SAMPLEOBJTILEX + j].objFrameY3 = i + 24;
							SetRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, (640 + (j * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),   //이미지 상의 좌표와 일치 해야 함 즉 j*45의 경우 45측이 이미지의 좌표 사이의 거리(왼쪽과 왼쪽 비교)
								(480 + (i * 45) - ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))),
								(640 + (j * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameWidth()))),
								(480 + (i * 45) + ((IMAGEMANAGER->findImage("objectmap")->getFrameHeight()))));
						}
					}
				}

			}
		}
	}

}

void maptool::save()
{
		if (_ctrlSelect == CTRL_SAVE) {
			//윈도우 핸들 추가 초기 창에 저장 위치 설정
			file = CreateFile("map.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			WriteFile(file, _tiles, sizeof(tagTile)*(TILEY*TILEX), &write, NULL);
			CloseHandle(file);

			/*
			_file2 = CreateFile("map2.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			WriteFile(_file2, _tiles, sizeof(tagTile)*(TILEY*TILEX), &write, NULL);
			CloseHandle(_file2);
			*/
		}
	
}

void maptool::load()
{
	if (_ctrlSelect == CTRL_LOAD) {
		//윈도우 핸들 추가 및 초기 창에서 위치 지정 밑 불러올 것 확인
		file = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(file, _tiles, sizeof(tagTile)*(TILEY*TILEX), &read, NULL);
		CloseHandle(file);

		/*
		_file2 = CreateFile("map.map", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ReadFile(_file2, _tiles, sizeof(tagTile)*(TILEX*TILEY), &read, NULL);
		CloseHandle(_file2);
		*/
	}
}

TERRAIN maptool::terrainSelect(int frameX, int frameY)
{
	if (_ctrlSelect == CTRL_TERRAINDRAW) {
		if (_viewTerNum == 1) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 7; j++) {
					if (j == 6 && i == 2) {
						if (j == frameX && i == frameY)
						{
							return TR_WATER;
						}
					}
					else {
						if (j == frameX && i == frameY)
						{
							return TR_FLOOR;
						}		
					}
				}
			}
		}
		else if (_viewTerNum == 2) {
			for (int i = 5; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					if (frameX == j && frameY == i)
					{
						return TR_WALL;
					}//벽		
				}
			}
		}		
	}
	return TERRAIN();
}

OBJECT maptool::objSelect(int frameX, int frameY)
{
	if (_ctrlSelect == CTRL_OBJDRAW) {
		if (_viewObjNum == 2) {
			for (int j = 17; j < 23; j++) {
				for (int i = 0; i < 14; i++)
				{
					if (frameX == i && frameY == j) {
						return OBJ_BED;
					}
				}
			}
		}
		
		else if (_viewObjNum == 3) {			
			for (int j = 23; j < 30; j++) {
				for (int i = 0; i < 9; i++) {
					if ((i == 0 && j == 23) || (i == 1 && j == 23)) {
						if (frameX == i && frameY == j) {
							return OBJ_MOVE;
						}
					}
					else {
						if (frameX == i && frameY == j) {
							return OBJ_RAND;
						}
					}
					
				}
			}
		}
		else if (_viewObjNum == 1) {
			for (int j = 11; j < 17; j++) {
				for (int i = 0; i < 11; i++) {
					if (frameX == i && frameY == j) {
						return OBJ_CAR;  
					}
				}
			}			
		}
		
	}

	return OBJECT();
}

void maptool::hideObj()
{
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 14; j++) {
			SetRect(&_sampleOBJTiles[i* SAMPLETERTILEX + j].rcTile, -100, -100, -100, -100);
		}
	}
	_currentTile.x =3;
	_currentTile.y = 3;
	_currentTile.x1 = 3;
	_currentTile.y1 = 3;
	_currentTile.x2 = 3;
	_currentTile.y2 = 3;
	_currentTile.x3 = 3;
	_currentTile.y3 = 3;
	_currentTile.x4 = 3;
	_currentTile.y4 = 3;
	_currentTile.x5 = 3;
	_currentTile.y5 = 3;
}

void maptool::hideTerrain()
{	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			SetRect(&_sampleTerrainTiles[i* SAMPLETERTILEX + j].rcTile, -100, -100, -100, -100);
		}
	}

}

void maptool::UI()
{
	if (isSelect == false) {
		if (isMenu == false) {
			if (PtInRect(&menuRc, m_ptMouse) && KEYMANAGER->isStayKeyDown(VK_RBUTTON)) {

				menuRc = RectMakeCenter(WINSIZEX, m_ptMouse.y, 100, 100);
				y = m_ptMouse.y;
			}  // 소메뉴 이동		
			if (PtInRect(&menuRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				isMenu = true;
				isFirst = true;
				menuRc = RectMakeCenter(825, WINSIZEY / 2, 400, WINSIZEY);
				if (isFirst = true) {
					initRc = RectMakeCenter(830, 260, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
					saveRc = RectMakeCenter(830, 120, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
					loadRc = RectMakeCenter(830, 190, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
					terrainRc = RectMakeCenter(830, 400, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
					objRc = RectMakeCenter(830, 470, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
					eraserRc = RectMakeCenter(830, 330, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());

				}
			}
		}
		if (isMenu == true) {
			if (KEYMANAGER->isOnceKeyDown(VK_LCONTROL)) {
				isMenu = false;
				isFirst = false;
				_viewTile = 0;
				_viewTerNum = 0;
				_viewObjNum = 0;
				menuRc = RectMakeCenter(WINSIZEX, y, 100, 100);
				hideObj();
				hideTerrain();
				isSelect = false;
				isSetting = false;
			}
		}
		if (isFirst == true) {
			if (PtInRect(&terrainRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				//_ctrlSelect = CTRL_TERRAINDRAW;
				isFirst = false;
				_viewTile = 1;
			}
		}

		if (_viewTile == 1) {
			if (PtInRect(&wallRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				hideTerrain();
				_ctrlSelect = CTRL_TERRAINDRAW;
				_viewTerNum = 2;

			}
			if (PtInRect(&floorRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				hideTerrain();
				_ctrlSelect = CTRL_TERRAINDRAW;
				_viewTerNum = 1;

			}
		}
		if (isFirst == true) {
			if (PtInRect(&objRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_ctrlSelect = CTRL_OBJDRAW;
				isFirst = false;
				_viewTile = 2;
			}
		}

		if (_viewTile == 2) {
			if (PtInRect(&carRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_viewObjNum = 1;
				hideObj();

			}
			if (PtInRect(&bedRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_viewObjNum = 2;
				hideObj();


			}
			if (PtInRect(&randRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_viewObjNum = 3;

				hideObj();

			}
		}
		if (isFirst == true) {
			if (PtInRect(&saveRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_ctrlSelect = CTRL_SAVE;
				save();
			}
			if (PtInRect(&loadRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_ctrlSelect = CTRL_LOAD;
				load();
			}
			if (PtInRect(&initRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_ctrlSelect = CTRL_INIT;
				init();
			}
			if (PtInRect(&eraserRc, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
				_ctrlSelect = CTRL_ERASER;
				isSelect = true;
				hideUi();

			}
		}
		if (_viewTile == 1) {
			wallRc = RectMakeCenter(830, 120, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
			floorRc = RectMakeCenter(830, 190, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
		}
		else {
			hideTerrainUI();
		}

		if (_viewTile == 2) {
			randRc = RectMakeCenter(830, 260, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
			carRc = RectMakeCenter(830, 120, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
			bedRc = RectMakeCenter(830, 190, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
		}
		else {
			hideOBJUI();
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Q')) {
		menuRc = RectMakeCenter(825, WINSIZEY / 2, 400, WINSIZEY);
		isFirst = true;
		_viewTile = 0;
		_viewTerNum = 0;
		_viewObjNum = 0;
		hideTerrain();
		hideObj();
		isSelect = false;
		isSetting = false;
	}
}

void maptool::hideTerrainUI()
{
	wallRc = RectMakeCenter(-830, 120, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	floorRc = RectMakeCenter(-830, 190, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
}

void maptool::hideOBJUI()
{	
	carRc = RectMakeCenter(-830, 120, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());	
	randRc = RectMakeCenter(-830, 400, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
	bedRc = RectMakeCenter(-830, 190, IMAGEMANAGER->findImage("button")->getWidth(), IMAGEMANAGER->findImage("button")->getHeight());
}

void maptool::hideUi()
{	
	menuRc = RectMakeCenter(WINSIZEX+50, y, 100, 100);		
	isSelect = true;		
}

void maptool::isTF()
{
	if (isSelect == false) {
		if (_viewObjNum == 2) {
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 12; j++) {
					if (i == 0 && j == 0) {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							bed = big;
						}
					}
					else if ((i == 2 || i == 3) && j > 2) {
						if (i == 2 && j > 5) {
							break;
						}
						if (i == 3 && j > 4) {
							break;
						}
						if (i == 2) {
							if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
								bed = small;
							}
						}
						if (i == 3) {
							if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
								bed = small;
							}
						}
					}
					else if (i == 3 && j == 0) {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							bed = big;
						}
					}
					else {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							bed = middle;
						}
					}
				}
			}
		}
		if (_viewObjNum == 1) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					if (i == 3 && j > 0) {
						break;
					}
					if (i == 3 && j == 0) {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							isBike = true;
						}
					}
					else
					{
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							isBike = false;
						}
					}
				}
			}
		}

		if (_viewObjNum == 3) {
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 8; j++) {


					if ((i == 0 && j == 3) || (i == 3 && j == 3) || (i == 3 && j == 0)) {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							random = two;
						}
					}


					else if ((i == 3 && j == 1) || (i == 5 && j == 0) || (i == 5 && j == 4)) {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							random = four;
						}
					}

					else  if (i == 3 && j == 4) {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							random = six;
						}
					}
					else {
						if (PtInRect(&_sampleOBJTiles[i* SAMPLEOBJTILEX + j].rcTile, m_ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) {
							random = one;
						}
					}
				}
			}
		}
	}
}
