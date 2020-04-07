#include "stdafx.h"
#include "gameNode.h"

bool gameNode::isChange = false;		//전역 변수 선언

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	_hdc = GetDC(m_hWnd);
	_managerInit = false;
	return S_OK;
}
HRESULT gameNode::init(bool managerInit)
{
	
	_hdc = GetDC(m_hWnd);
	_managerInit = managerInit;

	

	if (managerInit)
	{
		SetTimer(m_hWnd, 1, 10, NULL);
		//매니저 초기화
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->init();
		SOUNDMANAGER->init();
		ANIMATIONMANAGER->init();
		EFFECTMANAGER->init();
		TXTDATA->init();
		
	}
	
	return S_OK;
}
//void gameNode::setBackBuffer()
//{
//	_backBuffer = new image;
//	_backBuffer->init(WINSIZEX, WINSIZEY);
//}

void gameNode::release()
{	//타이머 해제

	if (_managerInit)
	{
		//해제를 안하면 종료를 해도 메모리가 줄줄줄~

		KillTimer(m_hWnd, 1);
		//매니저 해제
		KEYMANAGER->releaseSingleton();
		IMAGEMANAGER->releaseSingleton();
		TIMEMANAGER->releaseSingleton();
		SCENEMANAGER->releaseSingleton();
		SOUNDMANAGER->releaseSingleton();
		ANIMATIONMANAGER->releaseSingleton();
		EFFECTMANAGER->releaseSingleton();
		RND->releaseSingleton();
		TXTDATA->releaseSingleton();

		IMAGEMANAGER->release();
		SCENEMANAGER->release();
		SOUNDMANAGER->release();
		ANIMATIONMANAGER->release();
		EFFECTMANAGER->release();

	}
	ReleaseDC(m_hWnd, _hdc);

	//SAFE_DELETE(_backBuffer);

}

void gameNode::update()
{
	//더블버퍼 이후 사용하지 않는다 true->false
	InvalidateRect(m_hWnd, NULL, false);
}
void gameNode::render(/*HDC hdc*/)
{
}


LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage)
	{
	
	case WM_MOUSEMOVE:
		m_ptMouse.x = LOWORD(lParam);
		m_ptMouse.y = HIWORD(lParam);
		
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		/*
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		*/
		}
		break;
		//프로그램 실행중 사용자가 메뉴 항목을 선택하면 발생하는 메세지임.
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}//end of switch

	return (DefWindowProc(hWnd,iMessage,wParam,lParam));
}
