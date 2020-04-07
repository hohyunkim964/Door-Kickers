#pragma once
#include"singletonBase.h"
class txtData :  public singletonBase<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT init();

	//세이브용
	void txtSave(char* saveFileName, vector<string>vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//로드

	vector<string>txtLoad(char* loadFileName);
	vector<string>charArraySeperation(char charArray[]);


};

