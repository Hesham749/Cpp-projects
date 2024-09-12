#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"
class clsFindUserScreen :protected clsScreen
{
	static void _PrintUser(clsUser& User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.AccountPermissions;
		cout << "\n___________________\n";
	}

public:

	static void ShowFindUserScreen()
	{

		_ScreenHeader("Find User Screen", 2);

		string UserName;
		cout << "\nPlease Enter User Name: ";
		while (!clsUser::IsUserExist(UserName = clsInputValidate::ReadString()))
		{
			cout << "\nUser Name is not found, choose another one: ";
		}

		clsUser User1 = clsUser::Find(UserName);

		if (!User1.IsEmpty())
		{
			cout << "\nUser Found :-)\n";
		}
		else
		{
			cout << "\nUser Was not Found :-(\n";
		}

		_PrintUser(User1);

	}
};

