#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
class clsTotalBalancesScreen : protected clsScreen
{

	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:
	static void ShowTotalBalancesScreen()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "  Balances List Screen";
		string SubTitle = "    (" + to_string(vClients.size()) + ") Client(s).";

		_ScreenHeader(Title, 2, SubTitle);

		cout << "\n_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << "\n_______________________________________________________";
		cout << "__________________________\n" << endl;

		double TotalBalances = clsBankClient::GetTotalBalances();

		if (vClients.size() == 0)
			cout << "No Clients Available In the System!";
		else

			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordBalanceLine(Client);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(8) << left << "" << "  \t   Total Balances = " << TotalBalances << endl;
		cout << setw(8) << left << "" << "  ( " << clsUtil::NumberToText(TotalBalances) << ")\n";
	}
};

