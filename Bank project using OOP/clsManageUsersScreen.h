#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
#include "clsLoginRegisterScreen.h"

class clsManageUsersScreen :protected clsScreen
{
	enum enManageUsersMenuOptions {
		eListUsers = 1, eAddNewUser, eDeleteUser,
		eUpdateUser, eFindUser, eLoginRegisterScreen, eMainMenu
	};

	static short _ReadManageUsersMenuOption()
	{
		cout << "Choose what do you want to do? [1 to 7]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 7, "Enter Number between 1 to 7? ");
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

	static void _showLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
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
		cout << "\t[6] Login Register List.\n";
		cout << "\t[7] Main Menu.\n";
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
		case enManageUsersMenuOptions::eLoginRegisterScreen:
			_showLoginRegisterScreen();
			break;
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

