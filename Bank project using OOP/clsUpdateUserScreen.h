#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

class clsUpdateUserScreen :protected clsScreen
{

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

	static void ShowUpdateUserScreen()
	{

		_ScreenHeader("Update User Screen", 2);

		string AccountNumber = "";

		cout << "\nPlease Enter User Account Number: ";

		while (!clsUser::IsUserExist(AccountNumber = clsInputValidate::ReadString()))
		{
			cout << "\nAccount number is not found, choose another one: ";
		}

		clsUser User1 = clsUser::Find(AccountNumber);

		_PrintUser(User1);

		if (clsUtil::ConfirmAction("\nAre you sure you want to update this User y/n? "))
		{

			cout << "\n\nUpdate User Info:";
			cout << "\n____________________\n";


			_ReadUserInfo(User1);

			clsUser::enSaveResults SaveResult;

			SaveResult = User1.Save();

			switch (SaveResult)
			{
			case  clsUser::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Updated Successfully :-)\n";

				_PrintUser(User1);
				break;
			}
			case clsUser::enSaveResults::svFaildEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;

			}

			}

		}

	}
};

