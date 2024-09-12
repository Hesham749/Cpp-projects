#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

class clsManageUsersScreen :protected clsScreen
{
	enum enManageUsersMenuOptions {
		eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenu = 6
	};

	static short _ReadManageUsersMenuOption()
	{
		cout << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	static void _GoBackToManageUsersMenue()
	{
		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");

	}

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersList();

	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();

	}

	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();

	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _ManageUserMenu()
	{
		system("cls");
		_ScreenHeader("Manage Users Screen", 2);
		cout << "===========================================\n";
		cout << "\t\tManage Users Menu\n";
		cout << "===========================================\n";
		cout << "\t[1] List Users.\n";
		cout << "\t[2] Add New User.\n";
		cout << "\t[3] Delete User.\n";
		cout << "\t[4] Update User.\n";
		cout << "\t[5] Find User.\n";
		cout << "\t[6] Main Menu.\n";
		cout << "===========================================\n";
	}

	static void _PerformManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenueOption)
	{
		system("cls");
		switch (ManageUsersMenueOption)
		{
		case enManageUsersMenuOptions::eListUsers:
		{
			_ShowListUsersScreen();
			break;
		}

		case enManageUsersMenuOptions::eAddNewUser:
		{
			_ShowAddNewUserScreen();
			break;
		}

		case enManageUsersMenuOptions::eDeleteUser:
		{
			_ShowDeleteUserScreen();
			break;
		}

		case enManageUsersMenuOptions::eUpdateUser:
		{
			_ShowUpdateUserScreen();
			break;
		}

		case enManageUsersMenuOptions::eFindUser:
		{

			_ShowFindUserScreen();
			break;
		}
		}

		if (ManageUsersMenueOption != enManageUsersMenuOptions::eMainMenu)
			_GoBackToManageUsersMenue();
	}


public:

	static void ShowMangeUsersMenu()
	{
		enManageUsersMenuOptions ManageUsersMenueOption;
		do
		{
			_ManageUserMenu();
			_PerformManageUsersMenuOption(ManageUsersMenueOption = (enManageUsersMenuOptions)_ReadManageUsersMenuOption());
		} while (ManageUsersMenueOption != eMainMenu);
	}
};

