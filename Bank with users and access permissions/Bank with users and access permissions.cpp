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
	ShowList = 1, Add, Delete, Update, Find, TransActions, ManageUsers, LogOut
};

enum enManageUsersOptions
{
	eUsersList = 1, eAddUser, eDeleteUser, eUpdateUser, eFindUser, eMainMenu
};

enum enTransactionMenuOptions
{
	eDeposit = 1, eWithDraw, eTotalBalance, mainMenu
};
enum enTransactionType
{
	DepositType = 1, WithDrawType
};

enum enPermissions
{
	FullAccess = -1, ListAccess = 1, AddAccess = 2, DeleteAccess = 4, UpdateAccess = 8, FindAccess = 16, TransactionsAccess = 32
	, MangeUsersAccess = 64
};

struct stClientData
{
	string AccNumber = "", PinCode = "", Name = "", Phone = "";
	double AccBalance = 0;
};

struct stUsers
{
	string UserName = "", Password = "";
	short Permissions = 0;
};

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

string RecordToLine(stClientData Client, string Seperator = "#//#")
{
	string st = "";
	st += Client.AccNumber + Seperator;
	st += Client.PinCode + Seperator;
	st += Client.Name + Seperator;
	st += Client.Phone + Seperator;
	st += to_string(Client.AccBalance);
	return st;
}

stClientData LineToRecord(string Line, string Seperator = "#//#")
{
	stClientData Client;
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

void PrintClientCard(stClientData Client)
{
	cout << "Account Number : " << Client.AccNumber << endl;
	cout << "Pincode        : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Balance        : " << Client.AccBalance << endl;
}

vector <stClientData> DataFromFile(string FileName, string Seperator = "#//#")
{
	vector <stClientData> vAllClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
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

bool FindClient(stClientData& Client, string AccNumber, vector <stClientData>& vClients)
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

void UpdateFileData(vector <stClientData>& vClients, string FileName)
{
	fstream Myfile;
	Myfile.open(FileName, ios::out);
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

void PrintClientData(stClientData Client)
{
	cout << left
		<< "| " << setw(15) << Client.AccNumber
		<< "| " << setw(9) << Client.PinCode
		<< "| " << setw(23) << Client.Name
		<< "| " << setw(12) << Client.Phone
		<< "| " << setw(13) << Client.AccBalance
		<< endl;
}

void PrintClientsList(vector<stClientData>& vClients)
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

stClientData ReadClientData(vector <stClientData>& vClients)
{
	stClientData Client;
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

void AddNewClient(vector <stClientData>& vClients, string FileName)
{
	stClientData client = ReadClientData(vClients);
	AddDataLineToFile(FileName, RecordToLine(client));
	vClients.push_back(client);
	cout << "\nClient added successfully, ";
}

void AddClients(vector <stClientData>& vClients, string FileName)
{
	char addMore = 'y';
	while (tolower(addMore) == 'y')
	{
		system("cls");
		ScreenHeader("\tAdd New Clients Screen");
		cout << "Adding new client :\n";
		AddNewClient(vClients, FileName);
		cout << "do you want to add more clients ? [y] , [n] : ";
		cin >> addMore;
	}
}

//Delete

void DeleteClient(vector <stClientData>& vClients, string FileName)
{
	ScreenHeader("\tDelete Client Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClientData client;
	if (FindClient(client, AccNumber, vClients))
	{
		cout << "\nThe following are the client details :\n\n";
		PrintClientCard(client);
		if (ConfirmAction("\nAre you sure you want to delete this client ? y/n "))
		{
			vector <stClientData> vUpdatedClients;
			for (auto& C : vClients)
			{
				if (C.AccNumber != AccNumber)
					vUpdatedClients.push_back(C);
			}
			vClients = vUpdatedClients;
			UpdateFileData(vUpdatedClients, FileName);
			cout << "\nClient Deleted Successfully" << endl;
		}

	}
	else
	{
		cout << "\nClient with number (" + AccNumber + ") Not Found\n";
	}
}

//Update

stClientData UpdateClientData(string AccNumber)
{
	stClientData Client;
	Client.AccNumber = AccNumber;
	cout << "please enter cliet data : \n";
	Client.PinCode = ReadString("\nEnter Pincode ? ");
	Client.Name = ReadString("Enter Name ? ");
	Client.Phone = ReadString("Enter Phone ? ");
	Client.AccBalance = ReadPositiveNumber("Enter Acc BAlance ? ");
	return Client;
}

void UpdateClient(vector <stClientData>& vClients, string FileName)
{
	ScreenHeader("\tUpdate Client Info Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClientData client;
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
			UpdateFileData(vClients, FileName);
			cout << "\nClient Updated Successfully" << endl;
		}

	}
	else
	{
		cout << "\nClient with number (" + AccNumber + ") Not Found\n";
	}
}

//find

void FindClientResult(vector <stClientData>& vClients)
{
	ScreenHeader("\tFind Client Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClientData client;
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

void UpdateBalanceAfterTransaction(enTransactionType TransactionType, stClientData& client)
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

void MakeTransaction(vector<stClientData>& vClients, string FileName, enTransactionType TransactionType)
{
	if (TransactionType == DepositType)
		ScreenHeader("\tDeposit Screen");
	else
		ScreenHeader("\tWithDraw Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	stClientData client;
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
		UpdateFileData(vClients, FileName);
		cout << "\nDone Successfully , New Balance = " << client.AccBalance << endl;
	}

}

//total balances

void PrintClientBalance(stClientData Client)
{
	cout << left
		<< "| " << setw(18) << Client.AccNumber
		<< "| " << setw(33) << Client.Name
		<< "| " << setw(18) << Client.AccBalance
		<< endl;
}

void PrintBalancesList(vector<stClientData>& vClients)
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

void TransactionsMenu(vector <stClientData>& vClient, string FileName)
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
			MakeTransaction(vClient, FileName, enTransactionType::DepositType);
			break;
		case eWithDraw:
			MakeTransaction(vClient, FileName, enTransactionType::WithDrawType);
			break;
		case eTotalBalance:
			PrintBalancesList(vClient);
			break;
		}
		GoBackToMenu("\n\nPress any key to go back to Transactions Menu.....");
	} while (UserChoice != mainMenu);
}

// login screen 

stUsers LineToUser(string Line, string Seperator = "#//#")
{
	stUsers User;
	vector <string> vUser = SplitString(Line, Seperator);
	User.UserName = vUser[0];
	User.Password = vUser[1];
	User.Permissions = stoi(vUser[2]);
	return User;
}

vector <stUsers> GetUsers(string FileName, string Seperator = "#//#")
{
	vector <stUsers> vAllUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string line = "";
		while (getline(MyFile, line))
		{
			vAllUsers.push_back(LineToUser(line));
		}
		MyFile.close();
	}
	return vAllUsers;
}

bool FindUser(stUsers& User, string UserName, vector <stUsers>& vUsers)
{
	for (auto& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			User = U;
			return true;
		}
	}
	return false;
}

void ResetScreen(string Message)
{
	system("cls");
	ScreenHeader(Message);
}

stUsers ReadLoginData(stUsers& User)
{
	printf("Enter User Name ? ");
	getline(cin >> ws, User.UserName);
	printf("Enter Password ? ");
	getline(cin >> ws, User.Password);
	return User;
}

stUsers Login(vector <stUsers>& vUsers)
{
	ResetScreen("\t\tLogin Screen");
	stUsers User;
	stUsers Input;
	ReadLoginData(Input);
	FindUser(User, Input.UserName, vUsers);
	while (User.Password != Input.Password)
	{
		ResetScreen("\t\tLogin Screen");
		cout << "Invalid UserName/Password!\n";
		ReadLoginData(Input);
		FindUser(User, Input.UserName, vUsers);
	}
	return User;
}

bool HasPermission(stUsers User, enPermissions Permission)
{
	return (User.Permissions & Permission);
}

//manage menu

void ShowManageUsersMenu()
{
	system("cls");
	cout << "======================================================\n";
	cout << "\t\tManage Users Menu Screen\n";
	cout << "======================================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New User.\n";
	cout << "\t[3] Delete User.\n";
	cout << "\t[4] Update User Info.\n";
	cout << "\t[5] Find User.\n";
	cout << "\t[6] Main Menu.\n";
	cout << "======================================================\n";

}

void PrintUserData(stUsers User)
{
	cout << left
		<< "| " << setw(18) << User.UserName
		<< "| " << setw(18) << User.Password
		<< "| " << right << setw(3) << User.Permissions

		<< endl;
}

void PrintUsersList(vector<stUsers>& vUsers)
{
	cout << "\n\t\t\tUsers List(" << vUsers.size() << ") User(s)\n";
	cout << "________________________________________________________________________________\n"
		<< endl;
	cout << left
		<< setw(20) << "| User Name"
		<< setw(20) << "| Password"
		<< setw(20) << "| Permissions"
		<< endl;
	cout << "________________________________________________________________________________\n"
		<< endl;

	for (auto& i : vUsers)
	{
		PrintUserData(i);
	}
	cout << "________________________________________________________________________________\n"
		<< endl;
}

// Add user

short ReadUserPermissions()
{
	if (ConfirmAction("\nDo you want to give full access ? y/n ? "))
		return -1;
	short Permissions = 0;
	if (ConfirmAction("\nDo you want to give access to :\n\nShow Client List ? y/n ? "))
		Permissions |= enPermissions::ListAccess;
	if (ConfirmAction("Add new Client ?   y/n ? "))
		Permissions |= enPermissions::AddAccess;
	if (ConfirmAction("Delete Client ?    y/n ? "))
		Permissions |= enPermissions::DeleteAccess;
	if (ConfirmAction("Update Client ?    y/n ? "))
		Permissions |= enPermissions::UpdateAccess;
	if (ConfirmAction("Find Client ?      y/n ? "))
		Permissions |= enPermissions::FindAccess;
	if (ConfirmAction("Transactions ?     y/n ? "))
		Permissions |= enPermissions::TransactionsAccess;
	if (ConfirmAction("Manage Users ?     y/n ? "))
		Permissions |= enPermissions::MangeUsersAccess;
	return Permissions;
}

string RecordToLine(stUsers User, string Seperator = "#//#")
{
	string st = "";
	st += User.UserName + Seperator;
	st += User.Password + Seperator;
	st += to_string(User.Permissions);
	return st;
}

void AddNewUser(vector <stUsers>& vUsers)
{
	stUsers User;
	printf("\nEnter UserName ? ");
	getline(cin >> ws, User.UserName);
	while (FindUser(User, User.UserName, vUsers))
	{
		printf("\nUser Already Exist\n");
		printf("Enter UserName ? ");
		getline(cin >> ws, User.UserName);
	}
	printf("Enter Password ? ");
	getline(cin >> ws, User.Password);
	User.Permissions = ReadUserPermissions();
	AddDataLineToFile(UsersFile, RecordToLine(User));
	vUsers.push_back(User);
	cout << "\nUser added successfully, ";
}

void AddUsers(vector <stUsers>& vUsers)
{
	do
	{
		system("cls");
		ScreenHeader("\tAdd New Users Screen");
		cout << "Adding new client :\n";
		AddNewUser(vUsers);
	} while (ConfirmAction("do you want to add more Users ? [y] , [n] : "));
}

//Delete user

void PrintUserCard(stUsers User)
{
	cout << "User Name   : " << User.UserName << endl;
	cout << "Password    : " << User.Password << endl;
	cout << "Permissions : " << User.Permissions << endl;
}

void UpdateFileData(vector <stUsers>& vUsers)
{
	fstream Myfile;
	Myfile.open(UsersFile, ios::out);
	if (Myfile.is_open())
	{
		for (auto& U : vUsers)
		{
			Myfile << RecordToLine(U) << endl;
		}
		Myfile.close();
	}
}

void DeleteUser(vector <stUsers>& vUsers)
{
	ScreenHeader("\tDelete User Screen");
	string userName = ReadString("Please enter User Name ? ");
	stUsers User;
	if (FindUser(User, userName, vUsers))
	{
		cout << "\nThe following are the User details :\n\n";
		PrintUserCard(User);
		if (User.UserName == "Admin")
			printf("\nyou can not delete this user\n");
		else if (ConfirmAction("\nAre you sure you want to delete this User ? y/n "))
		{
			vector <stUsers> vUpdatedUsers;
			for (auto& U : vUsers)
			{
				if (U.UserName != userName)
					vUpdatedUsers.push_back(U);
			}
			vUsers = vUpdatedUsers;
			UpdateFileData(vUpdatedUsers);
			cout << "\nUser Deleted Successfully" << endl;
		}
	}
	else
	{
		cout << "\nUser (" + userName + ") Not Found\n";
	}
}

//Update user

stUsers UpdateUserData(string AccNumber)
{
	stUsers User;
	User.UserName = AccNumber;
	cout << "please enter User data : \n";
	User.Password = ReadString("\nEnter Password ? ");
	User.Permissions = ReadUserPermissions();
	return User;
}

void UpdateUser(vector <stUsers>& vUsers)
{
	ScreenHeader("\tUpdate User Info Screen");
	string userName = ReadString("Please enter User Name ? ");
	stUsers user;
	if (FindUser(user, userName, vUsers))
	{
		cout << "\nThe following are the user details :\n\n";
		PrintUserCard(user);
		if (ConfirmAction("\nAre you sure you want to update this user ? y/n "))
		{
			for (auto& U : vUsers)
			{
				if (U.UserName == userName) {

					U = UpdateUserData(userName);
					break;
				}
			}
			UpdateFileData(vUsers);
			cout << "\nUser Updated Successfully" << endl;
		}

	}
	else
	{
		cout << "\nUser (" + userName + ") Not Found\n";
	}
}

void ManageUsersMenu(vector <stUsers>& vUsers)
{
	enManageUsersOptions UserChoice = enManageUsersOptions::eMainMenu;
	do
	{
		system("cls");
		ShowManageUsersMenu();
		UserChoice = (enManageUsersOptions)ReadNumberInRange(1, 6, "Choose what do you want to do ? [1 to 6 ] : ");
		if (UserChoice == enManageUsersOptions::eMainMenu)
		{
			break;
		}
		system("cls");
		switch (UserChoice)
		{
		case eUsersList:
			PrintUsersList(vUsers);
			break;
		case eAddUser:
			AddUsers(vUsers);
			break;
		case eDeleteUser:
			DeleteUser(vUsers);
			break;
		case eUpdateUser:
			UpdateUser(vUsers);
			break;
		case eFindUser:
			break;
		}
		GoBackToMenu("\n\nPress any key to go back to Manage Users Menu.....");
	} while (UserChoice != eMainMenu);
}

void AccessDeniedMessage()
{
	ScreenHeader("Access Denied,\nyou don't have permission to do this,\nplease contact your Admin");
}

//main menu

void MainMenu(vector <stClientData>& vClients, vector <stUsers>& vUsers)
{
	stUsers loggedUser = Login(vUsers);
	enMainMenuOptions UserChoice;
	do
	{
		ShowMainMenu();
		UserChoice = (enMainMenuOptions)ReadNumberInRange(1, 8, "Choose what do you want to do ? [1 to 8 ] : ");
		system("cls");
		switch (UserChoice)
		{
		case ShowList:
			(HasPermission(loggedUser, ListAccess)) ? PrintClientsList(vClients)
				: AccessDeniedMessage();
			break;
		case Add:
			(HasPermission(loggedUser, ListAccess)) ? AddClients(vClients, ClientsFile)
				: AccessDeniedMessage();
			break;
		case Delete:
			(HasPermission(loggedUser, DeleteAccess)) ? DeleteClient(vClients, ClientsFile)
				: AccessDeniedMessage();
			break;
		case Update:
			(HasPermission(loggedUser, UpdateAccess)) ? UpdateClient(vClients, ClientsFile)
				: AccessDeniedMessage();
			break;
		case Find:
			(HasPermission(loggedUser, FindAccess)) ? FindClientResult(vClients)
				: AccessDeniedMessage();
			break;
		case TransActions:
			(HasPermission(loggedUser, TransactionsAccess)) ? TransactionsMenu(vClients, ClientsFile)
				: AccessDeniedMessage();
			break;
		case ManageUsers:
			(HasPermission(loggedUser, MangeUsersAccess)) ? ManageUsersMenu(vUsers)
				: AccessDeniedMessage();
			break;
		case LogOut:
			loggedUser = Login(vUsers);
			break;
		}
		if ((UserChoice != TransActions && UserChoice != ManageUsers && UserChoice != LogOut)
			|| (!HasPermission(loggedUser, MangeUsersAccess)
				&& !HasPermission(loggedUser, TransactionsAccess))
			)
			GoBackToMenu("\n\nPress any key to go back to main Menu.....");
	} while (true);
}


void StartProgram()
{
	vector <stClientData> vClients = DataFromFile(ClientsFile);
	vector <stUsers> vUsers = GetUsers(UsersFile);
	MainMenu(vClients, vUsers);
}

int main()
{
	StartProgram();
	system("pause>0");
}


