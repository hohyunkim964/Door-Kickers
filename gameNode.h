#pragma once
#include"image.h"
//백버퍼 이미지를 스태틱으로..

static image * _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);



class gameNode
{
private:

	//void setBackBuffer();		//백버퍼 셋팅

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


	//백버퍼 가져오기
	image* getBackBuffer() { return _backBuffer; }

	HDC getHDC() { return _hdc; }
	
	HDC getMemDC() { return _backBuffer->getMemDC(); }

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

};

