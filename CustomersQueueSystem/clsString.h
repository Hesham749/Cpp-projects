#pragma once
#include <iostream>
#include <string>
#include <vector>
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

	short Length()
	{
		return _Value.length();
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

	enum _enWhatToCount
	{
		smallLetters, CapitalLetters, All
	};

	static short CountLetters(string st, _enWhatToCount whatToCount = All)
	{
		short counter = 0;
		for (int i = 0; i < (int)st.length(); i++)
		{
			if (!ispunct(st[i]) && st[i] != ' ')
			{
				if (whatToCount == CapitalLetters)
				{
					if (st[i] == toupper(st[i]))
						counter++;
				}

				else if (whatToCount == smallLetters)
				{
					if (st[i] == tolower(st[i]))
						counter++;
				}
				else
				{
					counter++;
				}
			}
		}
		return counter;
	}

	short CountLetters(_enWhatToCount whatToCount = All)
	{
		return CountLetters(_Value, whatToCount);
	}

	static short CountCapitalLetters(string st)
	{
		return CountLetters(st, CapitalLetters);
	}

	short CountCapitalLetters()
	{
		return CountCapitalLetters(_Value);
	}

	static short CountSmallLetters(string st)
	{
		return CountLetters(st, smallLetters);
	}

	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}

	static short CountSpecificLetter(string st, char letter, bool CaseSensitive = true)
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

	short CountSpecificLetter(char letter, bool CaseSensitive = true)
	{
		return CountSpecificLetter(_Value, letter, CaseSensitive);
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

	static string InvertAllLettersCase(string st)
	{
		for (int i = 0; i < st.length(); i++)
		{
			st[i] = InvertCharCase(st[i]);
		}
		return st;
	}

	void InvertAllLettersCase()
	{
		InvertAllLettersCase(_Value);
	}

	static bool IsVowel(char letter)
	{
		letter = tolower(letter);
		return letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u';
	};

	static short CountVowels(string st)
	{
		short counter = 0;
		for (short i = 0; i < (short)st.size(); i++)
		{
			if (IsVowel(st[i]))
				counter++;
		}
		return counter;
	}

	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static vector<string> Split(string S1, string Delim)
	{
		vector<string> vString;
		short pos = 0;
		string sWord;
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			vString.push_back(sWord);
			S1.erase(0, pos + Delim.length());
		}
		if (S1 != "")
		{
			vString.push_back(S1);
		}
		return vString;
	}

	vector<string> Split(string delimiter = " ")
	{
		return Split(_Value, delimiter);
	}

	static string TrimLeft(string st)
	{
		for (short i = 0; i < st.length(); i++)
		{
			if (st[i] != ' ')
				return st.substr(i);
		}
		return "";
	}

	void TrimLeft()
	{
		TrimLeft(_Value);
	}

	static string TrimRight(string st)
	{
		for (short i = st.length() - 1; i >= 0; i--)
		{
			if (st[i] != ' ')
				return st.substr(0, i + 1);
		}
		return "";
	}

	void TrimRight()
	{
		TrimLeft(_Value);
	}

	static string Trim(string st)
	{
		return TrimLeft(TrimRight(st));
	}

	void Trim()
	{
		_Value = Trim(_Value);
	}

	static string JoinString(vector<string> vstring, string delimiter = " ")
	{
		string st = "";
		for (auto& i : vstring)
		{
			st += i + delimiter;
		}
		return st.erase(st.length() - delimiter.length());
	}

	static string JoinString(string arrString[], short length, string delimiter = " ")
	{
		string st = "";
		for (short i = 0; i < length; i++)
		{
			st += arrString[i] + delimiter;
		}
		return st.erase(st.length() - delimiter.length());
	}

	static string ReverseString(string st)
	{
		string sWord = "", delimiter = " ";
		short pos = 0;
		while ((pos = st.find(delimiter)) != string::npos)
		{
			sWord = sWord.insert(0, (delimiter + st.substr(0, pos)));

			st.erase(0, pos + delimiter.length());
		}
		if (st != "")
			return sWord.insert(0, st);
		return sWord;
	}

	void ReverseString()
	{
		_Value = ReverseString(_Value);
	}

	static string ReplaceWord(string st, string wordToReplace, string newWord, bool matchCase = true)
	{
		short pos = 0;
		string replaced = st;
		if (!matchCase)
		{
			wordToReplace = ToLower(wordToReplace);
			st = ToLower(st);
		}
		while ((pos = st.find(wordToReplace)) != string::npos)
		{
			replaced.replace(pos, wordToReplace.length(), newWord);
			st.replace(pos, wordToReplace.length(), newWord);
		}
		return replaced;
	}

	void  ReplaceWord(string wordToReplace, string newWord, bool matchCase = true)
	{
		_Value = ReplaceWord(_Value, wordToReplace, newWord, matchCase);
	}

	static string RemovePunctuations(string st)
	{
		for (short i = 0; i < st.size(); i++)
		{
			if (ispunct(st[i]))
			{
				st.erase(i, 1);
				i--;
			}
		}
		return st;
	}

	void RemovePunctuations()
	{
		_Value = RemovePunctuations(_Value);
	}
};
