#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyScreen.h"
class clsCurrenyExchangeMainScreen :protected clsScreen
{

	enum _enCurrencyExchangeMenu
	{
		eListCurrencies = 1, eFindCurrency, eUpdateRate, eCurrencyCalculator, eMainMenu
	};

	static short _ReadManageUsersMenuOption()
	{
		cout << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static void _CurrencyExchangeMenu()
	{
		system("cls");
		_ScreenHeader("Currency Exchange Main Screen", 2);
		cout << "======================================================\n";
		cout << "\t\tCurrency Exchange Menu\n";
		cout << "======================================================\n";
		cout << "\t[1] List Currencies.\n";
		cout << "\t[2] Find Currency.\n";
		cout << "\t[3] Update Rate.\n";
		cout << "\t[4] Currency Calculator.\n";
		cout << "\t[5] Main Menu.\n";
		cout << "======================================================\n";
	}

	static void _GoBackToCurrencyExchangeMenu()
	{
		cout << "\n\nPress any key to go back to Currency Exchange Menu...";
		system("pause>0");

	}

	static void _ShowListCurrenciesScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrencyScreen::ShowUpdateCurrencyScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		cout << "Currency Calculator" << endl;
	}

	static void _PerformCurrencyExchangeMenuOption(_enCurrencyExchangeMenu CurrencyExchangeMenuOption)
	{
		system("cls");
		switch (CurrencyExchangeMenuOption)
		{
		case _enCurrencyExchangeMenu::eListCurrencies:
			_ShowListCurrenciesScreen();
			break;
		case _enCurrencyExchangeMenu::eFindCurrency:
			_ShowFindCurrencyScreen();
			break;
		case _enCurrencyExchangeMenu::eUpdateRate:
			_ShowUpdateRateScreen();
			break;
		case _enCurrencyExchangeMenu::eCurrencyCalculator:
			_ShowCurrencyCalculatorScreen();
			break;
		}
		if (CurrencyExchangeMenuOption != eMainMenu)
			_GoBackToCurrencyExchangeMenu();
	}

public:
	static void ShowCurrencyExchangeMainScreen()
	{
		_enCurrencyExchangeMenu CurrencyExchangeMenuOption;
		do
		{
			_CurrencyExchangeMenu();
			_PerformCurrencyExchangeMenuOption(CurrencyExchangeMenuOption = (_enCurrencyExchangeMenu)_ReadManageUsersMenuOption());
		} while (CurrencyExchangeMenuOption != eMainMenu);
	}
};

