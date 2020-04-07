#pragma once


#define TILESIZE 32 //왼쪽 화면 타일 사이즈
#define TILEX 32//왼쪽화면 타일 X축 개수  
#define TILEY 32//왼쪽화면 타일 Y축 개수

#define TILESIZEX TILEX * TILESIZE
#define TILESIZEY TILEY * TILESIZE

//화면 오른쪽 이미지 타일 갯수 //terrain
#define SAMPLETERTILEX 8
#define SAMPLETERTILEY 8

#define SAMPLEOBJTILEX 16
#define SAMPLEOBJTILEY 30
//속성 관련 설정(이동 가능 여부)
#define ATTR_UNMOVABLE 0x00000001
#define ATTR_POSITION 0x00000002

enum TERRAIN
{
	TR_NULL, TR_FLOOR, TR_WALL, TR_WATER, TR_END
};

//오브젝트(EX :지형위쪽에 배치. 움직이거나 부서지거나 하는 녀석 등등 변화를 줄수 있는 물체)
enum OBJECT
{
	OBJ_CAR,
	OBJ_BED,
	OBJ_MOVE,
	OBJ_RAND,
	OBJ_NONE
};
//위치 좌표
enum POS
{

};
//타일 구조체
struct tagTile
{
	TERRAIN terrain;
	OBJECT obj;
	RECT rc;

	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;
	
	
};
//이미지 타일 구조체
struct tagSampleTile
{
	RECT rcTile;
	int terrainFrameX;
	int terrainFrameY;
	int objFrameX;
	int objFrameY;

	int objFrameX1;
	int objFrameY1;

	int objFrameX2;
	int objFrameY2;

	int objFrameX3;
	int objFrameY3;

	int objFrameX4;
	int objFrameY4;

	int objFrameX5;
	int objFrameY5;

	int objFrameX6;
	int objFrameY6;

	int objFrameX7;
	int objFrameY7;

	int objFrameX8;
	int objFrameY8;

	int objFrameX9;
	int objFrameY9;

	int objFrameX10;
	int objFrameY10;

	int objFrameX11;
	int objFrameY11;

	int objFrameX12;
	int objFrameY12;


};
//현재 타일 구조체
struct tagCurrentTile
{
	int x;
	int y;

	int x1;
	int y1;

	int x2;
	int y2;

	int x3;
	int y3;

	int x4;
	int y4;

	int x5;
	int y5;

	int x6;
	int y6;

	int x7;
	int y7;

	int x8;
	int y8;

	int x9;
	int y9;

	int x10;
	int y10;

	int x11;
	int y11;

	int x12;
	int y12;
};