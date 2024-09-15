#pragma once
#include <fstream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>
class clsTransferLogScreen :protected clsScreen
{
	static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
	{

		cout << "| " << setw(23) << left << TransferLogRecord.DateTime;
		cout << "| " << setw(8) << left << TransferLogRecord.FromClient;
		cout << "| " << setw(8) << left << TransferLogRecord.ToClient;
		cout << "| " << setw(8) << left << TransferLogRecord.Amount;
		cout << "| " << setw(10) << left << TransferLogRecord.FromBalance;
		cout << "| " << setw(10) << left << TransferLogRecord.ToBalance;
		cout << "| " << setw(8) << left << TransferLogRecord.User;


	}

public:

	static void ShowTransferLogScreen()
	{


		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = clsBankClient::GetTransferLogsList();

		string Title = "Transfer Log List Screen";
		string SubTitle = "    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

		_ScreenHeader(Title, 2, SubTitle);

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acc";
		cout << "| " << left << setw(8) << "d.Acc";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vTransferLogRecord.size() == 0)
			cout << "\t\tNo Transfers Available In the System!";
		else

			for (clsBankClient::stTransferLogRecord& Record : vTransferLogRecord)
			{

				PrintTransferLogRecordLine(Record);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_________________________________________\n" << endl;

	}

};

