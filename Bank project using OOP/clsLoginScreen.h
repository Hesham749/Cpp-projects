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
		short NumberOfTrials = 0;
		do
		{
			system("cls");
			_ScreenHeader("Login Screen", 2);
			if (LoginFailed)
			{
				NumberOfTrials++;
				cout << "Invalid User Name/Password!\n";
				printf("You have %d Trial(s) to login\n", 3 - NumberOfTrials);
			}
			if (NumberOfTrials == 3)
			{
				cout << "\nYou are locked after 3 Failed Trials\n\n";
				return false;
			}
			printf("Enter User Name ? ");
			string UserName = clsInputValidate::ReadString();
			printf("Enter Password ? ");
			string Password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
		} while (LoginFailed = CurrentUser.IsEmpty());
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenu();
		return  true;
	}

public:
	static bool ShowLoginScreen()
	{
		return _Login();
	}
};

