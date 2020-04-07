#pragma once
#include"image.h"
//����� �̹����� ����ƽ����..

static image * _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);



class gameNode
{
private:

	//void setBackBuffer();		//����� ����

	HDC _hdc;
	bool _managerInit;

protected:
	static bool isChange;
public:
	gameNode();
	~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update();
	virtual void render(/*HDC hdc*/);


	//����� ��������
	image* getBackBuffer() { return _backBuffer; }

	HDC getHDC() { return _hdc; }
	
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

