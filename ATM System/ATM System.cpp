#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string ClientsFile = "clients.txt";
const string UsersFile = "Users.txt";

enum enMainMenuOptions
{
	ShowList = 1, Add, Delete, Update, Find, TransActions, LogOut
};


enum enTransactionMenuOptions
{
	eDeposit = 1, eWithDraw, eTotalBalance, mainMenu
};
enum enTransactionType
{
	DepositType = 1, WithDrawType
};


struct stClient
{
	string AccNumber = "", PinCode = "", Name = "", Phone = "";
	double AccBalance = 0;
};


stClient loggedClient;


double ReadPositiveNumber(string message)
{
	double Number = 0;
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

void PrintClientCard(stClient Client)
{
	cout << "Account Number : " << Client.AccNumber << endl;
	cout << "Pincode        : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Balance        : " << Client.AccBalance << endl;
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

}

void GoBackToMenu(string message)
{
	cout << message;
	system("pause>0");
}

//list

void PrintClientData(stClient Client)
{
	cout << left
		<< "| " << setw(15) << Client.AccNumber
		<< "| " << setw(9) << Client.PinCode
		<< "| " << setw(23) << Client.Name
		<< "| " << setw(12) << Client.Phone
		<< "| " << setw(13) << Client.AccBalance
		<< endl;
}

void PrintClientsList(vector<stClient>& vClients)
{
	cout << "\n\t\t\tClients List(" << vClients.size() << ") client(s)\n";
	cout << "________________________________________________________________________________\n"
		<< endl;
	cout << left
		<< setw(17) << "| Account Number"
		<< setw(11) << "| Pin Code"
		<< setw(25) << "| Client Name"
		<< setw(14) << "| Phone"
		<< setw(15) << "| Balance"
		<< endl;
	cout << "________________________________________________________________________________\n"
		<< endl;

	for (auto& i : vClients)
	{
		PrintClientData(i);
	}
	cout << "________________________________________________________________________________\n"
		<< endl;
}

//Add

stClient ReadClientData(vector <stClient>& vClients)
{
	stClient Client;
	Client.AccNumber = ReadString("\nEnter Account Number ? ");
	while (FindClient(Client, Client.AccNumber, vClients))
	{
		Client.AccNumber = ReadString("\nClient with [" + Client.AccNumber + "] already exists, Enter another Account Number ? ");
	}
	Client.PinCode = ReadString("Enter Pincode ? ");
	Client.Name = ReadString("Enter Name ? ");
	Client.Phone = ReadString("Enter Phone ? ");
	Client.AccBalance = ReadPositiveNumber("Enter Acc Balance ? ");
	return Client;
}

void AddNewClient(vector <stClient>& vClients)
{
	stClient client = ReadClientData(vClients);
	AddDataLineToFile(ClientsFile, RecordToLine(client));
	vClients.push_back(client);
	cout << "\nClient added successfully, ";
}

void AddClients(vector <stClient>& vClients)
{
	char addMore = 'y';
	while (tolower(addMore) == 'y')
	{
		system("cls");
		ScreenHeader("\tAdd New Clients Screen");
		cout << "Adding new client :\n";
		AddNewClient(vClients);
		cout << "do you want to add more clients ? [y] , [n] : ";
		cin >> addMore;
	}
}

//Delete

void DeleteClient(vector <stClient>& vClients)
{
	ScreenHeader("\tDelete Client Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClient client;
	if (FindClient(client, AccNumber, vClients))
	{
		cout << "\nThe following are the client details :\n\n";
		PrintClientCard(client);
		if (ConfirmAction("\nAre you sure you want to delete this client ? y/n "))
		{
			vector <stClient> vUpdatedClients;
			for (auto& C : vClients)
			{
				if (C.AccNumber != AccNumber)
					vUpdatedClients.push_back(C);
			}
			vClients = vUpdatedClients;
			UpdateFileData(vUpdatedClients);
			cout << "\nClient Deleted Successfully" << endl;
		}

	}
	else
	{
		cout << "\nClient with number (" + AccNumber + ") Not Found\n";
	}
}

//Update

stClient UpdateClientData(string AccNumber)
{
	stClient Client;
	Client.AccNumber = AccNumber;
	cout << "please enter client data : \n";
	Client.PinCode = ReadString("\nEnter Pincode ? ");
	Client.Name = ReadString("Enter Name ? ");
	Client.Phone = ReadString("Enter Phone ? ");
	Client.AccBalance = ReadPositiveNumber("Enter Acc BAlance ? ");
	return Client;
}

void UpdateClient(vector <stClient>& vClients)
{
	ScreenHeader("\tUpdate Client Info Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClient client;
	if (FindClient(client, AccNumber, vClients))
	{
		cout << "\nThe following are the client details :\n\n";
		PrintClientCard(client);
		if (ConfirmAction("\nAre you sure you want to update this client ? y/n "))
		{
			for (auto& C : vClients)
			{
				if (C.AccNumber == AccNumber) {

					C = UpdateClientData(AccNumber);
					break;
				}
			}
			UpdateFileData(vClients);
			cout << "\nClient Updated Successfully" << endl;
		}

	}
	else
	{
		cout << "\nClient with number (" + AccNumber + ") Not Found\n";
	}
}

//find

void FindClientResult(vector <stClient>& vClients)
{
	ScreenHeader("\tFind Client Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClient client;
	if (FindClient(client, AccNumber, vClients))
	{
		cout << "\nThe following are the client details :\n\n";
		PrintClientCard(client);
	}
	else
	{
		cout << "\nClient with number (" + AccNumber + ") Not Found\n";
	}
}

//transactions

void ShowTransactionsMenu()
{
	system("cls");
	cout << "======================================================\n";
	cout << "\t\tTransactions Menu Screen\n";
	cout << "======================================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "======================================================\n";
}

// deposit & withdraw

void UpdateBalanceAfterTransaction(enTransactionType TransactionType, stClient& client)
{
	double addedAmount = 0;
	if (TransactionType == DepositType)
	{
		addedAmount = ReadPositiveNumber("\nPlease enter Deposit Amount ? ");
		client.AccBalance += addedAmount;
	}
	else
	{
		addedAmount = ReadPositiveNumber("\nPlease enter WithDraw Amount ? ");
		while (addedAmount > client.AccBalance)
		{
			cout << "\nAmount Exceeds the balance, you can Withdraw up to : " << client.AccBalance << endl;
			addedAmount = ReadPositiveNumber("Please enter another Amount ? ");
		}
		client.AccBalance -= addedAmount;
	}
}

void MakeTransaction(vector<stClient>& vClients, enTransactionType TransactionType)
{
	if (TransactionType == DepositType)
		ScreenHeader("\tDeposit Screen");
	else
		ScreenHeader("\tWithDraw Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClient client;
	while (!FindClient(client, AccNumber, vClients))
	{
		cout << "\nClient with Account number (" + AccNumber + ") does not exist.\n";
		AccNumber = ReadString("\nPlease enter Account Number ? ");
	}
	cout << "\nThe following are the client details :\n\n";
	PrintClientCard(client);
	UpdateBalanceAfterTransaction(TransactionType, client);
	if (ConfirmAction("\n\nAre you sure you want to perform this transaction ? y/n ? "))
	{
		for (auto& C : vClients)
		{
			if (C.AccNumber == AccNumber)
			{
				C = client;
				break;
			}
		}
		UpdateFileData(vClients);
		cout << "\nDone Successfully , New Balance = " << client.AccBalance << endl;
	}

}

//total balances

void PrintClientBalance(stClient Client)
{
	cout << left
		<< "| " << setw(18) << Client.AccNumber
		<< "| " << setw(33) << Client.Name
		<< "| " << setw(18) << Client.AccBalance
		<< endl;
}

void PrintBalancesList(vector<stClient>& vClients)
{
	double Total = 0;
	cout << "\n\t\t\tBalances List(" << vClients.size() << ") client(s)\n";
	cout << "________________________________________________________________________________\n"
		<< endl;
	cout << left
		<< setw(20) << "| Account Number"
		<< setw(35) << "| Client Name"
		<< setw(20) << "| Balance"
		<< endl;
	cout << "________________________________________________________________________________\n"
		<< endl;

	for (auto& i : vClients)
	{
		PrintClientBalance(i);
		Total += i.AccBalance;
	}
	cout << "________________________________________________________________________________\n"
		<< endl;
	cout << "\t\t\t" << "Total Balances = " << Total << "\n\n";
}

void TransactionsMenu(vector <stClient>& vClient)
{
	enTransactionMenuOptions UserChoice = enTransactionMenuOptions::mainMenu;
	do
	{
		ShowTransactionsMenu();
		UserChoice = (enTransactionMenuOptions)ReadNumberInRange(1, 4, "Choose what do you want to do ? [1 to 4 ] : ");
		if (UserChoice == enTransactionMenuOptions::mainMenu)
		{
			break;
		}
		system("cls");
		switch (UserChoice)
		{
		case eDeposit:
			MakeTransaction(vClient, enTransactionType::DepositType);
			break;
		case eWithDraw:
			MakeTransaction(vClient, enTransactionType::WithDrawType);
			break;
		case eTotalBalance:
			PrintBalancesList(vClient);
			break;
		}
		GoBackToMenu("\n\nPress any key to go back to Transactions Menu.....");
	} while (UserChoice != mainMenu);
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
	printf("Enter pin code ? ");
	getline(cin >> ws, Client.PinCode);
	return Client;
}

stClient Login(vector <stClient>& vClients)
{
	ResetScreen("\t\tLogin Screen");
	stClient Client;
	stClient Input;
	do
	{
		ResetScreen("\t\tLogin Screen");
		if (Client.PinCode != Input.PinCode)
			cout << "Invalid UserName/Password!\n";
		ReadLoginData(Input);
		FindClient(Client, Input.AccNumber, vClients);
	} while (Client.PinCode != Input.PinCode);
	return Client;
}



//main menu

void MainMenu(vector <stClient>& vClients)
{
	loggedClient = Login(vClients);
	enMainMenuOptions UserChoice;
	do
	{
		ShowMainMenu();
		UserChoice = (enMainMenuOptions)ReadNumberInRange(1, 8, "Choose what do you want to do ? [1 to 8 ] : ");
		system("cls");
		switch (UserChoice)
		{
		case ShowList:
			PrintClientsList(vClients);

			break;
		case Add:
			AddClients(vClients);

			break;
		case Delete:
			DeleteClient(vClients);

			break;
		case Update:
			UpdateClient(vClients);

			break;
		case Find:
			FindClientResult(vClients);

			break;
		case TransActions:
			TransactionsMenu(vClients);
			break;
		case LogOut:
			loggedClient = Login(vClients);
			break;
		}
		if ((UserChoice != TransActions && UserChoice != LogOut))
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


