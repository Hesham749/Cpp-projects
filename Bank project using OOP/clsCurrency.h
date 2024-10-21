#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "clsString.h"
using namespace std;
const string CurrencyFile = "Currencies.txt";

class clsCurrency
{
	enum enMode { EmptyMode, UpdateMode };
	enMode _Mode;
	string _Country,
		_CurrencyCode,
		_CurrencyName;
	float _Rate;

	static clsCurrency _LineToCurrencyObject(string line, string Seperator = "#//#")
	{
		vector <string> vCurrency = clsString::Split(line, Seperator);
		return clsCurrency(enMode::UpdateMode, vCurrency[0], vCurrency[1], vCurrency[2], stod(vCurrency[3]));
	}

	static string _CurrencyToLine(clsCurrency Currency, string Seperator = "#//#")
	{
		return Currency.Country() + Seperator + Currency.CurrencyCode() + Seperator + Currency.CurrencyName() + Seperator + to_string(Currency.Rate());
	}

	static clsCurrency _EmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

	static void _DataToFile(vector <clsCurrency> Currencies)
	{
		fstream Myfile;
		Myfile.open(CurrencyFile, ios::out);
		if (Myfile.is_open())
		{
			for (auto& C : Currencies)
			{
				Myfile << _CurrencyToLine(C) << endl;
			}
			Myfile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vAllCurrencies = GetAllCurrencies();
		for (auto& C : vAllCurrencies)
		{
			if (C._CurrencyCode == _CurrencyCode)
			{
				C._Rate = _Rate;
				break;
			}
		}
		_DataToFile(vAllCurrencies);
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
		:_Mode(Mode), _Country(Country), _CurrencyCode(CurrencyCode), _CurrencyName(CurrencyName), _Rate(Rate)
	{}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	bool IsEmpty()
	{
		return _Mode == EmptyMode;
	}

	static vector <clsCurrency> GetAllCurrencies()
	{
		vector <clsCurrency> vAllCurrencies;
		fstream Myfile;
		Myfile.open(CurrencyFile, ios::in);
		if (Myfile.is_open())
		{
			string line = "";
			while (getline(Myfile, line))
			{
				vAllCurrencies.push_back(_LineToCurrencyObject(line));
			}
			Myfile.close();
		}
		return vAllCurrencies;
	}

	static clsCurrency FindByCountry(string Country)
	{
		vector <clsCurrency> vAllCurrencies = GetAllCurrencies();
		for (auto& C : vAllCurrencies)
		{
			if (clsString::ToUpper(C.Country()) == clsString::ToUpper(Country))
				return C;
		}
		return _EmptyCurrencyObject();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		vector <clsCurrency> vAllCurrencies = GetAllCurrencies();
		for (auto& C : vAllCurrencies)
		{
			if (clsString::ToUpper(C.CurrencyCode()) == clsString::ToUpper(CurrencyCode))
				return C;
		}
		return _EmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		return FindByCode(CurrencyCode).IsEmpty();
	}

	float CurrencyExchangeTo(clsCurrency ToCurrency, float Amount)
	{
		if (ToCurrency._CurrencyCode == "USD")
			return (float)Amount / _Rate;
		return (float) (Amount / _Rate) * ToCurrency._Rate;
	}
};
