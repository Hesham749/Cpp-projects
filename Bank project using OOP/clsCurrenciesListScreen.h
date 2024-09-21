#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "string"
class clsCurrenciesListScreen :protected clsScreen
{

	static void _PrintCurrenyLine(clsCurrency Currency)
	{
		printf("| %-30s | %-10s | %-40s | ", Currency.Country().c_str(), Currency.CurrencyCode().c_str(), Currency.CurrencyName().c_str());
		cout << Currency.Rate();
	}

public:
	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetAllCurrencies();
		_ScreenHeader("Currencies List Screen", 2, "(" + to_string(vCurrencies.size()) + ") Currency");
		printf("\n_____________________________________________________________________________________________________________\n\n");
		printf("| %-30s | %-10s | %-40s | %-20s", "Country", "Code", "Name", "Rate(1$)");
		printf("\n-------------------------------------------------------------------------------------------------------------\n");
		for (auto& C : vCurrencies)
		{
			_PrintCurrenyLine(C);
			cout << endl;
		}
	}
};

