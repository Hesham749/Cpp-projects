#pragma once
#include <iostream>
using namespace std;

class clsString
{
	string _Value;

public:
	clsString()
		: _Value("")
	{
	}

	clsString(string Value)
		: _Value(Value)
	{
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string Value()
	{
		return _Value;
	}

	static string ToUpper(string st)
	{
		for (int i = 0; i < (int)st.size(); i++)
		{
			st[i] = toupper(st[i]);
		}
		return st;
	}

	void ToUpper()
	{
		_Value = ToUpper(_Value);
	}

	static string ToLower(string st)
	{
		for (int i = 0; i < (int)st.size(); i++)
		{
			st[i] = tolower(st[i]);
		}
		return st;
	}

	void ToLower()
	{
		_Value = ToLower(_Value);
	}

	static short LetterCount(string st, char letter, bool CaseSensitive = true)
	{
		short counter = 0;
		for (int i = 0; i < (int)st.length(); i++)
		{
			if (CaseSensitive)
			{
				if (st[i] == letter)
					counter++;
			}
			else
			{
				if (tolower(st[i]) == tolower(letter))
					counter++;
			}
		}
		return counter;
	}

	short LetterCount(char letter, bool CaseSensitive = true)
	{
		return LetterCount(_Value, letter, CaseSensitive);
	}

	static void PrintWords(string st)
	{
		cout << "\nyour string words is : \n";
		bool isFirstLetter = true;
		for (int i = 0; i < (int)st.length(); i++)
		{
			if (st[i] != ' ' && isFirstLetter)
			{
				cout << "\n";
			}
			isFirstLetter = st[i] == ' ' ? true : false;
			if (st[i] != ' ')
			{
				cout << st[i];
			}
		}
		cout << endl;
	}

	void PrintWords()
	{
		PrintWords(_Value);
	}

	static short WordsCount(string st)
	{
		bool isFirstLetter = true;
		short counter = 0;
		for (int i = 0; i < (int)st.length(); i++)
		{
			if (st[i] != ' ' && isFirstLetter)
				counter++;
			isFirstLetter = st[i] == ' ' ? true : false;
		}
		return counter;
	}

	short WordsCount()
	{
		return WordsCount(_Value);
	}

	static char InvertCharCase(char cr)
	{
		return islower(cr) ? toupper(cr) : tolower(cr);
	}

	char InvertCharCase()
	{
	}

	static bool IsVowel(char letter)
	{
		letter = tolower(letter);
		return letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u';
	};

	static short CountVowel(string st)
	{
		short counter = 0;
		for (short i = 0; i < (short)st.size(); i++)
		{
			if (IsVowel(st[i]))
				counter++;
		}
		return counter;
	}
	short CountVowel()
	{
		return CountVowel(_Value);
	}
};
