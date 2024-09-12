#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iomanip>
#include "clsUtil.h"

class clsAddNewUserScreen : protected clsScreen
{
private:


	static short _ReadUserPermissions()
	{
		if (clsUtil::ConfirmAction("\nDo you want to give full access ? y/n ? "))
			return -1;
		short Permissions = 0;
		if (clsUtil::ConfirmAction("\nDo you want to give access to :\n\nShow Client List ? y/n ? "))
			Permissions |= clsUser::enPermissions::ListAccess;
		if (clsUtil::ConfirmAction("Add new Client ?   y/n ? "))
			Permissions |= clsUser::enPermissions::AddAccess;
		if (clsUtil::ConfirmAction("Delete Client ?    y/n ? "))
			Permissions |= clsUser::enPermissions::DeleteAccess;
		if (clsUtil::ConfirmAction("Update Client ?    y/n ? "))
			Permissions |= clsUser::enPermissions::UpdateAccess;
		if (clsUtil::ConfirmAction("Find Client ?      y/n ? "))
			Permissions |= clsUser::enPermissions::FindAccess;
		if (clsUtil::ConfirmAction("Transactions ?     y/n ? "))
			Permissions |= clsUser::enPermissions::TransactionsAccess;
		if (clsUtil::ConfirmAction("Manage Users ?     y/n ? "))
			Permissions |= clsUser::enPermissions::MangeUsersAccess;
		return Permissions;
	}

	static void _ReadUserInfo(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();

		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();

		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();

		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();

		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();

		cout << "\nEnter Account Permissions: ";
		User.Permissions = _ReadUserPermissions();
	}

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

public:

	static void ShowAddNewUserScreen()
	{

		_ScreenHeader("Add New User Screen", 2);

		string UserName = "";

		cout << "\nPlease Enter User Name: ";
		while (clsUser::IsUserExist(UserName = clsInputValidate::ReadString()))
		{
			cout << "\nUser Name Is Already Used, Choose another one: ";
		}

		clsUser NewUser = clsUser::AddNewUser(UserName);


		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;

		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case  clsUser::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Added Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;

		}
		case clsUser::enSaveResults::svFaildUserNameExists:
		{
			cout << "\nError account was not saved because User Name is used!\n";
			break;

		}
		}
	}


};

