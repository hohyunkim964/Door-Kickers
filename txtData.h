#pragma once
#include"singletonBase.h"
class txtData :  public singletonBase<txtData>
{
public:
	txtData();
	~txtData();

	HRESULT init();

	//���̺��
	void txtSave(char* saveFileName, vector<string>vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//�ε�

	vector<string>txtLoad(char* loadFileName);
	vector<string>charArraySeperation(char charArray[]);


};

