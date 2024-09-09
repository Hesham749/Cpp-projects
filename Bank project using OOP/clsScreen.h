#pragma once
#include <iostream>
#include "clsUtil.h"
using namespace std;

class clsScreen
{
protected:
	static void _ScreenHeader(string Title, string SubTitle = "")
	{
		cout << "______________________________________________________";
		cout << "\n\n" << clsUtil::Tabs(2) << Title;
		if (SubTitle != "")
		{
			cout << "\n" << clsUtil::Tabs(2) << SubTitle;
		}
		cout << "\n______________________________________________________\n\n";
	}
};

