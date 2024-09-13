#pragma once
#include <iostream>
#include "clsUtil.h"
#include "Global.h"
#include "clsUser.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{
protected:

	static void _ShowUserName()
	{
		printf("User : %s\n", CurrentUser.UserName.c_str());
	}



	static void _ShowCurrentDate()
	{
		printf("Date : %s\n", clsDate::Print(clsDate()).c_str());
	}

	static void _ScreenHeader(string Title, short tabs = 0, string SubTitle = "")
	{
		cout << "______________________________________________________";
		cout << "\n\n" << clsUtil::Tabs(tabs) << Title;
		if (SubTitle != "")
		{
			cout << "\n" << clsUtil::Tabs(tabs) << SubTitle;
		}
		cout << "\n______________________________________________________\n\n";
		_ShowUserName();
		_ShowCurrentDate();
		cout << endl;
	}

	static bool HasPermission(clsUser::enPermissions Permission)
	{
		if (CurrentUser.Haspermission(Permission))
			return true;
		else
		{
			_ScreenHeader(" Access Denied! Contact your Admin.");
			return false;
		}

	}
};

