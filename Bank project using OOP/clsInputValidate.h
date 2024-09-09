#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
using namespace std;

class clsInputValidate
{

public:
	static bool IsNumberBetween(double Number, double start, double end)
	{
		return Number >= start && Number <= end;
	}

	static bool IsNumberBetween(int Number, int start, int end)
	{
		return IsNumberBetween((double)Number, (double)start, (double)end);
	}

	static bool IsNumberBetween(short Number, short start, short end)
	{
		return IsNumberBetween((double)Number, (double)start, (double)end);
	}

	static bool IsNumberBetween(float Number, float start, float end)
	{
		return IsNumberBetween((double)Number, (double)start, (double)end);
	}

	static 	bool IsDateBetween(clsDate Date, clsDate StartDate, clsDate EndDate)
	{
		if (clsDate::IsDate1AfterDate2(StartDate, EndDate))
			return IsDateBetween(Date, EndDate, StartDate);

		return !clsDate::IsDate1BeforeDate2(Date, StartDate) && !clsDate::IsDate1AfterDate2(Date, EndDate);
	}

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		return (int)ReadDblNumber(ErrorMessage);
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		return (float)ReadDblNumber(ErrorMessage);
	}

	static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		return (short)ReadDblNumber(ErrorMessage);
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again:\n")
	{
		double Num = 0;
		while (!(cin >> Num))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Num;
	}


	static int ReadIntNumberBetween(int from, int to, string ErrorMessage = "Number is not within range, enter again:\n")
	{
		return (int)ReadDblNumberBetween((double)from, (double)to, ErrorMessage);
	}

	static short ReadShortNumberBetween(short from, short to, string ErrorMessage = "Number is not within range, enter again:\n")
	{
		return (short)ReadDblNumberBetween((double)from, (double)to, ErrorMessage);
	}

	static double ReadDblNumberBetween(double from, double to, string ErrorMessage = "Number is not within range, enter again:\n")
	{
		double Num;
		while (!IsNumberBetween(Num = ReadDblNumber(), from, to))
		{
			cout << ErrorMessage;
		}
		return Num;
	}

	static float ReadFloatNumberBetween(float from, float to, string ErrorMessage = "Number is not within range, enter again:\n")
	{
		return (float)ReadDblNumberBetween((double)from, (double)to, ErrorMessage);
	}

	static bool IsValideDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static 	string ReadString(string message = "")
	{
		string st;
		cout << message;
		getline(cin >> ws, st, '\n');
		return st;
	}
};

