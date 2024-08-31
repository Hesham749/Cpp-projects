#pragma once
#include <iostream>
using namespace std;

class clsString
{
	string _Value;

public:
	clsString()
		:_Value("")
	{}

	clsString(string Value)
		:_Value(Value)
	{}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}

	__declspec(property (get = GetValue, put = SetValue)) string Value;



};

