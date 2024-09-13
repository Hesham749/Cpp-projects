#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "Global.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
private:
	enum enMainMenuOptions {
		eListClients = 1, eAddNewClient, eDeleteClient,
		eUpdateClient, eFindClient, eShowTransactionsMenu,
		eManageUsers, eLoginRegisterScreen, eExit
	};

	static short _ReadMainMenuOption()
	{
		cout << "Choose what do you want to do? [1 to 8]? ";
		return clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8? ");
	}

	static  void _GoBackToMainMenu()
	{
		cout << "\nPress any key to go back to Main Menu...\n";
		system("pause>0");
	}

	static void _ShowAllClientsScreen()
	{
		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientsScreen()
	{
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		clsDeleteClientScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		clsUpdateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenu()
	{
		clsTransactionsScreen::ShowTransactionsMenu();
	}

	static void _ShowManageUsersMenu()
	{
		clsManageUsersScreen::ShowMangeUsersMenu();
	}

	static void _showLoginRegisterScreen()
	{

	}

	static void _Logout()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static void _MainMenu()
	{
		system("cls");
		_ScreenHeader("Main Screen", 2);
		cout << "======================================================\n";
		cout << "\t\tMain Menu Screen\n";
		cout << "======================================================\n";
		cout << "\t[1] Show Clients list.\n";
		cout << "\t[2] Add New Client.\n";
		cout << "\t[3] Delete Client.\n";
		cout << "\t[4] Update Client Info.\n";
		cout << "\t[5] Find Client.\n";
		cout << "\t[6] Transactions.\n";
		cout << "\t[7] Manage Users.\n";
		cout << "\t[8] Logout.\n";
		cout << "======================================================\n";
	}

	static void _PerfromMainMenuOption(enMainMenuOptions MainMenuOption)
	{
		system("cls");
		switch (MainMenuOption)
		{
		case enMainMenuOptions::eListClients:
		{
			if (clsScreen::HasPermission(clsUser::ListAccess))
				_ShowAllClientsScreen();
			break;
		}
		case enMainMenuOptions::eAddNewClient:
			if (clsScreen::HasPermission(clsUser::AddAccess))
				_ShowAddNewClientsScreen();
			break;

		case enMainMenuOptions::eDeleteClient:
			if (clsScreen::HasPermission(clsUser::DeleteAccess))
				_ShowDeleteClientScreen();
			break;

		case enMainMenuOptions::eUpdateClient:
			if (clsScreen::HasPermission(clsUser::UpdateAccess))
				_ShowUpdateClientScreen();
			break;

		case enMainMenuOptions::eFindClient:
			if (clsScreen::HasPermission(clsUser::FindAccess))
				_ShowFindClientScreen();
			break;

		case enMainMenuOptions::eShowTransactionsMenu:
			(clsScreen::HasPermission(clsUser::TransactionsAccess)) ?
				_ShowTransactionsMenu() : _GoBackToMainMenu();
			break;

		case enMainMenuOptions::eManageUsers:
			(clsScreen::HasPermission(clsUser::MangeUsersAccess)) ?
				_ShowManageUsersMenu() : _GoBackToMainMenu();
			break;

		case enMainMenuOptions::eExit:
			_Logout();
			break;
		}
		if (MainMenuOption != eExit && MainMenuOption != eManageUsers && MainMenuOption != eShowTransactionsMenu)
			_GoBackToMainMenu();
	}
public:

	static void ShowMainMenu()
	{
		enMainMenuOptions MainMenuOption;
		do {
			_MainMenu();
			_PerfromMainMenuOption(MainMenuOption = (enMainMenuOptions)_ReadMainMenuOption());
		} while (MainMenuOption != eExit);
	}
};

