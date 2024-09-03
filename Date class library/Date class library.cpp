

#include <iostream>
#include "clsDate.h"
using namespace std;

int main()
{
	clsDate Date1;
	clsDate Date2(31, 10, 2022);
	clsDate Date3("31/1/2026");
	clsDate Date4(250, 2022);
	cout << Date1.Print() << endl;
	cout << Date2.Print() << endl;
	cout << Date3.Print() << endl;
	cout << Date4.Print() << endl;
	cout << Date3.IsValidDate() << endl;
	cout << Date1.GetDay()<<endl;
	cout << Date1.DayShortName() << endl;
	Date1.IncreaseDateByXDays(3);
	clsDate::IncreaseDateByXDays(Date1, 3);
	cout << Date1.Print() << endl;
}

