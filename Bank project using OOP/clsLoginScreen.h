#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen :protected::clsScreen
{

	static bool _Login()
	{
		bool LoginFailed = false;
		short NumberOfTries = 0;
		do
		{
			system("cls");
			_ScreenHeader("Login Screen", 2);
			if (LoginFailed)
			{
				NumberOfTries++;
				cout << "Invalid User Name/Password!\n";
				printf("You have %d Tries to login\n", 3 - NumberOfTries);
			}
			if (NumberOfTries == 3)
			{
				cout << "\nYou are locked after 3 failed tries\n\n";
				return false;
			}
			printf("Enter User Name ? ");
			string UserName = clsInputValidate::ReadString();
			printf("Enter Password ? ");
			string Password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
		} while (LoginFailed = CurrentUser.IsEmpty());
		clsMainScreen::ShowMainMenu();
		return  true;
	}

public:
	static bool ShowLoginScreen()
	{
		return _Login();
	}
};

