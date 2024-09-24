#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
class clsDepositScreen :protected clsScreen
{
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

public:

	static void ShowDepositScreen()
	{
		_ScreenHeader("Deposit Screen", 2);

		string AccountNumber = "";
		while (!clsBankClient::IsClientExist(AccountNumber = clsInputValidate::ReadString("\nPlease enter AccountNumber ? ")))
		{
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		double Amount = 0;
		cout << "\nPlease enter deposit amount? ";
		Amount = clsInputValidate::ReadNumber <double>();


		if (clsUtil::ConfirmAction("\nAre you sure you want to perform this transaction? "))
		{
			Client1.Deposit(Amount);
			cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client1.AccountBalance;

		}
		else
		{
			cout << "\nOperation was canceled.\n";
		}

	}


};

