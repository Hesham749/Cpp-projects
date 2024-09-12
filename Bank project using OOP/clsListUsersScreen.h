#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"

class clsListUsersScreen : protected clsScreen
{
	static void _PrintUserRecordLine(clsUser User)
	{

		cout << "| " << setw(15) << left << User.UserName;
		cout << "| " << setw(25) << left << User.FullName();
		cout << "| " << setw(12) << left << User.Phone;
		cout << "| " << setw(20) << left << User.Email;
		cout << "| " << setw(10) << left << User.Password;
		cout << "| " << setw(12) << left << User.AccountPermissons;

	}

public:
	static void ShowUsersList()
	{
		vector <clsUser> vUsers = clsUser::GetUsersList();
		string Title = "User List Screen";
		string SubTitle = "(" + to_string(vUsers.size()) + ") User(s).";

		_ScreenHeader(Title, 2, SubTitle);


		cout << "\n_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		cout << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(25) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << "\n_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

		if (vUsers.size() == 0)
			cout << "\t\t\t\tNo Users Available In the System!";
		else

			for (clsUser User : vUsers)
			{

				_PrintUserRecordLine(User);
				cout << endl;
			}

		cout << "\n_______________________________________________________";
		cout << "_____________________________________________________\n" << endl;

	}
};

