#pragma once
#include "clsPerson.h"
#include <iostream>

string UsersFile = "Users.txt";

class clsUser :public clsPerson
{
	enum enMode
	{
		EmptyMode, UpdatMode, AddNewMode
	};
	enMode _Mode;

	string
		_UserName,
		_Password;
	short _Permissions;
	bool _MarkForDelete = false;

	static clsUser _LineToUser(string Line, string Seperator = "#//#")
	{
		vector <string> vUser = clsString::Split(Line, Seperator);
		return clsUser(enMode::UpdatMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], vUser[5], stod(vUser[6]));
	}

	static clsUser _EmptyUser()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static string _UserToLine(clsUser User, string Seperator = "#//#")
	{
		string UserRecord = "";
		UserRecord += User.FirstName + Seperator;
		UserRecord += User.LastName + Seperator;
		UserRecord += User.Email + Seperator;
		UserRecord += User.Phone + Seperator;
		UserRecord += User.UserName + Seperator;
		UserRecord += User.Password + Seperator;
		UserRecord += to_string(User.AccountPermissions);
		return UserRecord;
	}

	static void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open(UsersFile, ios::app);
		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	}

	void _UpdateFileData(vector<clsUser>& vUsers)
	{
		fstream Myfile;
		Myfile.open(UsersFile, ios::out);
		if (Myfile.is_open())
		{
			for (auto& C : vUsers)
			{
				if (!C._MarkForDelete)
				{
					Myfile << _UserToLine(C) << endl;
				}
			}
			Myfile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> vUsers = GetUsersList();
		for (auto& C : vUsers)
		{
			if (C.UserName == _UserName)
			{
				C = *this;
				break;
			}
		}
		_UpdateFileData(vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_UserToLine(*this));
	}

public:
	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, short Permissons)
		: _Mode(Mode), clsPerson(FirstName, LastName, Email, Phone), _UserName(UserName), _Password(Password), _Permissions(Permissons)
	{
	}

	enum enPermissions
	{
		FullAccess = -1,
		ListAccess = 1,
		AddAccess = 2,
		DeleteAccess = 4,
		UpdateAccess = 8,
		FindAccess = 16,
		TransactionsAccess = 32,
		MangeUsersAccess = 64
	};

	bool IsEmpty()
	{
		return _Mode == EmptyMode;
	}

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissons(short Permissons)
	{
		_Permissions = Permissons;
	}

	short GetPermissons()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissons, put = SetPermissons)) short AccountPermissions;

	static vector<clsUser> GetUsersList(string Seperator = "#//#")
	{
		vector<clsUser> vAllUsers;
		fstream MyFile;
		MyFile.open(UsersFile, ios::in);
		if (MyFile.is_open())
		{
			string line = "";
			while (getline(MyFile, line))
			{
				vAllUsers.push_back(_LineToUser(line));
			}
			MyFile.close();
		}
		return vAllUsers;
	}

	static clsUser Find(string UserName)
	{
		fstream Myfile;
		Myfile.open(UsersFile, ios::in);
		if (Myfile.is_open())
		{
			string line = "";
			while (getline(Myfile, line))
			{
				clsUser User = _LineToUser(line);
				if (User.UserName == UserName)
				{
					Myfile.close();
					return User;
				}
			}
			Myfile.close();
			return _EmptyUser();
		}
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream Myfile;
		Myfile.open(UsersFile, ios::in);
		if (Myfile.is_open())
		{
			string line = "";
			while (getline(Myfile, line))
			{
				clsUser User = _LineToUser(line);
				if (User.UserName == UserName && User.Password == Password)
				{
					Myfile.close();
					return User;
				}
			}
			Myfile.close();
			return _EmptyUser();
		}

	}

	static bool IsUserExist(string UserName)
	{
		return !clsUser::Find(UserName).IsEmpty();
	}

	enum enSaveResults {
		svSucceeded, svFaildEmptyObject, svFaildUserNameExists
	};

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case clsUser::EmptyMode:
			return svFaildEmptyObject;
		case clsUser::UpdatMode:
			_Update();
			return svSucceeded;
		case clsUser::AddNewMode:
			if (IsUserExist(_UserName))
				return svFaildUserNameExists;
			else
			{
				_AddNew();
				return svSucceeded;
			}
		default:
			break;
		}
	}

	static clsUser AddNewUser(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	bool Delete()
	{
		_MarkForDelete = true;
		_Update();
		*this = clsUser::Find(_UserName);
		return IsEmpty();
	}
};

