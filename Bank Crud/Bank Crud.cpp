#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const string fileNmae = "clients.txt";

enum MainMenuOptions
{
	ShowList = 1, Add, Delete, Update, Find, Exit
};

struct strClientData
{
	string AccNumber = "", PinCode = "", Name = "", Phone = "";
	double AccBalance = 0;
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

string RecordToLine(strClientData Client, string Seperator = "#//#")
{
	string st = "";
	st += Client.AccNumber + Seperator;
	st += Client.PinCode + Seperator;
	st += Client.Name + Seperator;
	st += Client.Phone + Seperator;
	st += to_string(Client.AccBalance);
	return st;
}

strClientData LineToRecord(string Line, string Seperator = "#//#")
{
	strClientData Client;
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

void PrintClientCard(strClientData Client)
{
	cout << "Account Number : " << Client.AccNumber << endl;
	cout << "Pincode        : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Balance        : " << Client.AccBalance << endl;
}

vector <strClientData> DataFromFile(string FileName, string Seperator = "#//#")
{
	vector <strClientData> vAllClients;
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

bool FindClient(strClientData& Client, string AccNumber, vector <strClientData>& vClients)
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

void UpdateFileData(vector <strClientData>& vClients, string FileName)
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
	cout << "\t" + Title << endl;
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
	cout << "\t[6] Exit.\n";
	cout << "======================================================\n";

}

//list

void PrintClientData(strClientData Client)
{
	cout << left
		<< "| " << setw(15) << Client.AccNumber
		<< "| " << setw(9) << Client.PinCode
		<< "| " << setw(23) << Client.Name
		<< "| " << setw(12) << Client.Phone
		<< "| " << setw(13) << Client.AccBalance
		<< endl;
}

void PrintClientsList(vector<strClientData>& vClients)
{
	cout << "\n\t\t\tclient list(" << vClients.size() << ") client(s)\n";
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

strClientData ReadClientData(vector <strClientData>& vClients)
{
	strClientData Client;
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

void AddNewClient(vector <strClientData>& vClients, string FileName)
{
	strClientData client = ReadClientData(vClients);
	AddDataLineToFile(FileName, RecordToLine(client));
	vClients.push_back(client);
	cout << "\nClient added successfully, ";
}

void AddClients(vector <strClientData>& vClients, string FileName)
{
	char addMore = 'y';
	while (tolower(addMore) == 'y')
	{
		system("cls");
		ScreenHeader("Add New Clients Screen");
		cout << "Adding new client :\n";
		AddNewClient(vClients, FileName);
		cout << "do you want to add more clients ? [y] , [n] : ";
		cin >> addMore;
	}
}

//Delete

void DeleteClient(vector <strClientData>& vClients, string FileName)
{
	ScreenHeader("Delete Client Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	strClientData client;
	if (FindClient(client, AccNumber, vClients))
	{
		cout << "\nThe following are the client details :\n\n";
		PrintClientCard(client);
		if (ConfirmAction("\nAre you sure you want to delete this client ? y/n "))
		{
			vector <strClientData> vUpdatedClients;
			for (auto& C : vClients)
			{
				if (C.AccNumber != AccNumber)
					vUpdatedClients.push_back(C);
			}
			vClients = vUpdatedClients;
			UpdateFileData(vUpdatedClients, FileName);
			cout << "\nClient Deleted Succeffuly" << endl;
		}

	}
	else
	{
		cout << "\nClient with number (" + AccNumber + ") Not Found\n";
	}
}

//Update

strClientData UpdateClientData(string AccNumber)
{
	strClientData Client;
	Client.AccNumber = AccNumber;
	cout << "please enter client data : \n";
	Client.PinCode = ReadString("\nEnter Pincode ? ");
	Client.Name = ReadString("Enter Name ? ");
	Client.Phone = ReadString("Enter Phone ? ");
	Client.AccBalance = ReadPositiveNumber("Enter Acc BAlance ? ");
	return Client;
}

void UpdateClient(vector <strClientData>& vClients, string FileName)
{
	ScreenHeader("Update Client Info Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	strClientData client;
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
			cout << "\nClient Updated Succeffuly" << endl;
		}

	}
	else
	{
		cout << "\nClient with number (" + AccNumber + ") Not Found\n";
	}
}

//find

void FindClientResult(vector <strClientData>& vClients)
{
	ScreenHeader("Find Client Screen");
	string AccNumber = ReadString("Please enter Account Number ? ");
	strClientData client;
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

void StartProgram(string FileName)
{
	vector <strClientData> vClients = DataFromFile(FileName);
	MainMenuOptions UserChoice = MainMenuOptions::Exit;
	do
	{
		ShowMainMenu();
		UserChoice = (MainMenuOptions)ReadNumberInRange(1, 6, "Choose what do you want to do ? [1 to 6 ] : ");
		system("cls");
		if (UserChoice == MainMenuOptions::Exit)
		{
			ScreenHeader("Program Ends :-)");
			break;
		}
		switch (UserChoice)
		{
		case ShowList:
			PrintClientsList(vClients);
			break;
		case Add:
			AddClients(vClients, FileName);
			break;
		case Delete:
			DeleteClient(vClients, FileName);
			break;
		case Update:
			UpdateClient(vClients, FileName);
			break;
		case Find:
			FindClientResult(vClients);
			break;
		}
		cout << "\n\nPress any key to go back to main menu.....";
		system("pause>0");
	} while (UserChoice != MainMenuOptions::Exit);
}

int main()
{
	StartProgram(fileNmae);
}
