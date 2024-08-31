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

	string Value()
	{
		return _Value;
	}



};
