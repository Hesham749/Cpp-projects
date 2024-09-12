#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

class clsDeleteClientScreen :protected clsScreen
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
	static void ShowDeleteClientScreen()
	{

		_ScreenHeader("Delete Client Screen", 2);

		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		while (!clsBankClient::IsClientExist(AccountNumber = clsInputValidate::ReadString()))
		{
			cout << "\nAccount number is not found, choose another one: ";
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		if (clsUtil::ConfirmAction("\nAre you sure you want to delete this client y/n? "))
		{


			if (Client1.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client1);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}
	}
};

