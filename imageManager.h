#pragma once
#include"singletonBase.h"
#include"image.h"
class imageManager : public singletonBase<imageManager>
{

private:
	//������ ���� �̹��� ���
	typedef map<string, image*> mapImageList;
	//������ ���� �̹��� ����� �ݺ���
	typedef map<string, image*>::iterator mapImageListIter;

	mapImageList _mImageList;

public:
	imageManager();
	~imageManager();


	HRESULT init();
	void release();
	//Ű ������ �� ��Ʈ�� �ʱ�ȭ
	image* addImage(string strKey, int width, int height);
	//Ű������ �̹��� ���� �ʱ�ȭ
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);
	//Ű������ ������ �̹��� ���� �ʱ�ȭ
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	//�̹��� Ű������ ã��
	image* findImage(string strKey);
	//�̹��� Ű������ ����
	bool deleteImage(string strKey);
	//�̹��� ��ü����
	bool deleteAll();


	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

};

