#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientsFile = "clients.txt";

enum enMainMenuOptions
{
	eQuickWithdraw = 1, eNormalWithdraw, eMainDeposit, eCheckBalnce, LogOut
};

enum enQuickTransactionMenu
{
	eFifty = 1, eOneHundred, eTwoHundred, eFourHundred, eSixHundred, eEightHundred, eOneThousand, eTwoThousand, Exit
};
enum enTransactionType
{
	QuickWithDrawType = 1, NormalWithDrawType, DepositType
};

struct stClient
{
	string AccNumber = "", PinCode = "", Name = "", Phone = "";
	double AccBalance = 0;
};

stClient loggedClient;

int ReadPositiveNumber(string message)
{
	int Number = 0;
	do
	{
		cout << message;
		cin >> Number;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "invalid Number please enter valid Number ?" << endl;
			cin >> Number;
		}
	} while (Number <= 0);

	return Number;
}

short ReadNumberInRange(short from, short to, string message = "")
{
	short Num;
	cout << message;
	cin >> Num;
	while (cin.fail() || (Num > to || Num < from))
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "invalid Number please enter valid Number ? ";
		cin >> Num;
	}
	return Num;
}

string ReadString(string message)
{
	string st;
	cout << message;
	getline(cin >> ws, st, '\n');
	return st;
}

vector<string> SplitString(string st, string delimiter = "#//#")
{
	vector<string> split;
	string sWord = "";
	short pos = 0;
	while ((pos = st.find(delimiter)) != string::npos)
	{
		sWord = st.substr(0, pos);
		if (sWord != "")
			split.push_back(sWord);
		st.erase(0, pos + delimiter.length());
	}
	if (st != "")
		split.push_back(st);
	return split;
}

string RecordToLine(stClient Client, string Seperator = "#//#")
{
	string st = "";
	st += Client.AccNumber + Seperator;
	st += Client.PinCode + Seperator;
	st += Client.Name + Seperator;
	st += Client.Phone + Seperator;
	st += to_string(Client.AccBalance);
	return st;
}

stClient LineToRecord(string Line, string Seperator = "#//#")
{
	stClient Client;
	vector <string> vClient = SplitString(Line, Seperator);
	Client.AccNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AccBalance = stod(vClient[4]);
	return Client;
}

void AddDataLineToFile(string FileName, string DataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::app);
	if (MyFile.is_open())
	{
		MyFile << DataLine << endl;
		MyFile.close();
	}
}

vector <stClient> GetClients(string Seperator = "#//#")
{
	vector <stClient> vAllClients;
	fstream MyFile;
	MyFile.open(ClientsFile, ios::in);
	if (MyFile.is_open())
	{
		string line = "";
		while (getline(MyFile, line))
		{
			vAllClients.push_back(LineToRecord(line));
		}
		MyFile.close();
	}
	return vAllClients;
}

bool FindClient(stClient& Client, string AccNumber, vector <stClient>& vClients)
{
	for (auto& C : vClients)
	{
		if (C.AccNumber == AccNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool ConfirmAction(string message)
{
	cout << message;
	char confirmed = ' ';
	cin >> confirmed;
	return tolower(confirmed) == 'y';
}

void UpdateFileData(vector <stClient>& vClients)
{
	fstream Myfile;
	Myfile.open(ClientsFile, ios::out);
	if (Myfile.is_open())
	{
		for (auto& C : vClients)
		{
			Myfile << RecordToLine(C) << endl;
		}
		Myfile.close();
	}
}

void ScreenHeader(string Title)
{
	cout << "--------------------------------------------\n";
	cout << Title << endl;
	cout << "--------------------------------------------\n";
}

void ShowMainMenu()
{
	system("cls");
	cout << "======================================================\n";
	cout << "\t\tATM Main Menu Screen\n";
	cout << "======================================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "======================================================\n";

}

void GoBackToMenu(string message)
{
	cout << message;
	system("pause>0");
}

//Update

void UpdateClient(vector <stClient>& vClients)
{

	for (auto& C : vClients)
	{
		if (C.AccNumber == loggedClient.AccNumber) {

			C = loggedClient;
			break;
		}
	}
	UpdateFileData(vClients);
}



//transactions

void ShowQuickTransactionsMenu()
{
	system("cls");
	ScreenHeader("\t\tQuick Withdraw");
	printf("\t[1] %-4d", 50);
	printf("\t[2] %-4d\n", 100);
	printf("\t[3] %-4d", 200);
	printf("\t[4] %-4d\n", 400);
	printf("\t[5] %-4d", 600);
	printf("\t[6] %-4d\n", 800);
	printf("\t[7] %-4d", 1000);
	printf("\t[8] %-4d\n", 2000);
	printf("\t[9] Exit\n");
	cout << "======================================================\n";
}

// deposit & withdraw

bool ValidTransaction(int AddAmount)
{
	return(AddAmount % 50 == 0);
}

void TransactionBeforeConfirm(enTransactionType TransactionType, stClient& Client)
{
	int addedAmount = 0;
	if (TransactionType == DepositType)
	{
		do
		{
			addedAmount = ReadPositiveNumber("\nPlease enter Amount multiple of 50's ? ");
		} while (!ValidTransaction(addedAmount));
		Client.AccBalance += addedAmount;
	}
	else
	{
		do
		{
			if (addedAmount > Client.AccBalance)
				cout << "\nAmount Exceeds the balance, you can Withdraw up to : " << Client.AccBalance << endl;
			addedAmount = ReadPositiveNumber("Please enter Amount multiple of 50's ? ");
		} while (addedAmount > Client.AccBalance || !ValidTransaction(addedAmount));

		Client.AccBalance -= addedAmount;
	}
}

void MakeTransaction(vector<stClient>& vClients, enTransactionType TransactionType)
{
	stClient tempClient;
	tempClient.AccBalance = loggedClient.AccBalance;

	if (TransactionType == DepositType)
		ScreenHeader("\t\tDeposit Screen");
	else if (TransactionType == NormalWithDrawType)
		ScreenHeader("\t  Normal Withdraw Screen");
	TransactionBeforeConfirm(TransactionType, tempClient);
	if (ConfirmAction("are you sure you want to perform this transaction ? y/n ? "))
	{
		loggedClient.AccBalance = tempClient.AccBalance;
		UpdateClient(vClients);
		cout << "\nDone Successfully , New Balance = " << loggedClient.AccBalance << endl;
	}

}

//total balances

short GetQuickWithdrawValue(enQuickTransactionMenu Choice)
{
	if (Choice == Exit)
		return 0;
	switch (Choice)
	{
	case eFifty:
		return 50;
	case eOneHundred:
		return 100;
	case eTwoHundred:
		return 200;
	case eFourHundred:
		return 400;
	case eSixHundred:
		return 600;
	case eEightHundred:
		return 800;
	case eOneThousand:
		return 1000;
	case eTwoThousand:
		return 2000;
	}
}

void QuickTransactionsMenu(vector <stClient>& vClients)
{
	enQuickTransactionMenu UserChoice = enQuickTransactionMenu::Exit;
	short withdrawAmount = 0;
	do
	{
		system("cls");
		ShowQuickTransactionsMenu();
		printf("\nYour balance is %.2f ", loggedClient.AccBalance);
		UserChoice = (enQuickTransactionMenu)ReadNumberInRange(1, 9, "Choose what to Withdraw from [1 to 8 ] : ");
		if (UserChoice == Exit)
			return;
		withdrawAmount = GetQuickWithdrawValue(UserChoice);
		if (withdrawAmount > loggedClient.AccBalance)
		{
			cout << "\n\nThe amount exceeds balance, make another choice.\n";
			GoBackToMenu("\npress any key to continue...");
		}
	} while (withdrawAmount > loggedClient.AccBalance);
	if (ConfirmAction("\n\nAre you sure you want to perform this transaction ? y/n ? "))
	{
		loggedClient.AccBalance -= withdrawAmount;
		UpdateClient(vClients);
		cout << "\nDone Successfully , New Balance = " << loggedClient.AccBalance << endl;
	}
}

// login screen 

void ResetScreen(string Message)
{
	system("cls");
	ScreenHeader(Message);
}

stClient ReadLoginData(stClient& Client)
{
	printf("Enter Account Number ? ");
	getline(cin >> ws, Client.AccNumber);
	printf("Enter pin ? ");
	getline(cin >> ws, Client.PinCode);
	return Client;
}

bool IsValidLogin(stClient& Client, vector <stClient>& vClients)
{
	return(FindClient(loggedClient, Client.AccNumber, vClients) && loggedClient.PinCode == Client.PinCode);
}

void Login(vector <stClient>& vClients)
{
	stClient TempClient;
	bool LoginFailed = false;
	do
	{
		ResetScreen("\t\tLogin Screen");
		if (LoginFailed)
			cout << "Invalid Account Number/Pin!\n";
		ReadLoginData(TempClient);
	} while (LoginFailed = !IsValidLogin(TempClient, vClients));
}

// balance

void CheckBalance()
{
	ScreenHeader("\t\tCheck Balance Screen");
	printf("Your Balance is %.2f\n", loggedClient.AccBalance);
}

//main menu

void MainMenu(vector <stClient>& vClients)
{
	Login(vClients);
	enMainMenuOptions UserChoice;
	do
	{
		ShowMainMenu();
		UserChoice = (enMainMenuOptions)ReadNumberInRange(1, 5, "Choose what do you want to do ? [1 to 5 ] : ");
		system("cls");
		switch (UserChoice)
		{
		case eQuickWithdraw:
			QuickTransactionsMenu(vClients);
			break;
		case eNormalWithdraw:
			MakeTransaction(vClients, NormalWithDrawType);
			break;
		case eMainDeposit:
			MakeTransaction(vClients, DepositType);
			break;
		case eCheckBalnce:
			CheckBalance();
			break;
		case LogOut:
			Login(vClients);
			break;
		}
		if ((UserChoice != LogOut))
			GoBackToMenu("\n\nPress any key to go back to main Menu.....");
	} while (true);
}

void StartProgram()
{
	vector <stClient> vClients = GetClients();
	MainMenu(vClients);
}

int main()
{
	StartProgram();
	system("pause>0");
}


