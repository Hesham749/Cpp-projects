#pragma once
#include <iostream>
#include <string>
#include "clsDate.h"
using namespace std;


class clsUtil
{

public:
	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static 	int RandomNumber(int from, int to)
	{
		return rand() % (to + 1 - from) + from;
	}

	enum enCharType
	{
		smallLetter = 1,
		capitalLetter,
		digit,
		specialCharacter,
		mixChars

	};

	static char GetRandomChar(enCharType randomType)
	{
		if (randomType == mixChars)
			randomType = (enCharType)RandomNumber(1, 3);

		switch (randomType)
		{
		case enCharType::smallLetter:
			return char(RandomNumber(97, 122));
		case enCharType::capitalLetter:
			return char(RandomNumber(65, 90));
		case enCharType::specialCharacter:
			return char(RandomNumber(33, 47));
		case enCharType::digit:
			return (char)RandomNumber(48, 57);
		default:
			return char(RandomNumber(97, 122));
		}
	}

	static string GenerateWord(enCharType charType, short Lenght)
	{
		string word = "";
		for (int i = 1; i <= Lenght; i++)
		{
			word += GetRandomChar(charType);
		}
		return word;
	}

	static string GenerateKey(enCharType keyType)
	{
		string key = "";
		for (int i = 1; i <= 4; i++)
		{
			key += GenerateWord(keyType, 4);
			if (i != 4)
				key += '-';
		}
		return key;
	}

	static void GenerateKeys(int numberOfKeys, enCharType keyType)
	{
		cout << "\n";
		for (int i = 1; i <= numberOfKeys; i++)
		{
			printf("Key [%d] : %s \n", i, GenerateKey(keyType).c_str());
		}
	}

	static void Swap(double& Num1, double& Num2)
	{
		double temp = Num1;
		Num1 = Num2;
		Num2 = temp;
	}

	static void Swap(int& Num1, int& Num2)
	{
		int temp = Num1;
		Num1 = Num2;
		Num2 = temp;
	}

	static void Swap(float& Num1, float& Num2)
	{
		float temp = Num1;
		Num1 = Num2;
		Num2 = temp;
	}

	static void Swap(short& Num1, short& Num2)
	{
		short temp = Num1;
		Num1 = Num2;
		Num2 = temp;
	}

	static  void Swap(char& A, char& B)
	{
		char Temp;
		Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& S1, string& S2)
	{
		string temp = S1;
		S1 = S2;
		S2 = temp;
	}

	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate::Swap(Date1, Date2);
	}

	static bool IsElementInArray(int number, int arr[], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			if (arr[i] == number)
				return true;
		}
		return false;
	}

	static bool IsElementInArray(string st, string arr[], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			if (arr[i] == st)
				return true;
		}
		return false;
	}

	static void CopyArray(int FromArr[], int ToArr[], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			ToArr[i] = FromArr[i];
		}
	}

	static void CopyArray(string FromArr[], string ToArr[], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			ToArr[i] = FromArr[i];
		}
	}

	static void ShuffleArray(int arr[], int ArrLength)
	{
		int* ptr;
		ptr = new int[ArrLength];
		for (int i = 0; i < ArrLength; i++)
		{
			int random = 0;
			do
			{
				random = RandomNumber(0, ArrLength - 1);
			} while (IsElementInArray(arr[random], ptr, ArrLength));

			*(ptr + i) = arr[random];
		}
		CopyArray(ptr, arr, ArrLength);
		delete[] ptr;
	}

	static void ShuffleArray(string arr[], int ArrLength)
	{
		string* ptr;
		ptr = new string[ArrLength];
		for (int i = 0; i < ArrLength; i++)
		{
			int random = 0;
			do
			{
				random = RandomNumber(0, ArrLength - 1);
			} while (IsElementInArray(arr[random], ptr, ArrLength));

			*(ptr + i) = arr[random];
		}
		CopyArray(ptr, arr, ArrLength);
		delete[] ptr;
	}

	static void FillArrayWithRandomNumbers(int arr[], int ArrLength, int from, int to)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			arr[i] = RandomNumber(from, to);
		}
	}

	static void FillArrayWithRandomWords(string arr[], int ArrLength, enCharType CharType, int WordLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			arr[i] = GenerateWord(CharType, WordLength);
		}
	}


	static void FillArrayWithRandomKeys(string arr[], int ArrLength, enCharType CharType)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			arr[i] = GenerateKey(CharType);
		}
	}

	static string Tabs(short NumOfTabs)
	{
		string tab = "";
		for (short i = 0; i < NumOfTabs; i++)
		{
			tab += "\t";
		}
		return tab;
	}

	static void Encryption(string& text, short encryptionKey)
	{
		for (int i = 0; i < (int)text.length(); i++)
		{

			text[i] = (char)((int)text[i]) + encryptionKey;
		}
	}
	static void Decryption(string& text, short encryptionKey)
	{
		for (int i = 0; i < (int)text.length(); i++)
		{

			text[i] = (char)((int)text[i]) - encryptionKey;
		}
	}

	static string NumberToText(int number)
	{

		if (number >= 0 && number <= 19)
		{
			string arr[]{ "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
			return arr[number];
		}
		if (number >= 20 && number <= 99)
		{
			string arr[]{ "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
			return arr[number / 10] + " " + NumberToText(number % 10);
		}
		if (number >= 100 && number <= 999)
		{
			return NumberToText(number / 100) + " Hundred " + NumberToText(number % 100);
		}
		if (number >= 1000 && number <= 999999)
		{
			return NumberToText(number / 1000) + " Thousand " + NumberToText(number % 1000);
		}
		if (number >= 1000000 && number <= 999999999)
		{
			return NumberToText(number / 1000000) + " Million " + NumberToText(number % 1000000);
		}
	}
};

