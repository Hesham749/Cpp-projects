#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
class clsUpdateCurrencyScreen :protected clsScreen
{
	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		printf("\n\nCurrency Card : ");
		printf("\n______________________________________________\n\n");
		printf("%-10s : %s\n", "Country", Currency.Country().c_str());
		printf("%-10s : %s\n", "Code", Currency.CurrencyCode().c_str());
		printf("%-10s : %s\n", "Name", Currency.CurrencyName().c_str());
		printf("%-10s : ", "Rate(1$) =");
		cout << Currency.Rate();
		printf("\n\n----------------------------------------------\n");
	}
public:


	static void ShowUpdateCurrencyScreen()
	{
		system("cls");
		_ScreenHeader("Update Currency Screen", 2);
		clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString("\nPlease Enter Currency Code : "));
		while (Currency.IsEmpty())
		{
			cout << "\nCurrency is not found , choose another one : ";
			Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());
		}
		_PrintCurrencyCard(Currency);
		if (clsUtil::ConfirmAction("Are You Sure you want to update the Rate of this currency y/n ? "))
		{
			printf("\nUpdate Currency Rate : \n________________________________________________");
			printf("\n\nEnter new Rate : ");
			Currency.UpdateRate(clsInputValidate::ReadFloatNumber());
			printf("\nCurrency Rate Updated Successfully :-)");
			_PrintCurrencyCard(Currency);
		}
	}
};

