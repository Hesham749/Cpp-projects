#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"
class clsTransferScreen :protected clsScreen
{
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

	static string _ReadAccountNumber(string Message = "")
	{
		string AccountNumber;
		while (!clsBankClient::IsClientExist(AccountNumber = clsInputValidate::ReadString(Message)))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		}
		return AccountNumber;
	}
public:
	static void ShowTransferScreen()
	{
		_ScreenHeader("Transfer Screen", 2);
		clsBankClient FromClient = clsBankClient::Find(_ReadAccountNumber("Please enter account number to transfer from : "));
		_PrintClient(FromClient);
		clsBankClient ToClient = clsBankClient::Find(_ReadAccountNumber("Please enter account number to transfer To : "));
		_PrintClient(ToClient);

		double Amount = 0;
		cout << "\nPlease enter Transfer amount? ";
		while (FromClient.AccountBalance < (Amount = clsInputValidate::ReadDblNumber()))
		{
			cout << "\nAmount Exceeded the Available Balance, Enter another amount ? ";
		}
		if (clsUtil::ConfirmAction("\nAre you sure you want to perform this Operation? "))
		{
			if (FromClient.Transfer(ToClient, Amount))
			{
				cout << "\nTransfer Done Successfully\n";
				_PrintClient(FromClient);
				_PrintClient(ToClient);
			}
			else
			{
				cout << "\nTransfer Failed" << endl;
			}

		}
		else
		{
			cout << "\nOperation was canceled.\n";
		}

	}
};

