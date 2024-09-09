#pragma once
#include <iostream>
#include "clsUtil.h"
using namespace std;

class clsScreen
{
protected:
	static void _ScreenHeader(string Title, short tabs = 0, string SubTitle = "")
	{
		cout << "______________________________________________________";
		cout << "\n\n" << clsUtil::Tabs(tabs) << Title;
		if (SubTitle != "")
		{
			cout << "\n" << clsUtil::Tabs(tabs) << SubTitle;
		}
		cout << "\n______________________________________________________\n\n";
	}
};

