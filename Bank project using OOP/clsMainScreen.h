#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
	enum enMainMenuOptions
	{
		ShowList = 1,
		Add,
		Delete,
		Update,
		Find,
		TransActions,
		ManageUsers,
		LogOut
	};

	static short ReadMainMenuOption()
	{
		cout << "Choose what do you want to do ? [1 to 8 ] : ";
		return clsInputValidate::ReadShortNumberBetween(1, 8);
	}

	static void _PerformMainMenuOption(enMainMenuOptions MainMenuOption)
	{
		do
		{
			ShowMainMenu();
			
			system("cls");
			switch (MainMenuOption)
			{
			case ShowList:
				
				break;
			case Add:
				
				break;
			case Delete:
				
				break;
			case Update:
				
				break;
			case Find:
				
				break;
			case TransActions:
				
				break;
			case ManageUsers:
				
				break;
			case LogOut:
				
				break;
			}
			/*if ((MainMenuOption != TransActions && MainMenuOption != ManageUsers && MainMenuOption != LogOut))*/
				//GoBackToMenu("\n\nPress any key to go back to main Menu.....");
		} while (true);
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
		_PerformMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
	}
};

