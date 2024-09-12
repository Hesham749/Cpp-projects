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
		eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
		eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
		eManageUsers = 7, eExit = 8
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
			_ShowAllClientsScreen();
			break;
		}
		case enMainMenuOptions::eAddNewClient:
			_ShowAddNewClientsScreen();
			break;

		case enMainMenuOptions::eDeleteClient:

			_ShowDeleteClientScreen();
			break;

		case enMainMenuOptions::eUpdateClient:

			_ShowUpdateClientScreen();
			break;

		case enMainMenuOptions::eFindClient:

			_ShowFindClientScreen();
			break;

		case enMainMenuOptions::eShowTransactionsMenu:

			_ShowTransactionsMenu();
			break;

		case enMainMenuOptions::eManageUsers:

			_ShowManageUsersMenu();
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

