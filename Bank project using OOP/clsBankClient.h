#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;

string File = "Clients.txt";

class clsBankClient : public clsPerson
{
	enum enMode
	{
		EmptyMode, UpdatMode, AddNewMode
	};
	enMode _Mode;

	string
		_UserName,
		_PinCode;
	double _Balance;
	bool _MarkForDelete = false;

	static clsBankClient _LineToClient(string Line, string Seperator = "#//#")
	{
		vector <string> vClient = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdatMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));
	}

	static clsBankClient _EmptyClient()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _ClientToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string ClientRecord = "";
		ClientRecord += Client.FirstName + Seperator;
		ClientRecord += Client.LastName + Seperator;
		ClientRecord += Client.Email + Seperator;
		ClientRecord += Client.Phone + Seperator;
		ClientRecord += Client.AccountNumber() + Seperator;
		ClientRecord += Client.PinCode + Seperator;
		ClientRecord += to_string(Client.AccountBalance);
		return ClientRecord;
	}

	static void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open(File, ios::app);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _UpdateFileData(vector<clsBankClient>& vClients)
	{
		fstream Myfile;
		Myfile.open(File, ios::out);
		if (Myfile.is_open())
		{
			for (auto& C : vClients)
			{
				if (!C._MarkForDelete)
				{
					Myfile << _ClientToLine(C) << endl;
				}
			}
			Myfile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients = GetClientsList();
		for (auto& C : vClients)
		{
			if (C.AccountNumber() == _UserName)
			{
				C = *this;
				break;
			}
		}
		_UpdateFileData(vClients);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ClientToLine(*this));
	}

public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, double balance)
		: _Mode(Mode), clsPerson(FirstName, LastName, Email, Phone), _UserName(AccountNumber), _PinCode(PinCode), _Balance(balance)
	{
	}

	bool IsEmpty()
	{
		return _Mode == EmptyMode;
	}

	string AccountNumber()
	{
		return _UserName;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetBalance(double Balance)
	{
		_Balance = Balance;
	}

	double GetBalance()
	{
		return _Balance;
	}

	__declspec(property(get = GetBalance, put = SetBalance)) double AccountBalance;

	static vector<clsBankClient> GetClientsList(string Seperator = "#//#")
	{
		vector<clsBankClient> vAllClients;
		fstream MyFile;
		MyFile.open(File, ios::in);
		if (MyFile.is_open())
		{
			string line = "";
			while (getline(MyFile, line))
			{
				vAllClients.push_back(_LineToClient(line));
			}
			MyFile.close();
		}
		return vAllClients;
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream Myfile;
		Myfile.open(File, ios::in);
		if (Myfile.is_open())
		{
			string line = "";
			while (getline(Myfile, line))
			{
				clsBankClient client = _LineToClient(line);
				if (client.AccountNumber() == AccountNumber)
				{
					Myfile.close();
					return client;
				}
			}
			Myfile.close();
			return _EmptyClient();
		}
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream Myfile;
		Myfile.open(File, ios::in);
		if (Myfile.is_open())
		{
			string line = "";
			while (getline(Myfile, line))
			{
				clsBankClient client = _LineToClient(line);
				if (client.AccountNumber() == AccountNumber && client.PinCode == PinCode)
				{
					Myfile.close();
					return client;
				}
			}
			Myfile.close();
			return _EmptyClient();
		}

	}

	static bool IsClientExist(string AccountNumber)
	{
		return !clsBankClient::Find(AccountNumber).IsEmpty();
	}

	enum enSaveResults {
		svSucceeded, svFaildEmptyObject, svFaildAccountNumberExists
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return svFaildEmptyObject;
		case clsBankClient::UpdatMode:
			_Update();
			return svSucceeded;
		case clsBankClient::AddNewMode:
			if (IsClientExist(_UserName))
				return svFaildAccountNumberExists;
			else
			{
				_AddNew();
				return svSucceeded;
			}
		default:
			break;
		}
	}

	static clsBankClient AddNewClient(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		_MarkForDelete = true;
		_Update();
		*this = clsBankClient::Find(_UserName);
		return IsEmpty();
	}

	static double GetTotalBalances()
	{
		double total = 0;
		vector <clsBankClient> Clients = GetClientsList();
		for (auto& C : Clients)
		{
			total += C.AccountBalance;
		}
		return total;
	}

	void Deposit(double Amount)
	{
		_Balance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _Balance)
			return false;
		_Balance -= Amount;
		Save();
		return true;
	}

	bool Transfer(clsBankClient& ToClient, double Amount)
	{
		if (!Withdraw(Amount))
			return false;
		ToClient.Deposit(Amount);
		return true;
	}
};

