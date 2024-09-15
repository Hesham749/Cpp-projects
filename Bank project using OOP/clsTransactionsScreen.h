#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"
class clsTransactionsScreen :protected clsScreen
{
	enum enTransactionMenuOptions
	{
		Deposit = 1, WithDraw, TotalBalance, Transfer, TransferLog, MainMenu
	};

	static short _ReadTransactionsMenuOption()
	{
		cout << "Choose what do you want to do? [1 to 6]? ";
		return clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
	}

	static  void _GoBackToTransactionsMenu()
	{
		cout << "\nPress any key to go back to Transactions Menu...\n";
		system("pause>0");
		ShowTransactionsMenu();
	}

	static void _ShowDepositScreen()
	{
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithDrawScreen()
	{
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalanceScreen()
	{
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransferScreen::ShowTransferScreen();
	}

	static void _PerfromTransactionsMenuOption(enTransactionMenuOptions TransactionsMenuOption)
	{
		system("cls");
		switch (TransactionsMenuOption)
		{
		case enTransactionMenuOptions::Deposit:
			_ShowDepositScreen();
			break;
		case enTransactionMenuOptions::WithDraw:
			_ShowWithDrawScreen();
			break;
		case enTransactionMenuOptions::TotalBalance:
			_ShowTotalBalanceScreen();
			break;
		case enTransactionMenuOptions::Transfer:
			_ShowTransferScreen();
			break;
		case enTransactionMenuOptions::TransferLog:
			clsTransferLogScreen::ShowTransferLogScreen();
			break;
		}

		if (TransactionsMenuOption != MainMenu)
			_GoBackToTransactionsMenu();
	}

public:
	static void ShowTransactionsMenu()
	{
		system("cls");
		("Transactions Screen", 2);
		cout << "======================================================\n";
		cout << "\t\tTransactions Menu Screen\n";
		cout << "======================================================\n";
		cout << "\t[1] Deposit.\n";
		cout << "\t[2] Withdraw.\n";
		cout << "\t[3] Total Balances.\n";
		cout << "\t[4] Transfer.\n";
		cout << "\t[5] Transfer Log.\n";
		cout << "\t[6] Main Menu.\n";
		cout << "======================================================\n";
		_PerfromTransactionsMenuOption((enTransactionMenuOptions)_ReadTransactionsMenuOption());
	}
};

