#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
class clsLoginScreen :protected::clsScreen
{


public:
	static void ShowLoginScreen()
	{
		system("cls");
		_ScreenHeader("Login Screen", 2);
	}
};

