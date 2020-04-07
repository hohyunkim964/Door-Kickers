#pragma once
#include"singletonBase.h"
#include"image.h"
class imageManager : public singletonBase<imageManager>
{

private:
	//맵으로 만든 이미지 목록
	typedef map<string, image*> mapImageList;
	//맵으로 만든 이미지 목록의 반복자
	typedef map<string, image*>::iterator mapImageListIter;

	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();


	HRESULT init();
	void release();
	//키 값으로 빈 비트맵 초기화
	image* addImage(string strKey, int width, int height);
	//키값으로 이미지 파일 초기화
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	//키값으로 프레임 이미지 파일 초기화
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	bool deleteImage(string strKey);
	//이미지 전체삭제
	bool deleteAll();


	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

};

