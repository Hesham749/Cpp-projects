#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
class clsFindCurrencyScreen :protected clsScreen
{
	enum _enFindBy
	{
		eCode = 1, eCountry
	};

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		printf("\n______________________________________________\n\n");
		printf("%-10s : %s\n", "Country", Currency.Country().c_str());
		printf("%-10s : %s\n", "Code", Currency.CurrencyCode().c_str());
		printf("%-10s : %s\n", "Name", Currency.CurrencyName().c_str());
		printf("%-10s : ", "Rate(1$) =");
		cout << Currency.Rate();
		printf("\n\n----------------------------------------------\n");
	}

	static clsCurrency _PerformFindByOption(_enFindBy FindBy)
	{
		switch (FindBy)
		{
		case _enFindBy::eCode:
			return clsCurrency::FindByCode(clsInputValidate::ReadString("\nPlease Enter Currency Code : "));
		case _enFindBy::eCountry:
			return clsCurrency::FindByCountry(clsInputValidate::ReadString("\nPlease Enter Country Name : "));
		}
	}

	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			printf("\nCurrency Found :-)\n\nCurrency Card : ");
			_PrintCurrencyCard(Currency);
		}
		else
			printf("\nCurrency Not Found :-(\n\n");
	}

public:
	static void ShowFindCurrencyScreen()
	{
		system("cls");
		_ScreenHeader("Find Currency Screen", 2);
		printf("Find By : [1] Code or [2] Country ? ");
		clsCurrency Currency = _PerformFindByOption((_enFindBy)clsInputValidate::ReadShortNumberBetween(1, 2));
		_ShowResult(Currency);
	}
};

