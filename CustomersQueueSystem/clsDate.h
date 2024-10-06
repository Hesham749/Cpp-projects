#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "clsString.h"
using namespace std;

class clsDate
{
	short _Year, _Month, _Day;

	clsDate _StringToDate(string DateString, string Seperator = "/")
	{
		clsDate Date;
		vector<string> vDate = clsString::Split(DateString, Seperator);
		Date._Day = stoi(vDate[0]);
		Date._Month = stoi(vDate[1]);
		Date._Year = stoi(vDate[2]);
		return Date;
	}

	static short _UpdateDaysAfterDateChange(clsDate Date)
	{
		short monthDays = DaysInMonth(Date._Year, Date._Month);
		return (Date._Day > monthDays) ? monthDays : Date._Day;
	}

	static void _CalenderHeader(short month)
	{
		printf("\n_____________________%s_____________________\n", MonthShortName(month).c_str());
		for (short i = 0; i < 7; i++)
		{
			printf("%-7s", DayShortName(i).c_str());
		}
		cout << endl;
	}

	enum enWeekDays
	{
		Sun,
		Mon,
		Tue,
		Wed,
		Thu,
		Fri,
		Sat
	};

public:
	clsDate()
	{
		time_t _t = time(0);
		tm* _Now = localtime(&_t);
		_Year = (_Now->tm_year + 1900);
		_Month = (_Now->tm_mon + 1);
		_Day = (_Now->tm_mday);
	}

	clsDate(short day, short month, short year)
		:_Year(year), _Month(month), _Day(day)
	{}

	clsDate(string Date)
	{
		*this = _StringToDate(Date);
	}

	clsDate(short DateOrderInYear, short year)
	{
		*this = DateFromDayOrderInYear(DateOrderInYear, year);
	}

	static string GetSystemDateTimeString()
	{
		//system dateTime string
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	void SetDay(short day)
	{
		_Day = day;
	}

	short GetDay()
	{
		return _Day;
	}

	void SetMonth(short month)
	{
		_Month = month;
	}

	short GetMonth()
	{
		return _Month;
	}

	void SetYear(short year)
	{
		_Year = year;
	}

	short GetYear()
	{
		return _Year;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate temp = Date1;
		Date1 = Date2;
		Date2 = temp;
	}

	static string Print(clsDate Date, string Seperator = "/")
	{
		return to_string(Date._Day) + Seperator + to_string(Date._Month) + Seperator + to_string(Date._Year);
	}

	string Print(string Seperator = "/")
	{
		return Print(*this, Seperator);
	}

	static bool IsValidDate(clsDate Date)
	{
		return Date._Year > 0 && (Date._Month > 0 && Date._Month <= 12) && (Date._Day <= DaysInMonth(Date._Year, Date._Month) && Date._Day > 0);
	}

	bool IsValidDate()
	{
		return IsValidDate(*this);
	}

	static bool IsLeapYear(short Year)
	{
		return Year % 400 == 0 || (Year % 4 == 0 && Year % 100 != 0);
	}

	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short DaysInYear(short year)
	{
		return IsLeapYear(year) ? 366 : 365;
	}

	short DaysInYear()
	{
		return DaysInYear(_Year);
	}

	static short HoursInYear(short year)
	{
		return DaysInYear(year) * 24;
	}

	short HoursInYear()
	{
		return  HoursInYear(_Year);
	}

	static int MinutesInYear(short year)
	{
		return HoursInYear(year) * 60;
	}

	int MinutesInYear()
	{
		return MinutesInYear(_Year);
	}

	static int SecondsInYear(short year)
	{
		return MinutesInYear(year) * 60;
	}

	int SecondsInYear()
	{
		return SecondsInYear(_Year);
	}

	static short DaysInMonth(short year, short Month)
	{
		if (Month > 12 || Month < 1)
		{
			return 0;
		}
		return (Month == 2) ? (IsLeapYear(year) ? 29 : 28) : (Month == 4 || Month == 6 || Month == 9 || Month == 11 ? 30 : 31);
	}

	short DaysInMonth()
	{
		return DaysInMonth(_Year, _Month);
	}

	static short HoursInMonth(short year, short Month)
	{
		return DaysInMonth(year, Month) * 24;
	}

	short HoursInMonth()
	{
		return  HoursInMonth(_Year, _Month);
	}

	static int MinutesInMonth(short year, short Month)
	{
		return HoursInMonth(year, Month) * 60;
	}

	int MinutesInMonth()
	{
		return MinutesInMonth(_Year, _Month);
	}

	static int SecondsInMonth(short year, short Month)
	{
		return MinutesInMonth(year, Month) * 60;
	}

	int SecondsInMonth()
	{
		return SecondsInMonth(_Year, _Month);
	}

	static short DayOrderInWeek(short year, short month, short day)
	{
		short a, y, m;
		a = (14 - month) / 12;
		y = year - a;
		m = month + (12 * a) - 2;
		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static short DayOrderInWeek(clsDate Date)
	{
		return DayOrderInWeek(Date._Year, Date._Month, Date._Day);
	}

	short DayOrderInWeek()
	{
		return DayOrderInWeek(*this);
	}

	static short TotalDaysFromTheBeginningOfTheYear(clsDate Date)
	{
		short TotalDays = 0;
		for (short i = 1; i < Date._Month; i++)
		{
			TotalDays += DaysInMonth(Date._Year, i);
		}
		return TotalDays + Date._Day;
	}

	short TotalDaysFromTheBeginningOfTheYear()
	{
		return TotalDaysFromTheBeginningOfTheYear(*this);
	}

	static string DayShortName(short DayOrderInWeek)
	{
		string Days[]{ "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return Days[DayOrderInWeek];
	}

	static string DayShortName(clsDate Date)
	{
		return DayShortName(DayOrderInWeek(Date));
	}

	string DayShortName()
	{
		return DayShortName(*this);
	}

	static string MonthShortName(short monthOrder)
	{
		string Months[]{ "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return Months[monthOrder];
	}

	string MonthShortName()
	{
		return MonthShortName(_Month);
	}

	static void PrintMonthCalender(short year, short month)
	{
		_CalenderHeader(month);
		short counter = 1;
		short days = DaysInMonth(year, month);

		for (short i = 0; counter <= days; i++)
		{
			for (short j = 0; j < 7; j++)
			{
				if (i == 0 && j < DayOrderInWeek(year, month, 1))
				{
					printf("%-7c", ' ');
				}
				else
				{
					printf("%-7d", counter++);
				}
				if (counter > days)
					break;
			}
			cout << endl;
		}
		cout << "_____________________________________________" << endl;
	}

	void PrintMonthCalender()
	{
		PrintMonthCalender(_Year, _Month);
	}

	static void PrintYearCalender(short year)
	{
		printf("\n_____________________________________________\n");
		printf("\n             Calender - %d\n", year);
		printf("\n---------------------------------------------\n");
		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalender(year, i);
		}
	}

	void PrintYearCalender()
	{
		PrintYearCalender(_Year);
	}

	static clsDate DateFromDayOrderInYear(short DayOrder, short year)
	{
		clsDate Date;
		Date._Year = year;
		Date._Month = 1;
		short remainingDays = DayOrder;
		short MonthDays;
		while (remainingDays > (MonthDays = DaysInMonth(year, Date._Month)))
		{
			remainingDays -= MonthDays;
			Date._Month++;
		}
		Date._Day = remainingDays;
		return Date;
	}

	static void IncreaseDateByXDays(clsDate& Date, double DaysToAdd)
	{
		double remainDays = TotalDaysFromTheBeginningOfTheYear(Date) + DaysToAdd;
		short yearDays = 0;
		while (remainDays > (yearDays = DaysInYear(Date._Year)))
		{
			remainDays -= yearDays;
			Date._Year++;
		}
		Date = DateFromDayOrderInYear(remainDays, Date._Year);
	}

	void IncreaseDateByXDays(double DaysToAdd)
	{
		IncreaseDateByXDays(*this, DaysToAdd);
	}

	static bool IsDate1BeforeDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) || ((Date1._Year == Date2._Year) && (Date1._Month < Date2._Month || (Date1._Month == Date2._Month && Date1._Day < Date2._Day)));
	}

	bool IsDateBeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year && Date1._Month == Date2._Month && Date1._Day == Date2._Day);
	}

	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return !IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2);
	}

	bool IsDateAfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date._Day == DaysInMonth(Date._Year, Date._Month);
	}

	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonth(short Month)
	{
		return Month == 12;
	}

	bool IsLastMonth()
	{
		return IsLastMonth(_Month);
	}

	static void IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsLastDayInMonth(Date))
		{
			Date._Day = 1;
			IsLastMonth(Date._Month) ? (Date._Month = 1, Date._Year++) : ++Date._Month;
		}
		else
			Date._Day++;
	}

	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static short DaysFromYearToYear(short FromYear, short ToYear)
	{
		short Days = 0;
		while (ToYear > FromYear)
		{
			ToYear--;
			Days += DaysInYear(ToYear);
		}
		return Days;
	}

	static short DifferenceBetween2DatesInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		if (IsDate1EqualDate2(Date1, Date2))
			return 0;
		if (IsDate1BeforeDate2(Date1, Date2))
		{
			short Difference = (DaysFromYearToYear(Date1._Year, Date2._Year) + TotalDaysFromTheBeginningOfTheYear(Date2)) - TotalDaysFromTheBeginningOfTheYear(Date1);
			return IncludeEndDay ? ++Difference : Difference;
		}
		return -DifferenceBetween2DatesInDays(Date2, Date1, IncludeEndDay);
	}

	short DifferenceBetween2DatesInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return DifferenceBetween2DatesInDays(*this, Date2, IncludeEndDay);
	}

	static short AgeInDays(clsDate DateOfBirth)
	{
		return DifferenceBetween2DatesInDays(DateOfBirth, clsDate(), true);
	}

	short AgeInDays()
	{
		return AgeInDays(*this);
	}

	static void IncreaseDateByOneWeek(clsDate& Date)
	{
		IncreaseDateByXDays(Date, 7);
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static void IncreaseDateByXWeeks(clsDate& Date, short WeeksToAdd)
	{
		for (short i = 0; i < WeeksToAdd; i++)
			IncreaseDateByOneWeek(Date);
	}

	void IncreaseDateByXWeeks(short WeeksToAdd)
	{
		IncreaseDateByXWeeks(*this, WeeksToAdd);
	}

	static void IncreaseDateByOneMonth(clsDate& Date)
	{
		IsLastMonth(Date._Month) ? (Date._Month = 1, Date._Year++) : ++Date._Month;
		Date._Day = _UpdateDaysAfterDateChange(Date);
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static void IncreaseDateByXMonth(clsDate& Date, short MonthsToAdd)
	{
		for (short i = 0; i < MonthsToAdd; i++)
			IncreaseDateByOneMonth(Date);
	}

	void IncreaseDateByXMonth(short MonthsToAdd)
	{
		IncreaseDateByXMonth(*this, MonthsToAdd);
	}

	static void IncreaseDateByOneYear(clsDate& Date)
	{
		Date._Year++;
		Date._Day = _UpdateDaysAfterDateChange(Date);
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static void IncreaseDateByXYear(clsDate& Date, short YearsToAdd)
	{
		Date._Year += YearsToAdd;
		Date._Day = _UpdateDaysAfterDateChange(Date);
	}

	void IncreaseDateByXYear(short YearsToAdd)
	{
		IncreaseDateByXYear(*this, YearsToAdd);
	}


	static void DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date._Day == 1)
		{
			(Date._Month == 1) ? (Date._Month = 12, Date._Year--) : --Date._Month;
			Date._Day = DaysInMonth(Date._Year, Date._Month);
		}
		else
			Date._Day--;

	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static void DecreaseDateByXDays(clsDate& Date, short DaysToAdd)
	{
		for (short i = 0; i < DaysToAdd; i++)
			DecreaseDateByOneDay(Date);

	}

	void DecreaseDateByXDays(short DaysToAdd)
	{
		DecreaseDateByXDays(*this, DaysToAdd);
	}

	static void DecreaseDateByOneWeek(clsDate& Date)
	{
		DecreaseDateByXDays(Date, (short)7);

	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static void DecreaseDateByXWeeks(clsDate& Date, short WeeksToAdd)
	{
		for (short i = 0; i < WeeksToAdd; i++)
			DecreaseDateByOneWeek(Date);

	}

	void DecreaseDateByXWeeks(short WeeksToAdd)
	{
		DecreaseDateByXWeeks(*this, WeeksToAdd);
	}

	static void DecreaseDateByOneMonth(clsDate& Date)
	{
		(Date._Month == 1) ? (Date._Month = 12, Date._Year--) : --Date._Month;
		Date._Day = _UpdateDaysAfterDateChange(Date);
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static void DecreaseDateByXMonth(clsDate& Date, short MonthsToAdd)
	{
		for (short i = 0; i < MonthsToAdd; i++)
			DecreaseDateByOneMonth(Date);
	}

	void DecreaseDateByXMonth(short MonthsToAdd)
	{
		DecreaseDateByXMonth(*this, MonthsToAdd);
	}

	static void DecreaseDateByOneYear(clsDate& Date)
	{
		Date._Year--;
		Date._Day = _UpdateDaysAfterDateChange(Date);
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static void DecreaseDateByXYear(clsDate& Date, short YearsToAdd)
	{
		Date._Year -= YearsToAdd;
		Date._Day = _UpdateDaysAfterDateChange(Date);
	}

	void DecreaseDateByXYear(short YearsToAdd)
	{
		DecreaseDateByXYear(*this, YearsToAdd);
	}

	static bool IsEndOfTheWeek(clsDate Date)
	{
		return (DayOrderInWeek(Date) == enWeekDays::Sat);
	}

	bool IsEndOfTheWeek()
	{
		return IsEndOfTheWeek(*this);
	}

	static bool IsWeekend(clsDate Date)
	{
		return (DayOrderInWeek(Date) == enWeekDays::Fri || DayOrderInWeek(Date) == enWeekDays::Sat);
	}

	bool IsWeekend()
	{
		return IsWeekend(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekend(Date);
	}

	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfTheWeek(clsDate Date)
	{
		return (enWeekDays::Sat - DayOrderInWeek(Date));
	}

	bool DaysUntilTheEndOfTheWeek()
	{
		return DaysUntilTheEndOfTheWeek(*this);
	}

	static short DaysUntilTheEndOfTheMonth(clsDate Date)
	{
		return (DaysInMonth(Date._Year, Date._Month) - Date._Day);
	}

	bool DaysUntilTheEndOfTheMonth()
	{
		return DaysUntilTheEndOfTheMonth(*this);
	}

	static short DaysUntilTheEndOfTheYear(clsDate Date)
	{
		return (DaysInYear(Date._Year) - TotalDaysFromTheBeginningOfTheYear(Date));
	}

	bool DaysUntilTheEndOfTheYear()
	{
		return DaysUntilTheEndOfTheYear(*this);
	}

	static short CalculateVacationDays(clsDate FromDate, clsDate ToDate)
	{
		short DaysCount = 0;
		while (IsDate1BeforeDate2(FromDate, ToDate))
		{
			if (IsBusinessDay(FromDate))
				DaysCount++;
			IncreaseDateByOneDay(FromDate);
		}
		return DaysCount;
	}

	static clsDate VacationReturnDate(clsDate FromDate, short VacationDays)
	{
		while (VacationDays > 0 || IsWeekend(FromDate))
		{
			if (IsBusinessDay(FromDate))
				VacationDays--;
			IncreaseDateByOneDay(FromDate);
		}
		return FromDate;
	}

};
