#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
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
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 8, "Enter Number between 1 to 8? ");
		return Choice;
	}

	static  void _GoBackToMainMenu()
	{
		cout << "\nPress any key to go back to Main Menu...\n";

		system("pause>0");
		ShowMainMenu();
	}

	static void _ShowAllClientsScreen()
	{
		cout << "\nClient List Screen Will be here...\n";

	}

	static void _ShowAddNewClientsScreen()
	{
		cout << "\nAdd New Client Screen Will be here...\n";

	}

	static void _ShowDeleteClientScreen()
	{
		cout << "\nDelete Client Screen Will be here...\n";

	}

	static void _ShowUpdateClientScreen()
	{
		cout << "\nUpdate Client Screen Will be here...\n";

	}

	static void _ShowFindClientScreen()
	{
		cout << "\nFind Client Screen Will be here...\n";

	}

	static void _ShowTransactionsMenu()
	{
		cout << "\nTransactions Menu Will be here...\n";

	}

	static void _ShowManageUsersMenu()
	{
		cout << "\nUsers Menu Will be here...\n";

	}

	static void _ShowEndScreen()
	{
		cout << "\nEnd Screen Will be here...\n";

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

			_ShowEndScreen();
			//Login();

			break;
		}
		if (MainMenuOption != eExit && MainMenuOption != eManageUsers && MainMenuOption != eShowTransactionsMenu)
			_GoBackToMainMenu();

	}

public:
	static void ShowMainMenu()
	{
		system("cls");
		_ScreenHeader("Main Screen");
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
		_PerfromMainMenuOption((enMainMenuOptions)_ReadMainMenuOption());
	}
};

