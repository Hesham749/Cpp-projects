#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsDeleteUserScreen :protected clsScreen
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
		cout << "\nPermissions : " << User.Permissions;
		cout << "\n___________________\n";
	}


public:	static void ShowDeleteUserScreen()
	{

		_ScreenHeader("Delete User Screen", 2);

		string UserName = "";

		cout << "\nPlease Enter Account Number: ";
		while (!clsUser::IsUserExist(UserName = clsInputValidate::ReadString()))
		{
			cout << "\nAccount number is not found, choose another one: ";
		}

		clsUser User1 = clsUser::Find(UserName);
		_PrintUser(User1);

		if (clsUtil::ConfirmAction("\nAre you sure you want to delete this User y/n? "))
		{


			if (User1.Delete())
			{
				cout << "\nUser Deleted Successfully :-)\n";
				_PrintUser(User1);
			}
			else
			{
				cout << "\nError User Was not Deleted\n";
			}
		}
	}
};

