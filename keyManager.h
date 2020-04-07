#pragma once
#include"singletonBase.h"
#include<bitset>
using namespace std;
#define KEYMAX 256
class keyManager :  public singletonBase<keyManager>
{
private:

	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	
public:
	keyManager();
	~keyManager();

	HRESULT init();

	void release();

	//한번만 눌렀냐
	bool isOnceKeyDown(int key);
	//눌렀다가 뗏냐
	bool isOnceKeyUp(int key);
	//누르고 있냐
	bool isStayKeyDown(int key);
	//토글키냐
	bool isToggleKey(int key);
};

