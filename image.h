#pragma once
#include"animation.h"
class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,	//���ҽ� �ε�
		LOAD_FILE,			//���� �ε�
		LOAD_EMPTY,			//�� ��Ʈ�� ����
		LOAD_END
	};


	typedef struct tagImage
	{
		DWORD	resID;		//���ҽ� ID
		HDC		hMemDC;		//�޸� DC
		HBITMAP hBit;				//��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP hOBit;				//�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)
		int		width;				//�̹��� ����ũ��
		int		height;				//�̹��� ����ũ��
		BYTE	loadType;			//�ε� Ÿ��
		float	x;					//�̹��� x��ǥ
		float   y;					//�̹��� Y��ǥ
		int		currentFrameX;		//����������X
		int		currentFrameY;		//����������Y
		int		maxFrameX;			//�ִ� X������ ����
		int		maxFrameY;			//�ִ� Y������ ����
		int		frameWidth;			//1������ ���α���
		int		frameHeight;		//1������ ���α���


		tagImage()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			x = 0;
			y = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

	image();
	~image();

private:

	LPIMAGE_INFO	_imageInfo;		//�̹��� ����
	char*			_fileName;		//�̹��� �̸�
	bool			_isTrans;		//���� ��������?
	COLORREF		_transColor;	//���� ���� RGB

	BLENDFUNCTION	_blendFunc;		//���ĺ��� ��������
	LPIMAGE_INFO	_blendImage;	//���� ���带 ����ϱ� ���� �̹��� ����

public:
	//�� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT init(int width, int height);

	HRESULT init(const char* fileName, int width, int height,
		bool isTrans, COLORREF transColor);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		bool isTrans, COLORREF transColor);
	//������ �̹��� ���Ϸ� �ʱ�ȭ

	HRESULT init(const char* fileName, int width, int height,
		int frameX, int frameY, bool isTrans, COLORREF transColor);

	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, bool isTrans, COLORREF transColor);

	//���� ����
	void setTransColor(bool isTrans, COLORREF transColor);

	//����
	void release();

	//����(���� ������ ��ġ�� �̹��� ���)
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);


	//�����ӷ���
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	//��������(hdc, ������ų����, x������, y������)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);
	//���ķ���
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	//DC�����Ͷ�
	inline HDC getMemDC() { return _imageInfo->hMemDC; }


	//�̹��� ��ǥx ���
	inline float getX() { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }

	//�̹��� ��ǥy ���
	inline float getY() { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	//�̹��� ���� ��ǥ ����
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	//����,����ũ�� ���
	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	//�ٿ�� �ڽ�(�浹��)
	inline RECT getBoundingBox()
	{
		RECT rc = RectMakeCenter(_imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height);
		return rc;
	}

	//������ x ����
	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	//������ y ����
	inline int getFrameY() { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	//1������ ���μ��� ũ��
	inline int getFrameWidth() { return _imageInfo->frameWidth; }
	inline int getFrameHeight() { return _imageInfo->frameHeight; }

	//�ƽ������� x,y
	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }


};

