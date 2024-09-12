#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen :protected::clsScreen
{

	static void _Login()
	{
		bool LoginFailed = false;
		do
		{
			system("cls");
			_ScreenHeader("Login Screen", 2);
			if (LoginFailed)
				cout << "Invalid User Name/Password!\n";
			printf("Enter User Name ? ");
			string UserName = clsInputValidate::ReadString();
			printf("Enter Password ? ");
			string Password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
		} while (LoginFailed = CurrentUser.IsEmpty());
		clsMainScreen::ShowMainMenu();
	}

public:
	static void ShowLoginScreen()
	{
		_Login();
	}
};

