#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
class clsCurrencyCalculatorScreen : protected clsScreen
{

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

	static clsCurrency _ReadCurrency(string Message)
	{
		clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString(Message));
		while (Currency.IsEmpty())
		{
			cout << "\nCurrency is not found , choose another one : ";
			Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());
		}
		return Currency;
	}

public:
	static void ShowCurrencyCalculatorScreen()
	{
		do
		{
			system("cls");
			_ScreenHeader("Currency Calculator Screen", 2);
			clsCurrency Currency1 = _ReadCurrency("\nPlease Enter Currency Code1 : ");
			clsCurrency Currency2 = _ReadCurrency("\nPlease Enter Currency Code2 : ");
			printf("\nEnter Amount to Exchange : ");
			float Amount = clsInputValidate::ReadFloatNumber();
			printf("\nConvert From : ");
			_PrintCurrencyCard(Currency1);
			if (Currency2.CurrencyCode() != "USD")
			{
				printf("\nTo : ");
				_PrintCurrencyCard(Currency2);
			}
			cout << Amount << " " << Currency1.CurrencyCode() << " = " << Currency1.CurrencyExchangeTo(Currency2, Amount);
			cout << " " << Currency2.CurrencyCode() << endl;
		} while (clsUtil::ConfirmAction("\nDo You Want to Perform Another Calculation ? y/n ? "));

	}
};

